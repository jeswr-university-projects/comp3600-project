#include <vector>
#include <iostream>
#include "graph.h"
#include <limits>
#include <map>
using namespace std;

// move23 a move .
// move23 moveTime t .
// move23 moveTo nodeX .
// This is a dynamic programming problem as we can break problems into an acyclic graph over time




// Assume that infection risk is not increased in hallway traversals
// as they are *spread out* through the hallway and they
// are already at risk in the rooms they have gone to/from

// Add assumption about infection risk having to be
// calculated at a separate stage going directly from the
// RDF file - this makes sense as we should not be calculating
// the infection risk *whilst* working out the safest way
// to get everyone out of the building. This allows us to
// just write the functionality directly from read in triple.
// We can also expand on the complexity of reading in this particlar data.
// First we need

// Add assumption that the compiler being used is
// doing this <https://stackoverflow.com/questions/35052586/is-it-more-efficient-to-store-vector-size-into-an-int-variable-when-using-it-mul>
// optimisation

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

    // TODO: FIX THE SECOND CONDITION IN THIS LOOP
    while (!visited[endId] && currentDistance != Infinity)
    {
        // vector<weightedEdge> edges = graph.weightedEdges(current);

        int minTentative = Infinity;
        Id nextId;

        for (weightedEdge edge : graph.weightedEdges(current))
        {
            // Check to make sure the node has not yet been visited
            if (!visited[edges[i].object])
            {
                int tentativeDistance = edges[i].weight + currentDistance;

                if (tentativeDistance < minTentative)
                {
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
    vector<string> path = {start};
    Id focus = startId;

    while (focus != endId)
    {
        int min = Infinity;

        for (weightedEdge edge : graph.weightedEdges(focus))
        {
            if ((int temp = distance[edge.object]) < min)
            {
                min = temp;
                focus = edge.object;
            };
        };

        path.push_back(graph.fromId(focus));
    };

    return path;
};

template <typename Id = int>
bool isNotEnd(Id n, vector<Id> &endIds)
{
    for (int i : endIds)
    {
        if (i == n)
        {
            return false;
        };
    };
    return true;
};

struct nodeInfo {
    bool end = true;
    bool visited = false;
    int weight = 0;
};

struct Info {
    bool end = true;
    bool visited = false;
    int weight = 0;
};

template <typename Id = int>
map<Id, vector<Id>> multiStartMultiEnd(vector<Id> starts, vector<Id> ends, GraphWithIdInternals<Id> graph)
{
    map<Id, vector<Id>> paths;
    map<Id, Info> ending;
    for (Id end: ends)
    {
        ending[end] = {
            end: true;
            weight: 0;
        };
    };
    for (Id start: starts) 
    {
        // TODO:
    };
};



template <typename Id = int>
vector<string> djikstrasMultiEndpoint(string start, vector<string> end, GraphWithIdInternals<Id> graph)
{
    map<Id, 
    
    
    
    
    Id room = graph.toId(start);
    int distance = Infinity;

    vector<bool> visited(graph.nodeCount(), false);
    vector<int> dist(graph.nodeCount(), Infinity);

    vector<Id> endIds;
    for (string e : end)
    {
        endIds.push_back(graph.toId(e));
    };

    while (isNotEnd(room))
    {

    }

        dist[room] = 0;
    visited[room] = true;

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
