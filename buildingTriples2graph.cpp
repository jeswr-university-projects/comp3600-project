#pragma once
// #include "graph.h"
#include "rdf-types.h"
#include <set>
#include <cmath>
#include "graph-matrix.cpp"
#include "rdf-io/reader.cpp"
#include <vector>
#include <valgrind/valgrind.h>

using namespace std;

string pathTo = "http://architecture#hasPathTo";

GraphMatrix<string> buildingsTriplesToGraph(Triples buildingTriples)
{
    int noEdges = 0; // TODO: Double check
    set<string> rooms;
    Triples pathTriples;

    rooms.clear();
    pathTriples.clear();

    for (Triple triple : buildingTriples)
    {
        if (triple[1] == pathTo)
        {
            rooms.insert(triple[0]);
            noEdges++;
            pathTriples.push_back(triple);
        };
    };

    // In the true case we consider the
    // rooms to be dense enough to use
    // a matrix as the uderlying data structure
    // rather than linked list
    // TODO: FIX UP POLYMORPHISM OF DATA STRUCUTURES

    GraphMatrix<string> buildingGraph;// = ((2 * noEdges) > pow(rooms.size(), 2)) ? GraphMatrix<string>() : GraphMatrix<string>();

    for (Triple triple : pathTriples)
    {
        buildingGraph.addEdge(triple[0], triple[2], 1);
        buildingGraph.print();
    };
    return buildingGraph;
};
