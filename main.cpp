#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "rdf-types.h"
using namespace std;

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
}

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
        }
        inFile >> c;

        while ( (c = inFile.get()) != '>' ) {
            prefixes[key] += c;
        }
        inFile >> c >> c;
    }

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
            }
            o = component(inFile, prefixes);
            triples.push_back({s, p, o});
            inFile >> c;
        }
    }
    return triples;
}


int main(int argc, char *argv[]) {

    
    vector<int> v = {};
    // return 1;
    v[10] = 5;

    return v[10];

    return 0;
    if (argc < 2) {
        cout << "Please supply name of .ttl document";
    } else {
        Triples triples = getTriples(argv[1]);
        for (int i = 0; i < triples.size(); i++) {
            cout << triples[i][0] << ' ' << triples [i][1] << ' ' << triples[i][2] << '\n';
        }
    }
    return 0;
}


// string component(ifstream &inFile, map<string, string> &prefixes) {
//     bool isURI = true;
//     bool hasPrefix = false;
//     char breakAt = '>';
//     char c;
//     string val;
//     inFile >> c;

//     if (c == '<') {
//         inFile >> c;
//     } else if (c == '"') {
//         inFile >> c;
//         bool isURI = false;
//         breakAt = '"';
//     } else {
//         hasPrefix = true;
//         breakAt = ' ';
//     }

//     // Assume URI in this loop
//     while (c != breakAt && !(hasPrefix && (c == ',' || c == ';' || c == '.'))) {
//         if (c == ':' && hasPrefix) {
//             // This is when the triple has a prefix rather than a full uri
//             val = prefixes[val];
//         } else {
//             val = val + c;
//         }

//         c = inFile.get(); // We care about whitespace here
        
//     }

//     cout << 'x' << ' ' << c << '\n';

//     if (val.length() == 1 && val[0] == 'a') {
//         return "http://www.w3.org/1999/02/22-rdf-syntax-ns#type";
//     }

//     return val;
// }

// vector<vector<string>> getTriples(string file) {
//     ifstream inFile(file);
//     vector<string[3]> triples = {};
//     map<string, string> prefixes = {};
//     char c;
//     inFile >> c;

//     while (c == '@') {
//         // Skips over the expected word 'prefix'
//         inFile.seekg(inFile.tellg() + (std::streampos)6) >> c;
//         string key;

//         while ( (c = inFile.get()) != ':') {
//             key += c;
//         }

//         inFile >> c >> c;

//         while ( (c = inFile.get()) != '>' ) {
//             prefixes[key] += c;
//         }

//         inFile >> c >> c;
//     }

//     inFile.putback(c);

//     while (!inFile.eof()) {
//         string s = component(inFile, prefixes);
//         string p = component(inFile, prefixes);
//         string o = component(inFile, prefixes);
//         triples.push_back({s, p, o});
//         inFile >> c;


//         while (c == ';' || c == ',') {
//             if (c == ';') {
//                 p = component(inFile, prefixes);
//             }
//             o = component(inFile, prefixes);
//             triples.push_back({s, p, o});
//             inFile >> c;
//         }
        
//         if (triples.size() == 6) {
//             break;
//         }
        
//     }
//     return triples;
// }


// int main(int argc, char *argv[]) {
//     if (argc < 2) {
//         cout << "Please supply name of .ttl document";
//     } else {
//         vector<vector<string>> triples = getTriples(argv[1]);
//         for (int i = 0; i < triples.size(); i++) {
//             cout << triples[i][0] << ' ' << triples [i][1] << ' ' << triples[i][2] << '\n';
//         }
//     }
//     ret


// ifstream inFile(argv[1]);
//         vector<vector<string>> triples = {};
//         map<string, string> prefixes = {};
//         char c;
               
//         // Extract prefixes from file
//         while (true) {
//             inFile >> c;
//             if (c != '@') {
//                 inFile.putback(c);
//                 break;
//             } else {
//                 // Move over word 'prefix'
//                 inFile >> c;
//                 inFile >> c;
//                 inFile >> c;
//                 inFile >> c;
//                 inFile >> c;
//                 inFile >> c;
//                 inFile >> c;
//             }

