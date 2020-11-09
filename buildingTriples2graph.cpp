#include "graph.h";
#include "rdf-types.h";
#include <set>
#include <cmath>

using namespace std;

string pathTo = "http://architecture#hasPathTo";

Graph buildingsTriplesToGraph(Triples buildingTriples)
{
    // First we need to determine
    int noEdges = 0; // TODO: Double check
    set<string> rooms;
    Triples pathTriples;

    for (Triple triple : buildingTriples)
    {
        if (triple[1] == pathTo)
        {
            rooms.insert(triple[0]);
            noEdges++;
            pathTriples.push_back(triple);
        }
    };

    // In the true case we consider the
    // rooms to be dense enough to use
    // a matrix as the uderlying data structure
    // rather than linked list
    Graph buildingGraph = 2 * noEdges > pow(rooms.size(), 2) ? Graph() : Graph();

    for (Triple triple : pathTriples)
    {
        buildingGraph.addEdge(triple[0], triple[2], 1);
    };

    return buildingGraph;
};