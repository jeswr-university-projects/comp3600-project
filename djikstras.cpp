#include <vector>
#include <iostream>
#include "graph.h"
#include <limits>
using namespace std;

// Add assumption about the number of nodes begin
// less than the numeric limit of int in the system

// Another assumption is that the RDF file must represent
// a valid building; be correctly serialised; and that there
// is a path
int Infinity = std::numeric_limits<int>::max();

template <typename Id = int>
vector<string> djikstras(string start, string end, GraphWithIdInternals<Id> graph)
{
    // Id of the initial node we are working with
    Id startId = graph.toId(start);
    Id endId = graph.toId(end);
    // Initialise an array, with length equal to the number of
    // nodes

    // In order for this to work we do need some way of
    // mapping each node to an integer - TODO: WORK OUT
    // if this is ok

    // Possibly use hash maps here instead when generalising
    vector<bool> visited(graph.nodeCount(), false);
    vector<int> distance(graph.nodeCount(), Infinity);

    int current = startId;
    int currentDistance = 0;

    distance[current] = currentDistance;

    while (!visited[endId] && currentDistance != Infinity)
    {
        vector<weightedEdge> edges = graph.weightedEdges(current);

        int minTentative = Infinity;
        Id nextId;

        for (int i = 0; i < edges.size(); i++)
        {
            // Check to make sure the node has not yet been visited
            if (!visited[edges[i].object]) {
                int tentativeDistance = edges[i].weight + currentDistance;

                if (tentativeDistance < minTentative) {
                    minTentative = tentativeDistance;
                    nextId = i;
                };
                // Take the minimium of the current distance and the tentative distance
                distance[i] = min(distance[i], edges[i].weight + currentDistance);
            };
        };
        visited[current] = true;
        currentDistance = minTentative;
        current = i;
    };

    // Now we extract the root from that
    


    // for (int i = 0; i < edges.size(); i++)
    // {
    // };

    // edges[0].object
    //     //

    //     bool visited[graph.nodeCount()];
    // return {};
};

// Since we are working with multiple exits we extend djikstras algorithm
// here is the first more "naive" method
template <typename Id = int>
vector<string> naiveEscape(string start, vector<string> exits, GraphWithIdInternals<Id> graph)
{
    // In the naive method we just apply djikstras algorithm to each exit
    // and then take the best
}

// In this less naive method algorithm, we note that we can terminate an iteration of djikstras
// algorithm as soon as we know there is a more expansive path.
template <typename Id = int>
vector<string> version2Escape(string start, vector<string> exits, GraphWithIdInternals<Id> graph)
{
}

// Run above - then we can look into doing something with computing the MST immediately after we ingest
// the graph
