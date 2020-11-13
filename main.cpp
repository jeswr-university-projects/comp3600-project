// #pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <boost/program_options.hpp>
// #include "rdf-types.h"
#include "rdf-io/reader.cpp"
#include "buildingTriples2graph.cpp"
#include "djikstras.cpp"
using namespace std;
using namespace boost;
using namespace boost::program_options;

Triples ingestCliTriples(string file, variables_map vm)
{
    if (vm.count(file))
    {
        try
        {
            Triples triples = getTriples(vm[file].as<string>());
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
            throw error("Invalid file"  + file + "; please fix");
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
    Triples building, person, escape, risk;

    if (vm.count("help"))
    {
        cout << desc << "\n";
        return 1;
    }

    if (vm.count("calculate-paths"))
    {
        building = ingestCliTriples("building-file", vm);
        // person = ingestCliTriples("person-file", vm);

        GraphMatrix<string> graph = buildingsTriplesToGraph(building);

        set<int> exits;

        for (Triple t : building)
        {
            if (t[1] == "http://architecture#hasBuildingExit" && t[2] == "true")
            {
                exits.insert(graph.nameToId(t[0]));
            };
        };

        Map<int, vector<int>> paths = multiStartMultiEnd<int>({1}, exits, graph);

        cout << "ingesting data ..." << endl;
        if (!vm.count("escape-file")) {
            throw error("Please specify the escape-file in order to run this command");
        };
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
