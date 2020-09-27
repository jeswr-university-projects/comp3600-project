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
        char c;
        inFile >> c;
        
        // Extract prefixes from file
        while (true) {

            if (c != '@' ) {
                break;
            } else {
                // Move over word 'prefix'
                inFile >> c;
                inFile >> c;
                inFile >> c;
                inFile >> c;
                inFile >> c;
                inFile >> c;
                inFile >> c;
            }

            string key;
            string val;

            while (c != ':') {
                key += c;
                inFile >> c;
            }

            inFile >> c;
            inFile >> c;

            while ( c != '>' ) {
                val += c;
                inFile >> c;
            }

            inFile >> c;
            inFile >> c;
            cout << key << ' ' << val << '\n';
            prefixes[key] = val;
        }
        
        // Assume that the ttl file does not cotain any syntax errors
        while (true) {
            string s;
            string p;
            string o;
            bool isURI = false;
            bool hasPrefix = false;

            // Skip whitespace
            if (c != '"') {
                    isURI = true;
                    if (c == '<') {
                        inFile >> c;
                        hasPrefix = false;
                    } else {
                        hasPrefix = true;
                    }
            }


            // Assume URI in this loop
            while ( 
                hasPrefix ? (c != ' ') : (c != '>')
                ) {
                if (c == ':' && hasPrefix) {
                    // This is when the triple has a prefix rather than a full uri
                    s = prefixes[s];
                } else {
                    s = s + c;
                }
                c = inFile.get(); // We care about whitespace here
            }

            inFile >> c;

            // Assume URI in this loop
            while ( 
                hasPrefix ? (c != ' ') : (c != '>')
                ) {
                if (c == ':' && hasPrefix) {
                    // This is when the triple has a prefix rather than a full uri
                    p = prefixes[p];
                } else {
                    p = p + c;
                }
                c = inFile.get(); // We care about whitespace here
            }

            if (s.length() == 1 && s[0] == 'a') {
                //s = 
            }

            if (p.length() == 1 && s[0] == 'a') {

            }

            if (o.length() == 1 && s[0] == 'a') {

            }



            triples.push_back({s, p, o});


            break;
        }

        
        // int i = 0;
        char delimiter = '.';
        // while (true) {
        inFile >> delimiter;
            // break;
        // };
        //cout << triples[i][0];
    }
    return 0;
}