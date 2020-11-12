#include "graph.h"
#include "../rdf-io/reader.cpp"
#include "../buildingTriples2graph.cpp"

GraphMatrix<string> functionalityOne(string file)
{
    return buildingsTriplesToGraph(getTriples(file));
};

// int main(int argc, int* argv[])
// {
//     functionalityOne()
// };