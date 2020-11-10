#include <iostream>
#include <fstream>
#include <vector>
// #include <map>
#include "graph.h"
#include "hash-map.cpp"

using namespace std;

// struct LinkedEdgeList {

// };

template <typename K>
struct Edge
{
    K object;
    int weight;
};

// Should try and keep a record of the number of
// subjects and objects first that way we can
// initialise the array
template <typename NodeKind>
struct Graph
{
    // Technically should handle case of tring to add a different
    // weight to the same object but I don't think that is necessary
    // here
    void addEdge(string subject, string object, int weight)
    {

        int s = nameToId(subject);
        Edge<int> edge = {
            object : nameToId(object);
    weight:
        weight;
    };

    if (graph.hasKey(s))
    {
        graph.get(s).push_back(edge)
    }
    else
    {
        graph.add(s, {edge})
    };

    void removeEdge(string subject, string object)
    {
        int s = nameToId(subject);
        int o = nameToId(subject);

        if (graph.hasKey(s))
        {
            vector<Edge<int>> *edges = graph.get(s);
            vector<Edge<int>> edgesCopy = edges;
            edges.clear();
            for (int edge : edgesCopy)
            {
                if (edge.)
            };
        };
    }

    // graph.get(nameToId(subject)).push_back()

    // graph.add(nameToId(subject), {
    //     object : nameToId(object);
    //     weight : weight;
    // })
};

private:
// Important assumption is that we only
// ever want to to queries starting
// at the 's'.
Map<int, vector<Edge<int>>> graph = {};
Map<NodeKind, int> named = {};

// graph.
// need to map subject to tuple with
// [predicate, object][]

// Converts beteen name of entry
// and row/col of matrix

// vector<array<string | vector<int>, 2>> named = {};

int nameToId(string name)
{
    int i = 0;
    // TODO: CHECK/FIX
    while (i++ < named.size())
    {
        if (name == named[i])
        {
            return i;
        };
    }
    // Name does not yet exist on matrix
    named.push_back(name);
    return i;
};

// Implemented like this so it is easier to update
string idToName(int id)
{
    return named[id];
};
}
;