#include <vector>
#include <iostream>
#include <map>
using namespace std;

/**
 * An RDF 3-triple https://www.w3.org/TR/n-triples
 */
typedef array<string, 3> Triple;

/**
 * A collection of RDF 3-triples
 */
typedef vector<Triple> Triples;

/**
 * Used to store the p-o relation of triples
 * in a nested object structure (single predicate)
 */
struct PredicateData
{
    string predicate;
    vector<string> objects;
};

/**
 * Used to store the p-o relation of triples
 * in a nested object structure (many predicates)
 */
typedef vector<PredicateData> PredicatesData;

/**
 * Used to store triples in a nested
 * object structure (single subject)
 */
struct SubjectData
{
    string subject;
    vector<PredicateData> predicates;
};

/**
 * Used to store triples in a nested
 * object structure (many subjects)
 */
typedef vector<SubjectData> SubjectsData;

/**
 * Used to store prefixes
 */
typedef map<string, string> Prefixes;

/**
 * Standard prefixes used in this application
 * TODO: CHECK IF THIS IS AN APPROPRIATE LOCATION
 */
Prefixes defaultPrefixes = {
    {"room", "http://example.org/room#"},
    {"person", "http://example.org/person#"},
    {"ach", "http://architecture#"}};