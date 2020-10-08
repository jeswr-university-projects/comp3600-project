#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "rdf-types.h"
using namespace std;

/**
 * Parses a single component (URI or object literal)
 * @param inFile an inFile stream
 * @param prefixes the prefixes to be used
 */
string component(ifstream &inFile, Prefixes &prefixes) {
    bool isURI = true;
    bool hasPrefix = false;
    char breakAt = '>';
    char c;
    string val;
    inFile >> c;

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
    while (c != breakAt && !(hasPrefix && (c == ',' || c == ';' || c == '.'))) {
        if (c == ':' && hasPrefix) {
            // This is when the triple has a prefix rather than a full uri
            val = prefixes[val];
        } else {
            val = val + c;
        }

        c = inFile.get(); // We care about whitespace here   
    }

    if (val.length() == 1 && val[0] == 'a') {
        return "http://www.w3.org/1999/02/22-rdf-syntax-ns#type";
    }

    if (c == ',') {
        inFile.putback(c);
    }

    return val;
};

/**
 * Takes the name of a file to be parsed and
 * returns the associated triples 
 * @param file the file name
 */
Triples getTriples(string file) {
    ifstream inFile(file);
    Triples triples = {};
    Prefixes prefixes = {};
    char c;
    inFile >> c;

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

    inFile.putback(c);

    while (inFile.peek() >= 0) {
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
