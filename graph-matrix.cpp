#pragma once
#include <iostream>
#include <fstream>
#include <vector>
// #include <map>
#include <limits>
#include "graph.h"
#include "hash-map.cpp"

using namespace std;

int Infinity = numeric_limits<int>::max();

template <typename T = int>
struct Matrix
{
    // If the number of rows/columns are known in advance
    // we hence can pre-allocate O(rows + cols)
    Matrix(int _rows = 0, int _cols = 0, T _dflt = 0)
    {
        rows = _rows;                            // O(1)
        cols = _cols;                            // O(1)
        dflt = _dflt;                            // O(1)
        vector<T> dfltCol(rows, dflt);           // O(rows)
        vector<vector<T>> matrix(cols, dfltCol); // O(cols)
    };

    // O(1) time complexity (though this will be amatorized)
    // if the number of rows/cols are left at 0 to start off
    // with
    void addColumn()
    {
        matrix.push_back(dfltCol);
        cols++;
    };

    // O(n) time complexity (though this will be amatorized)
    // if the number of rows/cols are left at 0 to start off
    // with
    void addRow()
    {
        for (int i = 0; i < cols; i++)
        {
            matrix[i].push_back(dflt);
        };
        dfltCol.push_back(dflt);
        rows++;
    };

    // O(1)
    void addEntry(int row, int col, int val)
    {
        matrix[row][col] = val;
    };

    // O(1)
    int getRows()
    {
        return rows;
    };

    // O(1)
    int getColumns()
    {
        return cols;
    };

    // O(cols)
    vector<int> getRow(int no)
    {
        vector<int> row;
        row.reserve(cols);
        for (int i = 0; i < cols; i++)
        {
            row.push_back(matrix[i][no]);
        };
        return row;
    }

    // O(1)
    vector<int> getCol(int no)
    {
        return matrix[no];
    };

    // O(1)
    int getEntry(int row, int col)
    {
        return matrix[row][col];
    };

    void print()
    {
        for (vector<T> c : matrix)
        {
            for (T e : c)
            {
                cout << e << " ";
            };
            cout << "|" << endl;
        };
    };

private:
    int rows = 0;
    int cols = 0;
    int dflt = 0;
    vector<T> dfltCol;
    vector<vector<T>> matrix;
};

template <typename T = int>
struct SquareMatrix
{

    // O(size^2 + 1)
    SquareMatrix(int size = 0, T dflt = 0)
    {
        _matrix = Matrix<T>(size, size, dflt);
    };

    // O(n)
    void addDim()
    {
        _matrix.addRow();
        _matrix.addColumn();
    }

    // O(1)
    int size()
    {
        return _matrix.getRows();
    };

    // O(1)
    void addEntry(int row, int col, T val)
    {
        // cout << "at add entry " << endl;
        while ((row >= size()) || (col >= size()))
        {
            cout << "adding dim " << this->size() << endl;
            addDim();
        };
        cout << "dims added" << endl;
        _matrix.addEntry(row, col, val);
    };

    // O(1)
    int getEntry(int row, int col)
    {
        return _matrix.getEntry(row, col);
    };

    // O(1)
    vector<int> getCol(int no)
    {
        return _matrix.getCol(no);
    };

    // O(no)
    vector<int> getRow(int no)
    {
        return _matrix.getRow(no);
    };

    void print()
    {
        _matrix.print();
    }

private:
    Matrix<T> _matrix;
};

// Note that for weightedEdge and weightedNode we have to
// already have converted back into the string subject/object
// by this point, hence it is going to add expense to our calculation
// a better option may be handle djikstras algorithm using a more
// "private" id and then following this promote the final result to the
// actual value

/**
 * Used to capture an edge with a weight 
 */
// struct weightedEdge {
//     string subject;
//     string object;
//     int weight;
// };

/** 
 * Used (when we already have the subject nodes)
 * to capture an object node and the associated
 * weight
 */
// struct weightedNode {
//     int object;
//     int weight;
// };

// Should try and keep a record of the number of
// subjects and objects first that way we can
// initialise the array
template <typename T>
class GraphMatrix
{
public:
    // O(nodes^2 + 1)
    GraphMatrix(int nodes = 0)
    {
        this->matrix = SquareMatrix<int>(nodes);
    };

    void addEdge(T subject, T object, int weight)
    {
        int s = nameToId(subject);
        int o = nameToId(object);
        this->edges++;
        this->matrix.addEntry(s, o, weight);
    };

    int nodeCount()
    {
        return matrix.size();
    };

    int edgeCount()
    {
        return edges;
    };

    vector<_weightedEdge<T>> weightedEdges(T subject)
    {
        vector<_weightedEdge<T>> output;
        vector<int> edges = matrix.getCol(names.get(subject));
        for (int i = 0; i < matrix.size(); i++)
        {
            if (edges[i] != 0)
            {
                output.push_back({
                    subject : subject,
                    object : names.getKey(i),
                    weight : edges[i]
                });
            };
        };
        return output;
    };

