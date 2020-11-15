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
#include "RB-tree.cpp"
// #include <httplib.h>
using namespace std;
using namespace boost;
using namespace boost::program_options;

// This is the skolemizer id so that we
// can provide a unique identifier to each
// blank node that we are working with.
int skol_id = 0;

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
    // int t = stof("0.1");
    // cout << t << endl;
    
    
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
        cout << desc << endl;
        return 1;
    };

    if (vm.count("unit-test"))
    {
    };

    // Now we perform the first functionality of materialising
    // the data - note that this operation is performed here as

    cout << "Materializing building strucutre in memory (functionality 1) ..." << endl;

    building = ingestCliTriples("building-file", vm);
    GraphMatrix<string> graph = buildingsTriplesToGraph(building.triples);

    cout << "Building triples materialized" << endl;

    person = ingestCliTriples("person-file", vm);
    
    cout << "Person triples materialized" << endl;

    set<int> exits;
    Map<string, RoomDimensions> dimensions;

    for (Triple t : building.triples)
    {
        if (t[1] == "http://architecture#hasBuildingExit" && t[2] == "true")
        {
            exits.insert(graph.nameToId(t[0]));
        }
        else if (t[1] == "http://architecture#width") // Could just calc area directly
        {
            if (!dimensions.hasKey(t[0]))
            {
                dimensions.add(t[0], RoomDimensions(stoi(t[2]), 0));
            }
            else
            {
                dimensions.add(t[0], RoomDimensions(stoi(t[2]), dimensions.get(t[0]).length));
                // RoomDimensions d = dimensions.get(t[0]);
                // d.width = stof(t[2]);
            };
        }
        else if (t[1] == "http://architecture#length")
        {
            if (!dimensions.hasKey(t[0]))
            {
                dimensions.add(t[0], RoomDimensions(0, stoi(t[2])));
            }
            else
            {
                // dimensions.get(t[0]).length = stof(t[0]);
                // dimensions.get(t[0]).length = stof("0.1");
                dimensions.add(t[0], RoomDimensions(dimensions.get(t[0]).width, stoi(t[2])));
                
                // RoomDimensions d = dimensions.get(t[0]);
                // d.length = stof(t[2]);
            };
        };
    };

    Map<int, int> path = shortestNeightbour(exits, graph);

    // person = ingestCliTriples("person-file", vm);

    // GraphMatrix<string> graph = buildingsTriplesToGraph(building.triples);

    if (vm.count("calculate-paths"))
    {
        // building = ingestCliTriples("building-file", vm);
        person = ingestCliTriples("person-file", vm);

        // GraphMatrix<string> graph = buildingsTriplesToGraph(building.triples);

        int skol_id = 0;

        Map<string, int> locations;
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

        for (string p : people)
        {
            int location = locations.get(p);

            if (path.hasKey(location))
            {

                escapeTriples.push_back({p,
                                         "http://example.org/canEscape",
                                         "\"true\""});

                escapeTriples.push_back({p,
                                         "http://example.org/escapeRoute",
                                         "http://example.org/" + to_string(++skol_id)});

                while (location != -1)
                {
                    escapeTriples.push_back({"http://example.org/" + to_string(skol_id),
                                             "http://example.org/path",
                                             graph.idToName(location)});

                    escapeTriples.push_back({"http://example.org/" + to_string(skol_id),
                                             "http://www.w3.org/1999/02/22-rdf-syntax-ns#rest",
                                             "http://example.org/" + to_string(++skol_id)});

                    location = path.get(location);
                };

                escapeTriples.push_back({"http://example.org/" + to_string(skol_id),
                                         "http://www.w3.org/1999/02/22-rdf-syntax-ns#rest",
                                         "http://www.w3.org/1999/02/22-rdf-syntax-ns#nil"});
            }
            else
            {
                escapeTriples.push_back({p,
                                         "http://example.org/canEscape",
                                         "\"false\""});
            };
        };

        // Map<int, vector<int>> paths = multiStartMultiEnd<int>(startIds, exits, graph);

        // for (string p : people)
        // {
        //     int order = 0;
        //     vector<int> pathList = paths.get(locations.get(p));

        //     if (pathList.size() > 0)
        //     {
        //         escapeTriples.push_back({p,
        //                                  "http://example.org/canEscape",
        //                                  "true"});

        //         escapeTriples.push_back({p,
        //                                  "http://example.org/escapeRoute",
        //                                  "http://example.org/" + to_string(++skol_id)});

        //         for (int path : pathList)
        //         {

        //             escapeTriples.push_back({"http://example.org/" + to_string(skol_id),
        //                                      "http://example.org/path",
        //                                      graph.idToName(path)});

        //             escapeTriples.push_back({"http://example.org/" + to_string(skol_id),
        //                                      "http://www.w3.org/1999/02/22-rdf-syntax-ns#rest",
        //                                      "http://example.org/" + to_string(++skol_id)});
        //         };

        //         escapeTriples.push_back({"http://example.org/" + to_string(skol_id),
        //                                  "http://www.w3.org/1999/02/22-rdf-syntax-ns#rest",
        //                                  "http://www.w3.org/1999/02/22-rdf-syntax-ns#nil"});
        //     }
        //     else
        //     {
        //         escapeTriples.push_back({p,
        //                                  "http://example.org/canEscape",
        //                                  "'false'"});
        //     };
        // };

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

    // At this point we are able to assume that the escape file has been created by the
    // previous functionality
    // In additon we note that the shortest path mappings are also used in this functionality
    if (vm.count("calculate-risk"))
    {
        Map<string, IndividualRiskDetails> individualRisks = personRisks(person.triples, graph);
        cout << "individual risks have been generated" << endl;
        individualRisks.print();
        
        Map<int, RoomRisk> init = initRisk(graph, individualRisks);
        Map<int, RoomDimensions> dims;

        for (Pair<string, RoomDimensions> d : dimensions.getPairs())
        {
            dims.add(graph.nameToId(d.key), d.value);
        };

        Map<int, float> risks = generateCovidRisk(graph, init, path, dims);
        RBtree<IndividualAndRisk> riskTree;

        cout << "printing risks" << endl;
        for (Pair<int, float> r : risks.getPairs())
        {
            cout << r.key << " " << r.value;
        };

        // Now we actually determine those most likely to be at risk of covid
        for (Pair<string, IndividualRiskDetails> individual : individualRisks.getPairs())
        {
            cout << "inserting into risk tree" << endl;
            cout << individual.key << " " << individual.value.risk << " " << individual.value.startLocation << " " << risks.hasKey(individual.value.startLocation) << endl;
            
            cout << "the starting point risk is" << risks.get(individual.value.startLocation) << endl;
            riskTree.insert(
                IndividualAndRisk(
                    individual.key, 
                    individual.value.risk + (1 - individual.value.risk) * risks.get(individual.value.startLocation)
                ));
        };
        
        vector<IndividualAndRisk> rs = riskTree.flat();
        cout << "-------------------------------" << endl;
        
        for (IndividualAndRisk r : rs)
        {
            cout << r.individual << " " << r.risk << endl;
        };

        cout << "--------------------------------" << endl;

        for (IndividualAndRisk r : riskTree.getHighest(3))
        {
            cout << r.individual << " " << r.risk << endl;
        };

        // cout << riskTree.flat().size() << endl;
        
        // Again we can argue that RB tree is better than just "live culling" as it allows
        // us to generalise the software more easily

        // We also need acknowledge that this process is just a heuristic
        // and there are some slightly odd effects such as "reflecting" your
        // own covid risk
        
        cout << "inside calculate risk" << endl;
    };

    return 0;
};
