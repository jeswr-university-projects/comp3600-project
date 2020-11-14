#pragma once
#include <iostream>
#include <fstream>
#include "../rdf-types.h"
using namespace std;

/**
 * Takes a set of triples and converts it into
 * a SubjectsData data structure so we can print
 * it more cleanly to a file
 */
SubjectsData triplesToSubjectData(Triples &triples)
{
    SubjectsData data;
    int l = triples.size();
    int a = -1;
    int b = -1;

    for (int i = 0; i < l; i++)
    {
        Triple triple = triples[i];
        string s = triple[0];
        string p = triple[1];
        string o = triple[2];
        PredicatesData predData;

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
            };
        };
        a = -1;
        b = -1;
    };

    return data;
};

/**
 * Converts a value in an RDF triple to string of the
 * correct format to write to .ttl file.
 * @param value string to be prepared for file
 * @param prefixes prefixes used in the file
 */
string valueToString(string value, Prefixes &prefixes)
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
    for (pair<string, string> p : prefixes)
    {
        // This is when the namespace matches
        if ((value.size() >= p.second.size()) && (value.substr(p.second.length()) == p.second))
        {
            return p.first + ":" + value.substr(p.second.length());
        };
    };

    // Otherwise we must have a URI with no prefix
    // TODO: FIX THIS IN OTHER FILE
    return "<" + value + ">";
};

/**
 * Takes data in the format of SubjectsData and writes it to a file
 * @param data takes a set of triples in SubjectsData format
 * @param prefies used in the file
 * @param file name of file to be generated
 */
void outputSubjectData(SubjectsData data, Prefixes prefixes, string file)
{
    ofstream outFile(file);

    for (pair<string, string> p : prefixes)
    {
        outFile << "@prefix " << p.first << ": <" << p.second << "> ." << endl;
    };

    // Now we output the actual data
    for (SubjectData subj : data)
    {
        // outFile << endl;
        outFile << endl
                << valueToString(subj.subject, prefixes) << " ";
        bool firstPred = true;
        for (PredicateData pred : subj.predicates)
        {
            if (!firstPred)
            {
                outFile << ";\n\t";
            };
            firstPred = false;
            outFile << valueToString(pred.predicate, prefixes) << " ";
            bool firstObj = true;
            for (string obj : pred.objects)
            {
                if (!firstObj)
                {
                    outFile << ", ";
                };
                firstPred = false;
                outFile << valueToString(obj, prefixes);
            };
        };
        outFile << " .\n";
    };

    outFile.close();
};

/**
 * Writes triples to a file
 * @param triples triples to write to file
 * @param prefixes prefixes to use in the file
 * @param file name of the file
 */
void writeTriples(Triples triples, Prefixes prefixes, string file)
{
    outputSubjectData(triplesToSubjectData(triples), prefixes, file);
};