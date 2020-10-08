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
vector<string> djikstras(string start, string end, GraphWithIdInternals<Id> graph);

template <typename Id = int>
bool isNotEnd(Id n, vector<Id> &endIds)
;

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
map<Id, vector<Id>> multiStartMultiEnd(vector<Id> starts, vector<Id> ends, GraphWithIdInternals<Id> graph);

// Since we are working with multiple exits we extend djikstras algorithm
// here is the first more "naive" method
template <typename Id = int>
vector<string> naiveEscape(string start, vector<string> exits, GraphWithIdInternals<Id> graph);

// In this less naive method algorithm, we note that we can terminate an iteration of djikstras
// algorithm as soon as we know there is a more expansive path.
template <typename Id = int>
vector<string> version2Escape(string start, vector<string> exits, GraphWithIdInternals<Id> graph);

// Run above - then we can look into doing something with computing the MST immediately after we ingest
// the graph
