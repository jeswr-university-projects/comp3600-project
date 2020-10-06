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
    int a, b = -1;

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

    // Next we see if we can apply a prefix
    for (map<string, string>::iterator i = prefixes.begin(); i != prefixes.end(); ++i)
    {
        // This is when the namespace matches
        if (value.compare(i->second) >= 0)
        {
            return (i->first) + ":" + value.substr((i->second).length());
        };
    };

    // Otherwise we must have a URI with no prefix
    return "<" + value + ">";
};

void outputSubjectData(SubjectsData &data, map<string, string> prefixes, string file)
{
    ofstream outFile(file);
    
    
    // First the prefixes
    
    

    // Now we output the actual data
    for (int i = 0; i < data.size(); i++)
    {
        SubjectData subj = data[i];
        outFile << valueToString(subj.subject, prefixes) << ' ';

        for (int j = 0; j < subj.predicates.size(); j++)
        {
            PredicateData pred = subj.predicates[j];
            outFile << valueToString(pred.predicate, prefixes) << ' ';

            for (int k = 0; k < pred.objects.size(); k++)
            {
                string obj = pred.objects[k];
                outFile << valueToString(obj, prefixes);

                if (k + 1 < pred.objects.size())
                {
                    outFile << ', ';
                };
            };

            if (j + 1 < pred.objects.size())
            {
                outFile << '; ';
            };
        };

        outFile << " ." << endl;
    };

    outFile.close();
};

int main()
{
    return 0;
};