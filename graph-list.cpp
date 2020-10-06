#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "graph.h"

using namespace std;


// Should try and keep a record of the number of 
// subjects and objects first that way we can
// initialise the array
struct Graph {

    void addEdge(string subject, string object, int weight) {
        int s = nameToId(subject);
        int o = nameToId(object);
        matrix.addEntry(s, o, weight);
    };

    private:
        // Important assumption is that we only
        // ever want to to queries starting
        // at the 's'.
        map<string, vector<int>> graph = {};
        graph.
        // need to map subject to tuple with
        // [predicate, object][]


        // Converts beteen name of entry
        // and row/col of matrix



        vector<array<string | vector<int>, 2>> named = {};



        int nameToId(string name) {
            int i = 0;
            // TODO: CHECK/FIX
            while (i++ < named.size()) {
                if (name == named[i]) {
                    return i;
                };
            }
            // Name does not yet exist on matrix
            named.push_back(name);
            return i;
        };

        // Implemented like this so it is easier to update
        string idToName(int id) {
            return named[id];
        };
};