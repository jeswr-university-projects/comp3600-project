#include "graph-list.cpp" rename("Graph", "GraphList");
#include "graph-matrix.cpp" rename("Graph", "GraphMatrix");


template<typename NodeKind>
struct Graph {
    Graph(bool sparse = true) {
        this = sparse ? GraphList<NodeKind>() : GraphMatrix<NodeKind>();
    };
};

int main()
{
    cout << "compilation test worked" << endl;  
};




// #include <iostream>

// using namespace std;

// /**
//  * Used to capture an edge with a weight 
//  */
// struct weightedEdge {
//     string subject;
//     string object;
//     int weight;
// };

// /** 
//  * Used (when we already have the subject nodes)
//  * to capture an object node and the associated
//  * weight
//  */
// struct weightedNode {
//     string object;
//     int weight;
// };

// // Creating our generic Id type
// template<typename Id = int>
// struct _weightedEdge {
//     Id subject;
//     Id object;
//     int weight;
// };

// template<typename Id = int>
// struct _weightedNode {
//     Id object;
//     int weight;
// };

// /**
//  * The abstract data strucuture with which we 
//  */
// template <typename NodeKind = string>
// struct Graph {
//     int nodeCount();
//     int edgeCount();
//     void addEdge(NodeKind subject, NodeKind object, int weight);
//     vector<_weightedEdge<NodeKind>> weightedEdges(NodeKind subject);
//     _weightedEdge<NodeKind> lightestEdge(NodeKind subject);
// };

// // Algorithms such as djikstras are more efficient
// // to implement on the *id* rather than doing conversions
// // between the id rather than the more abstract graph
// // so we create this struct with internals that we
// // can use to create djikstras algoritm
// template<typename Id = int>
// struct GraphWithIdInternals {
//     int nodeCount();
//     int edgeCount();
//     Id toId(string subject);
//     string fromId(Id id);
//     vector<_weightedEdge<Id>> weightedEdges(Id subject);
//     _weightedEdge<Id> lightestEdge(Id suject);
//     void addEdge(string subject, string object, int weight);
// };
