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

int g_int = 12;
GraphMatrix<string> buildingsTriplesToGraph(Triples buildingTriples)
{
    // // First we need to determine
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

    // GraphMatrix<string> myGraph;
    // myGraph.print();
    // myGraph.addEdge("http://example.org/subject", "http://example.org/predicate", 10);
    // myGraph.addEdge("http://example.org/predicate", "http://example.org/predicate", 10);
    // myGraph.print();
    // myGraph.addEdge("http://example.org/subject1", "http://example.org/predicate2", 2);
    // myGraph.print();
    // myGraph.addEdge("http://example.org/subject2", "http://example.org/predicate2", 1);
    // myGraph.print();
    // myGraph.addEdge("http://example.org/subject2sd", "http://example.org/predicate2", 1);
    // myGraph.addEdge("http://example.org/predicate2", "http://example.org/predicate2", 1);
    // myGraph.print();
    // cout << endl
    //      << myGraph.edgeCount() << endl;

    // _weightedEdge<string> e = myGraph.lightestEdge("http://example.org/subject1");
    // cout << e.weight << " " << e.subject << " " << e.object << endl;

    // printf("%d\n", x);
    // if (VALGRIND_COUNT_ERRORS > 0)
    // {
    //     VALGRIND_PRINTF("y=%d, g_int=%d\n", y, g_int);
    // }
    // return x;

    // return myGraph;

    GraphMatrix<string> buildingGraph;// = ((2 * noEdges) > pow(rooms.size(), 2)) ? GraphMatrix<string>() : GraphMatrix<string>();
    // cout << "at line 38" << endl;

    // buildingGraph.addEdge("http://example.org/test", "http://example.org/test2", 1);

    // return buildingGraph;

    for (Triple triple : pathTriples)
    {
        cout << "reading in triple" << endl;
        cout << triple[0] << " " << triple[1] << " " << triple[2] << endl;
        cout << "triple read in" << endl;
        buildingGraph.addEdge(triple[0], triple[2], 1);
        buildingGraph.print();
    };
    return buildingGraph;
    // return buildingGraph;
};

// int main()
// {
//     Triples t = getTriples("tests/buildings/test-1.ttl");
//     for (Triple ts : t)
//     {
//         cout << ts[0] << ts[1] << ts[2] << endl;
//     };

//     // Functionality one
//     buildingsTriplesToGraph(t);
// };
