// #pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <boost/program_options.hpp>
// #include "rdf-types.h"
#include "rdf-io/reader.cpp"
#include "rdf-io/writer.cpp"
#include "buildingTriples2graph.cpp"
#include "djikstras.cpp"
#include "risk-calculation.cpp"
// #include <httplib.h>
using namespace std;
using namespace boost;
using namespace boost::program_options;

TriplesAndPrefixes ingestCliTriples(string file, variables_map vm)
{
    if (vm.count(file))
    {
        try
        {
            return getTriples(vm[file].as<string>());
        }
        catch (int e)
        {
            throw error("Invalid file" + file + "; please fix");
        };
    }
    else
    {
        throw error("Please specify the " + file + " in order to run this command");
    };
}

int main(int argc, char *argv[])
{
    // Declare the supported options.
    options_description desc("Allowed options");
    desc.add_options()("help,h", "produce help message")("building-file,b", value<string>(), "A .ttl file (to read) containing information about the architecture of the building")("person-file,p", value<string>(), "A .ttl file (to read) containing information the location of people in the building")("escape-file,e", value<string>(), "A .ttl file (to read/write) containing the escape paths to be taken by those in the building")("risk-file,s", value<string>(), "A .ttl file (to read/write) containing the escape paths to be taken by those in the building")("diagnostic-file,d", value<string>(), "A .txt file (to write) which contains diagonstics of running the algorithm")("calculate-paths,c", "Calculate the escape path to be taken")("calculate-risk,r", "Calculate the risk of catching covid")("run-diagnostics,i", "Run diagonstics on the program and output to the assigned .txt file");

    variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);

    bool diagnostics = vm.count("run-diagnostics");
    TriplesAndPrefixes building, person, escape, risk;

    if (vm.count("help"))
    {
        cout << desc << "\n";
        return 1;
    };

    if (vm.count("calculate-paths"))
    {
        building = ingestCliTriples("building-file", vm);
        person = ingestCliTriples("person-file", vm);

        GraphMatrix<string> graph = buildingsTriplesToGraph(building.triples);

        int skol_id = 0;

        Map<string, int> locations;
        Map<string, RoomDimensions> dimensions;
        set<string> people;
        set<int> startIds;
        Triples escapeTriples;

        for (Triple p : person.triples)
        {
            if (p[1] == "http://architecture#located")
            {
                int id = graph.nameToId(p[2]);
                locations.add(p[0], id);
                startIds.insert(id);
                people.insert(p[0]);
            };
        };

        set<int> exits;

        for (Triple t : building.triples)
        {
            if (t[1] == "http://architecture#hasBuildingExit" && t[2] == "true")
            {
                exits.insert(graph.nameToId(t[0]));
            }
            else if (t[1] == "http://architecture#width") // Could just calc area directly
            {
                if (dimensions.hasKey(t[0]))
                {
                    dimensions.add(t[0], {
                        width : stof(t[0]),
                        length : 0
                    });
                }
                else
                {
                    dimensions.get(t[0]).width = stof(t[0]);
                };
            }
            else if (t[1] == "http://architecture#length")
            {
                if (dimensions.hasKey(t[0]))
                {
                    dimensions.add(t[0], {
                        width : 0,
                        length : stof(t[0])
                    });
                }
                else
                {
                    dimensions.get(t[0]).length = stof(t[0]);
                };
            };
        };

        Map<int, vector<int>> paths = multiStartMultiEnd<int>(startIds, exits, graph);

        for (string p : people)
        {
            int order = 0;
            vector<int> pathList = paths.get(locations.get(p));

            if (pathList.size() > 0)
            {
                escapeTriples.push_back({p,
                                         "http://example.org/canEscape",
                                         "true"});

                escapeTriples.push_back({p,
                                         "http://example.org/escapeRoute",
                                         "http://example.org/" + to_string(++skol_id)});

                for (int path : pathList)
                {
    
                    escapeTriples.push_back({"http://example.org/" + to_string(skol_id),
                                             "http://example.org/path",
                                             graph.idToName(path)});

                    escapeTriples.push_back({"http://example.org/" + to_string(skol_id),
                                             "http://www.w3.org/1999/02/22-rdf-syntax-ns#rest",
                                             "http://example.org/" + to_string(++skol_id)});
                };

                escapeTriples.push_back({"http://example.org/" + to_string(skol_id),
                                         "http://www.w3.org/1999/02/22-rdf-syntax-ns#rest",
                                         "http://www.w3.org/1999/02/22-rdf-syntax-ns#nil"});
            }
            else
            {
                escapeTriples.push_back({p,
                                         "http://example.org/canEscape",
                                         "'false'"});
            };
        };

        if (!vm.count("escape-file"))
        {
            throw error("Please specify the escape-file in order to run this command");
        };

        string outFile = vm["escape-file"].as<string>();
        // TODO: Change prefix map to our map

        person.prefixes["rdfs"] = "http://www.w3.org/1999/02/22-rdf-syntax-ns#";
        writeTriples(escapeTriples, person.prefixes, outFile);

        // httplib::Client cli("http://www.ldf.fi/service/rdf-grapher");

        // cli.Post("", "from=ttl", "to=png","rdf=")

        //escape = ingestCliTriples("escape-file", vm);
    };

    return 0;
};
