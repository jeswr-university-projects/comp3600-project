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
            TriplesAndPrefixes triples = getTriples(vm[file].as<string>());
            // cout << "ingested triples ..." << endl;
            // for (Triple t : triples)
            // {
            //     cout << t[0] << ' ' << t[1] << ' ' << t[2] << endl;
            // };
            // cout << endl;
            return triples;
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
            cout << "----------------------person triple------------------------" << endl;
            cout << p[0] << " " << p[1] << " " << p[2] << endl;
            if (p[1] == "http://architecture#located")
            {
                int id = graph.nameToId(p[2]);
                locations.add(p[0], id);
                startIds.insert(id);
                people.insert(p[0]);
                cout << "---------------------found location------------------------" << endl;
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

        cout << "at line 78" << endl;

        // int startId = graph.nameToId("http://architecture#room_ConferenceRoom1");

        Map<int, vector<int>> paths = multiStartMultiEnd<int>(startIds, exits, graph);

        cout << "at line 82" << endl;

        cout << "the path size is" << paths.size() << endl;

        for (int startId : startIds)
        {
            for (int p : paths.get(startId))
            {
                cout << p << " ";
            };
            cout << endl;

            for (int p : paths.get(startId))
            {
                cout << graph.idToName(p) << " ";
            };
            cout << endl;
        };

        for (string p : people)
        {
            cout << "adding escape triple for " << p << endl;
            // Triple t = {
            //     p,
            //     "http://example.org/escape_route",
            //     "http://example.org/" + to_string(skol_id++)
            // };
            int order = 0;
            vector<int> pathList = paths.get(locations.get(p));

            // skol_id++;
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
                cout << path << " ";
                escapeTriples.push_back({"http://example.org/" + to_string(skol_id),
                                         "http://example.org/path",
                                         graph.idToName(path)});

                // skol_id++;

                escapeTriples.push_back({"http://example.org/" + to_string(skol_id),
                                         "http://www.w3.org/1999/02/22-rdf-syntax-ns#rest",
                                         "http://example.org/" + to_string(++skol_id)});
            };

            cout << endl;

            escapeTriples.push_back({"http://example.org/" + to_string(skol_id),
                                     "http://www.w3.org/1999/02/22-rdf-syntax-ns#rest",
                                     "http://www.w3.org/1999/02/22-rdf-syntax-ns#nil"});
            }
            else
            {
                escapeTriples.push_back({p,
                                     "http://example.org/canEscape",
                                     "false"});
            }
            
        };

        cout << "ingesting data ..." << endl;
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

    // if (vm.count("calculate-risk"))
    // {
    //     building = ingestCliTriples("building-file", vm);
    //     person = ingestCliTriples("person-file", vm);
    //     escape = ingestCliTriples("escape-file", vm);
    //     risk = ingestCliTriples("risk-file", vm);
    // };

    // if (vm.count("run-diagnostics"))
    // {
    //     if (!vm.count("diagnostics-file")) {
    //         throw error("Please specify location to output diagnostics file");
    //     }
    // };

    // building.

    //     vm["compression"]

    // Performing checks to make sure

    // if (vm.count("compression"))
    // {
    //     cout << "Compression level was set to "
    //          << vm["compression"].as<int>() << ".\n";
    // }
    // else
    // {
    //     cout << "Compression level was not set.\n";
    // }

    // if (argc < 3)
    // {
    //     cout << "Please supply the documents for the building and persons";
    // }
    // else
    // {
    //     Triples building, people;

    // try
    // {
    //     Triples building = getTriples(argv[1]);
    //     cout << "ingested building triples ..." << endl;
    //     for (Triple t : building)
    //     {
    //         cout << t[0] << ' ' << t[1] << ' ' << t[2] << endl;
    //     };
    //     cout << endl;
    // }
    // catch (int e)
    // {
    //     cout << "Invalid building file; please fix";
    //     return 0;
    // };

    //     try
    //     {
    //         Triples people = getTriples(argv[2]);
    //         cout << "ingested person triples ..." << endl;
    //         for (Triple t : people)
    //         {
    //             cout << t[0] << ' ' << t[1] << ' ' << t[2] << endl;
    //         };
    //     }
    //     catch (int e)
    //     {
    //         cout << "Invalid person file; please fix";
    //         return 0;
    //     };
    // };

    // bool paths = true;
    // bool risk = true;
    // bool diagonstics = false;
    // vector<char> opt;

    // for (int i = 3; i <= argc; i++)
    // {
    //     x = program_options.()
    //             string s = argv[i];
    //     for (int i = 1; i < s.length(); i++)
    //     {
    //         cout << s[i] << endl;
    //     };
    //     cout << 5;
    // };

    return 0;
};
