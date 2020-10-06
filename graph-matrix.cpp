#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "graph.h"

using namespace std;

template <typename T = int>
struct Matrix {

    Matrix(int _rows = 0, int _cols = 0, T dflt = 0) 
    {
        rows = _rows;
        cols = _cols;
        vector <T> dfltCol(rows, dflt);
        vector<vector<T>> matrix(cols, dfltCol);
    };

    void addColumn() {
        matrix.push_back(defaulCol)
    };

    void addRow() {
        for (let i = 0, i < columns; i++) {
            matrix[i].push_back(dflt);
        };
    };

    void addEntry(int row, int col, int val) {
        matrix[row][col] = val;
    };

    int getRows() {
        return rows;
    };

    int getColumns() {
        return columns;
    };

    vector<int> getRow(int no)
    {
        vector<int> row = {};
        for (int i = 0; i < cols; i++) {
            row.push_back(matrix[i][no])
        }
        return row
    }

    vector<int> getCol(int no)
    {
        return matrix[no]
    }

    int getEntry(int row, int col) 
    {
        return matrix[row][col]
    }

    private:
        int rows, cols;
        vector <T> dfltCol(rows);
        vector<vector<T>> matrix;
};

template <typename T = int>
struct SquareMatrix {

    SquareMatrix(int size = 0, T dflt = 0) 
    {
        _matrix = Matrix<T>(size, size, dflt);
    };

    void addDim() 
    {
        _matrix.addRow();
        _matrix.addColumn();
    }

    int size() 
    {
        return _matrix.getRows();
    };

    void addEntry(int row, int col, T val)
    {
        _matrix.addEntry(row, col, val);
    };

    int getEntry(int row, int col)
    {
        return _matrix.getEntry(row, col);
    }

    vector<int> getCol(int no)
    {
        return _matrix.getCol(no);
    };

    vector<int> getRow(int no) {
        return _matrix.getRow(no);
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
struct weightedEdge {
    string subject;
    string object;
    int weight;
};

/** 
 * Used (when we already have the subject nodes)
 * to capture an object node and the associated
 * weight
 */
struct weightedNode {
    string object;
    int weight;
};





// Should try and keep a record of the number of 
// subjects and objects first that way we can
// initialise the array
struct Graph {

    void addEdge(string subject, string object, int weight) 
    {
        int s = nameToId(subject);
        int o = nameToId(object);
        edges += 1;
        matrix.addEntry(s, o, weight);
    };

    vector<weightedNode> getEdges(string subject) 
    {
        int id = nameToId(subject);
        vector<int> col = matrix.getCol(id);

    };

    int nodeCount() 
    {
        return matrix.size();
    };

    int edgeCount()
    {
        return 
    };

    void _djikstra(int start) 
    {
        array<bool> visited[]
        
        vector<int> visited = {};

    }

    void djikstra(string start)
    {
        return _djikstra(nameToId(start))
    }

    private:
        // Converts beteen name of entry
        // and row/col of matrix
        vector<string> named = {};

        SquareMatrix<int> matrix;

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
            matrix.addDim();
            return i;
        };

        // Implemented like this so it is easier to update
        string idToName(int id) {
            return named[id];
        };

        int edges = 0;

};