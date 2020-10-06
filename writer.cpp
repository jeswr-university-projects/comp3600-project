#include <vector>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;
#include <cstdlib>

typedef array<string, 3> Triple;

typedef vector<Triple> Triples;

struct PredicateData
{
    string predicate;
    vector<string> objects;
};

struct SubjectData
{
    string subject;
    vector<PredicateData> predicates;
};

typedef vector<SubjectData> SubjectsData;

/**
 * Takes a set of triples and converts it into
 * a SubjectsData data structure so we can print
 * it more cleanly to a file
 */
SubjectsData triplesToSubjectData(Triples &triples)
{
    vector<SubjectData> data;
    int l = triples.size();
    int a = -1;
    int b = -1;

    for (int i = 0; i < l; i++)
    {
        Triple triple = triples[i];
        string s = triple[0];
        string p = triple[1];
        string o = triple[2];
        vector<PredicateData> predData;

        for (int j = 0; j < data.size(); j++)
        {
            // We already have record of the subject
            if (data[j].subject == s)
            {
                a = j;
                predData = data[j].predicates;
                break;
            };
        };

        // No record of the subject exists yet
        if (a < 0)
        {
            data.push_back({
                subject : s,
                predicates : {{
                    predicate : p,
                    objects : {o}
                }}
            });
        }
        else
        {
            for (int j = 0; j < predData.size(); j++)
            {
                // We already have record of the subject
                if (predData[j].predicate == p)
                {
                    b = j;
                    break;
                };
            };

            if (b < 0)
            {
                data[a].predicates.push_back({
                    predicate : p,
                    objects : {o}
                });
            }
            else
            {
                data[a].predicates[b].objects.push_back(o);
            }
        }
        a = -1;
        b = -1;
    };

    return data;
};

string valueToString(string value, map<string, string> &prefixes)
{
    // Object literal
    if (value[0] == '"')
    {
        return value;
    };

    if (value == "http://www.w3.org/1999/02/22-rdf-syntax-ns#type")
    {
        return "a";
    };

    // Next we see if we can apply a prefix
    for (map<string, string>::iterator i = prefixes.begin(); i != prefixes.end(); ++i)
    {
        // This is when the namespace matches
        if ((value.size() >= (i->second).size()) && (value.substr(0, (i->second).length()) == (i->second)))
        {
            return (i->first) + ":" + value.substr((i->second).length());
        };
    };

    // Otherwise we must have a URI with no prefix
    return "<" + value + ">";
};

void outputSubjectData(SubjectsData data, map<string, string> prefixes, string file)
{
    ofstream outFile(file);

    // First the prefixes
    for (map<string, string>::iterator i = prefixes.begin(); i != prefixes.end(); ++i)
    {
        outFile << "@prefix " << i->first << ": <" << i->second << "> ." << endl;
    };

    if (prefixes.size() > 0)
    {
        outFile << endl;
    }

    // Now we output the actual data
    for (int i = 0; i < data.size(); i++)
    {
        SubjectData subj = data[i];
        outFile << valueToString(subj.subject, prefixes) << ' ';

        for (int j = 0; j < subj.predicates.size(); j++)
        {
            PredicateData pred = subj.predicates[j];
            if (j > 0)
            {
                outFile << "\t";
            }
            outFile << valueToString(pred.predicate, prefixes) << ' ';

            for (int k = 0; k < pred.objects.size(); k++)
            {
                string obj = pred.objects[k];
                outFile << valueToString(obj, prefixes);

                if (k + 1 < pred.objects.size())
                {
                    outFile << ", ";
                };
            };

            if (j + 1 < pred.objects.size())
            {
                outFile << "; " << endl;
            };
        };

        outFile << " ." << endl;

        // Can be improved by putting endl at start of loop as this
        // also handles the spacing from prefixes
        if (subj.predicates.size() > 1 && i + 1 < data.size())
        {
            outFile << endl;
        };
    };

    outFile.close();
};

void writeTriples(Triples triples, map<string, string> prefixes, string file)
{
    outputSubjectData(triplesToSubjectData(triples), prefixes, file);
};

// int main(int argc, char *argv[])
// {
//     Triples triples = {
//         {"http://example.org/Alice", "http://www.w3.org/1999/02/22-rdf-syntax-ns#type", "http://example.org/human"},
//         {"http://example.org/Alice", "http://www.w3.org/1999/02/22-rdf-syntax-ns#type", "http://example.org/agent"},
//         {"http://example.org/Alice", "http://example.org/alive", "\"true\""},
//         {"http://example.org/Bob", "http://www.w3.org/1999/02/22-rdf-syntax-ns#type", "http://example.org/human"},
//         {"http://example.org/Bob", "http://www.w3.org/1999/02/22-rdf-syntax-ns#type", "http://example.org/agent"},
//         {"http://example.org/Bob", "http://example.org/alive", "\"true\""},
//         {"http://test.org/Bob", "http://example.org/alive", "\"true\""},
//     };

//     map<string, string> prefixes = {
//         {"ex", "http://example.org/"}};

//     writeTriples(triples, prefixes, "test-write.ttl");

//     return 0;
// };