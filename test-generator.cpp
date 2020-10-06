#include <vector>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

/**
 * This file is used to generate test files for the software -
 * command line options include those to 
 */

int main(int argc, char *argv[]) 
{

};

/**
 * 
 * @param rooms - number of rooms to generate
 * @param avgNeighbours - the average number of rooms that are neighbours
 * @params clustering [0-100] - 0 no clustering, connections are more or less random; 100 - high clustering will connect to immediate neighbours
 */
void generateBuildingFile(int rooms, int avgNeighbours, int clustering)
{
    // TODO: MAKE SURE THAT THEIR IS ALWAYS A PATHWAY TO AN EXIT!!
    
};

typedef vector<array<string, 3>>  Triples;

void triplesToFile(vector<array<string, 3>> triples, map<string, string> prefixes) {

};