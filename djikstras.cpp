#include <vector>
#include <iostream>
#include "graph.h"

template<typename Id = int>
vector<string> djikstras(string start, string end, GraphWithIdInternals<Id> graph)
{
    // Id of the initial node we are working with
    Id startId = graph.toId(start);
    
    // Initialise an array, with length equal to the number of
    // nodes

    // In order for this to work we do need some way of
    // mapping each node to an integer - TODO: WORK OUT
    // if this is ok
    vector<bool> visited(graph.nodeCount(), false);
    
    // 

    bool visited[graph.nodeCount()];
    return {};
};

// Since we are working with multiple exits we extend djikstras algorithm
// here is the first more "naive" method
template<typename Id = int>
vector<string> naiveEscape(string start, vector<string> exits, GraphWithIdInternals<Id> graph)
{
    // In the naive method we just apply djikstras algorithm to each exit
    // and then take the best
}

// In this less naive method algorithm, we note that we can terminate an iteration of djikstras
// algorithm as soon as we know there is a more expansive path.
template<typename Id = int>
vector<string> version2Escape(string start, vector<string> exits, GraphWithIdInternals<Id> graph)
{

}

// Run above - then we can look into doing something with computing the MST immediately after we ingest
// the graph
