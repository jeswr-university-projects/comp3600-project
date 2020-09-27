#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

vector<char> breakChar = {'.', ' ', ';', ','};

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Please supply name of .ttl document";
    } else {
        ifstream inFile(argv[1]);
        vector<vector<string>> triples = {};
        map<string, string> prefixes = {};
        string s;
        s = inFile.get();
        cout << s << '\n';
        
        
        return 0;
        
    //     cout << '.';
    //     char c;
    //     inFile >> c;
    //     cout << 'h';
        



    //     // Extract prefixes from file
    //     while (true) {
    //         cout << 'p';

    //         // Ignore whitespace
    //         // while (c == ' ' || c == '\n') {
    //         //     cout << c << '\n';
    //         //     inFile >> c;
                
    //         // }

    //         if (c != '@' ) {
    //             break;
    //         } else {
    //             // Move over word 'prefix'
    //             inFile >> c;
    //             inFile >> c;
    //             inFile >> c;
    //             inFile >> c;
    //             inFile >> c;
    //         }

    //         // Ignore whitespace
    //         while (c == ' ' || c == '\n') {
    //             cout << c << '\n';
    //             inFile >> c;
    //         }

    //         string key;
    //         string val;

    //         while (c != ':') {
    //             key += c;
    //             inFile >> c;
    //         }
    //         inFile >> c;

    //         while (c == ' ' || c == '<') {
    //             inFile >> c;
    //         }

    //         while ( c != '>' ) {
    //             val += c;
    //             inFile >> c;
    //         }

    //         while ( c != '.' ) {
    //             inFile >> c;
    //         }

    //         prefixes[key] = val;

    //         inFile >> c;
    //     }

    //     // Assume that the ttl file does not cotain any syntax errors
    //     while (true) {
    //         string temp;
    //         bool isURI;
    //         bool hasPrefix;

    //         // Skip whitespace
    //         // while (c == ' ') {
    //         //     inFile >> c;
    //         // }

    //         if (c != '"') {
    //                 isURI = true;
    //                 if (c == '<') {
    //                     inFile >> c;
    //                     hasPrefix = false;
    //                 } else {
    //                     hasPrefix = true;
    //                 }
    //         }
    //         int ct = 0;
    //         cout << '\n';
    //         // Assume URI in this loop
    //         while (
    //             //c != ' ' && c!= '.' && c != ';' && c != ',' && c != '<' && 
    //             hasPrefix ? (c != ' ' && ct < 10) : (c != '>')
    //             //c != '>' || (!hasPrefix )
    //             ) {
    //                 inFile.
    //                 ct++;
    //             //cn++;
    //             if (c == ':' && hasPrefix) {
    //                 // This is when the triple has a prefix rather than a full uri
    //                 temp = prefixes[temp];
    //             } else {
    //                 temp = temp + c;
    //             }
    //             inFile >> c;
    //             cout << c << '\n';
    //         }
    //         // return 0;
    //         cout << temp;
    //         break;
    //     }

        
    //     // int i = 0;
    //     char delimiter = '.';
    //     // while (true) {
    //     inFile >> delimiter;
    //         // break;
    //     // };
    //     //cout << triples[i][0];
    // }
    // return 0;
    }
}