//             string key;
//             string val;

//             while (c != ':') {
//                 key += c;
//                 inFile >> c;
//             }

//             inFile >> c;
//             inFile >> c;

//             while ( c != '>' ) {
//                 val += c;
//                 inFile >> c;
//             }

//             inFile >> c;
//             prefixes[key] = val;
//         }
        
//         // Assume that the ttl file does not cotain any syntax errors
//         while (true) {
//             cout << 'a';
//             string s = component(inFile, prefixes);
//             cout << 'b';
//             string p = component(inFile, prefixes);
//             cout << 'c';
//             string o = component(inFile, prefixes);
//             triples.push_back({s, p, o});
//             cout << 1;
//             c = inFile.get();
//             while (c == ' ') {
//                 c = inFile.get();
//             }
//             cout << 2;
            
//             while (c == ';' || c == ',') {

//                 if (c == ';') {
//                     string p = component(inFile, prefixes);
//                 }
//                 string o = component(inFile, prefixes);
//                 triples.push_back({s, p, o});

//                 // cout << 1 << c << '\n';
//                 c = inFile.get();
//                 // cout << 2 << c << '\n';
//                 while (c == ' ') {
//                     c = inFile.get();
//                 }
//                 // cout << 3 << c << '\n';
                

//                 if (c != '.' && c != ';' && c != ',') {
//                     // cout << c << '\n';
//                 }
//                 cout << 3;

//             }

//             cout << 4;

//             cout << c << '\n';
//             if (c != '.') {
//                 break;
//             }
//             // break;
//         }
//         inFile.close();
//         cout << triples.size();
//         cout << triples[0][0] << ' ' << triples[0][1] << ' ' << triples[0][2] << '\n';
//         cout << triples[1][0] << ' ' << triples[1][1] << ' ' << triples[1][2] << '\n';
//         cout << triples[2][0] << ' ' << triples[2][1] << ' ' << triples[2][2] << '\n';
//     }
            
            
            // string s;
            // string p;
            // string o;
            // char delimeter;
            // bool isURI = true;
            // bool hasPrefix = false;
            // char breakAt = '>';

            // if (c == '<') {
            //     inFile >> c;
            // } else if (c == '"') {
            //     inFile >> c;
            //     bool isURI = false;
            //     breakAt = '"';
            // } else {
            //     hasPrefix = true;
            //     breakAt = ' ';
            // }

            // // Assume URI in this loop
            // while (c != breakAt) {
            //     if (c == ':' && hasPrefix) {
            //         // This is when the triple has a prefix rather than a full uri
            //         s = prefixes[s];
            //     } else {
            //         s = s + c;
            //     }
            //     c = inFile.get(); // We care about whitespace here
            // }

            // inFile >> c;

            // // Assume URI in this loop
            // while ( 
            //     hasPrefix ? (c != ' ') : (c != '>')
            //     ) {
            //     if (c == ':' && hasPrefix) {
            //         // This is when the triple has a prefix rather than a full uri
            //         p = prefixes[p];
            //     } else {
            //         p = p + c;
            //     }
            //     c = inFile.get(); // We care about whitespace here
            // }

            // inFile >> c;

            // if (c == '"') {
            //     while ( 
            //     hasPrefix ? (c != ' ') : (c != '>')
            //     ) {
            //     if (c == ':' && hasPrefix) {
            //         // This is when the triple has a prefix rather than a full uri
            //         o = prefixes[o];
            //     } else {
            //         o = o + c;
            //     }
            //     c = inFile.get(); // We care about whitespace here
            // }
            // } else {
            //     while ( 
            //         c != '"'
            //     ) {
            //     o = o + c;
            //     c = inFile.get(); // We care about whitespace here
            //     }
            // }
          
            // if (p.length() == 1 && s[0] == 'a') {
            //     //p = 'http://www.w3.org/1999/02/22-rdf-syntax-ns#type';
            // }

            // triples.push_back({s, p, o});

            // // inFile >> delimeter;

            // break;