     vector<_weightedEdge<int>> _weightedEdgesInto(int object)
    {
        vector<_weightedEdge<int>> output;
        vector<int> edges = matrix.getRow(object);
        for (int i = 0; i < matrix.size(); i++)
        {
            if (edges[i] != 0)
            {
                output.push_back({
                    subject : i,
                    object : object,
                    weight : edges[i]
                });
            };
        };
        return output;
    };

    vector<_weightedEdge<int>> _weightedEdges(int subject)
    {
        vector<_weightedEdge<T>> output;
        vector<int> edges = matrix.getCol(subject);
        for (int i = 0; i < matrix.size(); i++)
        {
            if (edges[i] != 0)
            {
                output.push_back({
                    subject : subject,
                    object : i,
                    weight : edges[i]
                });
            };
        };
        return output;
    };

    _weightedEdge<int> _lightestEdge(int subject)
    {
        _weightedEdge<T> output;
        output.weight = Infinity;
        vector<int> edges = matrix.getCol(subject);

        


        for (int i = 0; i < matrix.size(); i++)
        {
            if (0 < edges[i] && edges[i] < output.weight)
            {
                output = {
                    subject : subject,
                    object : i,
                    weight : edges[i]
                };
            };
        };
        return output;
    };

    void print()
    {
        cout << "----" << endl;
        matrix.print();
        cout << "----" << endl;
        names.print();
        cout << "---------------" << endl;
    };

    int nameToId(T key)
    {
        int id;

        cout << "name to id called " << names.hasKey(key) << endl;
        cout << "------------------------------------------------" << endl;
        print();
        cout << "------------------------------------------------" << endl;

        if (!names.hasKey(key))
        {
            id = names.size();
            names.add(key, id);
        }
        else
        {
            id = names.get(key);
        };
        return id;
    };

    T idToName(int Id)
    {
        return names.getKey(Id);
    };

private:
    SquareMatrix<int> matrix;
    ReverseLookupMap<T, int> names;
    int edges = 0;
};

// int main()
// {
//     // GraphMatrix<string> myGraph;
//     GraphMatrix<string> myGraph;
//     myGraph.print();
//     myGraph.addEdge("http://example.org/subject", "http://example.org/predicate", 10);
//     myGraph.addEdge("http://example.org/predicate", "http://example.org/predicate", 10);
//     myGraph.print();
//     myGraph.addEdge("http://example.org/subject1", "http://example.org/predicate2", 2);
//     myGraph.print();
//     myGraph.addEdge("http://example.org/subject2", "http://example.org/predicate2", 1);
//     myGraph.print();
//     myGraph.addEdge("http://example.org/subject2sd", "http://example.org/predicate2", 1);
//     myGraph.addEdge("http://example.org/predicate2", "http://example.org/predicate2", 1);
//     myGraph.print();
//     cout << endl
//          << myGraph.edgeCount() << endl;

//     _weightedEdge<string> e = myGraph.lightestEdge("http://example.org/subject1");
//     cout << e.weight << " " << e.subject << " " << e.object << endl;

//     // Map<string, int> test;
//     // test.add("1", 1);
//     // test.add("2", 2);

//     // cout << test.size() << endl;
//     // cout << test.get("1") << endl;
//     // cout << test.get("2") << endl;

//     return 0;
// };

// template<typename T>
// Graph<T>::Graph()
// {
//     //SquareMatrix<int>
//     this->storage = SquareMatrix<int>();
// };

// template<typename T>
// void Graph<T>::addEdge(T subject, T object, int weight)
// {
//     int s = nameToId(subject);
//     int o = nameToId(object);
//     this->edges++;
//     this->matrix.addEntry(s, o, weight);
// };

// template<typename NodeKind>
// struct Graph {

// int nodeCount();
// int edgeCount();
// void addEdge(NodeKind subject, NodeKind object, int weight);
// vector<_weightedEdge<NodeKind>> weightedEdges(NodeKind subject);
// _weightedEdge<NodeKind> lightestEdge(NodeKind subject);

// void addEdge(NodeKind subject, NodeKind object, int weight)
// {
//     int s = nameToId(subject);
//     int o = nameToId(object);
//     edges++;
//     matrix.addEntry(s, o, weight);
// };

// vector<weightedNode> getEdges(NodeKind subject)
// {
//     int id = nameToId(subject);
//     vector<int> col = matrix.getCol(id);
// };

// int nodeCount()
// {
//     return matrix.size();
// };

// int edgeCount()
// {
//     return edges;
// };

// // void _djikstra(int start)
// // {
// //     array<bool> visited[]

// //     vector<int> visited = {};

// // }

// // void djikstra(string start)
// // {
// //     return _djikstra(nameToId(start))
// // }

// private:
//     // Converts beteen name of entry
//     // and row/col of matrix
//     vector<string> named = {};

//     SquareMatrix<int> matrix;

//     int nameToId(string name) {
//         int i = 0;
//         // TODO: CHECK/FIX
//         while (i++ < named.size()) {
//             if (name == named[i]) {
//                 return i;
//             };
//         };
//         // Name does not yet exist on matrix
//         named.push_back(name);
//         matrix.addDim();
//         return i;
//     };

//     // Implemented like this so it is easier to update
//     string idToName(int id) {
//         return named[id];
//     };

//     int edges = 0;
// };
