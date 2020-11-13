#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "../rdf-types.h"
using namespace std;

/**
 * Parses a single component (URI or object literal)
 * @param inFile an inFile stream
 * @param prefixes the prefixes to be used
 * In the following let n be the length of the "component"
 * in the file we are analysing - we are assuming the file
 * to be syntactically correct for the sake of this analysis
 * Time complexity is O(n)
 */
string component(ifstream &inFile, Prefixes &prefixes) {
    bool isURI = true; // O(1)
    bool hasPrefix = false; // O(1)
    char breakAt = '>'; // O(1)
    char c; // O(1)
    string val; // O(1)
    inFile >> c; // O(1)

    // Entire if statement is O(1)
    if (c == '<') {
        inFile >> c;
    } else if (c == '"') {
        inFile >> c;
        bool isURI = false;
        breakAt = '"';
    } else {
        hasPrefix = true;
        breakAt = ' ';
    }

    // Assume URI in this loop
    // O(n)
    while (c != breakAt && !(hasPrefix && (c == ',' || c == ';' || c == '.'))) {
        if (c == ':' && hasPrefix) {
            // This is when the triple has a prefix rather than a full uri
            val = prefixes[val];
        } else {
            val = val + c;
        };

        c = inFile.get(); // We care about whitespace here   
    };

    if (val.length() == 1 && val[0] == 'a') {
        return "http://www.w3.org/1999/02/22-rdf-syntax-ns#type";
    }

    if (c == ',') {
        inFile.putback(c);
    };

    return val;
};

/**
 * Takes the name of a file to be parsed and
 * returns the associated triples 
 * @param file the file name
 */
Triples getTriples(string file) {
    ifstream inFile(file); // O(1) ish?
    Triples triples = {}; // O(1)
    Prefixes prefixes = {}; // O(1)
    char c; // O(1)
    inFile >> c; // O(1)

    while (c == '@') {
        // Skips over the expected word 'prefix'
        inFile.seekg(inFile.tellg() + (std::streampos)6) >> c;
        string key;

        while ( c != ':' ) {
            key += c;
            c = inFile.get();
        };
        inFile >> c;

        while ( (c = inFile.get()) != '>' ) {
            prefixes[key] += c;
        };
        inFile >> c >> c;
    };

    // O(1)
    inFile.putback(c);

    while (inFile.peek() >= 0) {
        // O(subject component length)
        string s = component(inFile, prefixes);
        string p = component(inFile, prefixes);
        string o = component(inFile, prefixes);
        triples.push_back({s, p, o});
        inFile >> c;

        while (c == ';' || c == ',') {
            if (c == ';') {
                p = component(inFile, prefixes);
            };
            o = component(inFile, prefixes);
            triples.push_back({s, p, o});
            inFile >> c;
        };
    };
    return triples;
};
// We can argue that the complexity of this algorithm is O(n)
// where n is the length of the file (in characaters)
// This is because there are 1 to ~15 *constant* time
// operations between reading each character from a file.
// in addition, each character will be read at most 2x
// as a result of the push back operation. Hence we conclude that
// there will be between n and 300n constant time operations so the
// algorithm is in the O(n) complexity class.p