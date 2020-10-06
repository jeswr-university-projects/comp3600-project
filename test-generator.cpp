#include <vector>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "writer.cpp"
#include <random>

using namespace std;

map<string, string> prefixes = {
    {"room", "http://example.org/room#"},
    {"person", "http://example.org/person#"},
    {"ach", "http://architecture#"}};

/**
 * This file is used to generate test files for the software -
 * command line options include those to 
 */

int main(int argc, char *argv[]){

};

int genPositive(int mean, double var)
{
    std::default_random_engine generator;
    std::normal_distribution<int> distribution(mean, var);

    int out;
    // Generate a number of neighbours that is strictly positive
    while ((out = distribution(generator)) <= 0)
        ;

    return out;
}

struct PositionRoom
{
    int room;
    int x;
    int y;
};

/**
 * 
 * @param rooms - number of rooms to generate
 * @param avgNeighbours - the average number of rooms that are neighbours
 * @params clustering [0 - 1] - 0 no clustering, connections are more or less random; 1 - high clustering will connect to immediate neighbours
 */
Triples generateBuildingTriples(
    int rooms = 15,
    int avgNeighbours = 4,
    double variance = 1.0,
    double clustering = 0.5,
    int exits = 2)
{
    Triples triples;
    vector<int> roomsList;

    // Generate the triples for the room
    for (int i = 0; i < rooms; i++)
    {
        // Create triple for room
        triples.push_back({"http://example.org/room#" + i,
                           "http://www.w3.org/1999/02/22-rdf-syntax-ns#type",
                           "http://architecture#room"});

        triples.push_back({"http://example.org/room#" + i,
                           "http://architecture#width",
                           "\"" + to_string(genPositive(5, 5)) + "\""});

        triples.push_back({"http://example.org/room#" + i,
                           "http://architecture#length",
                           "\"" + to_string(genPositive(10, 5)) + "\""});

        roomsList.push_back(i);
    };

    // Randomly allocate the exists
    for (int i = 0; i < exits; i++)
    {
        int index = rand() % roomsList.size();
        triples.push_back({"http://example.org/room#" + roomsList[index],
                           "http://architecture#hasExit",
                           "\"true\""});
        roomsList.erase(roomsList.begin() + index);
    };

    vector<PositionRoom> positionedRooms;
    int bound = int(sqrt(rooms));

    for (int i = 0; i < rooms; i++)
    {
        positionedRooms.push_back({
            room : i,
            x : rand() % bound,
            y : rand() % bound
        });
    };

    void createPath(int l, int r)
    {

        int distance = int(
            sqrt(
                pow(positionedRooms[l].x - positionedRooms[r].x, 2) +
                pow(positionedRooms[l].y - positionedRooms[r].y, 2)));

        triples.push_back({"http://example.org/room#" + l,
                           "http://architecture#hasPathTo",
                           "http://example.org/room#" + r});
    };

    // For now we just place the paths randomly?
    // Use taken type code from above?

    // TODO: MAKE SURE THAT THEIR IS ALWAYS A PATHWAY TO AN EXIT!!
};

void generatePeopleFile(int noPeople, int noRooms, string file)
{
    Triples triples;

    for (int i = 0; i < noPeople; i++)
    {
        triples.push_back({"http://example.org/person#" + i,
                           "http://architecture#located",
                           "\"" + to_string(rand() % noRooms) + "\""});
    };

    writeTriples(triples, prefixes, file);
};

/**
 * @param rooms - number of rooms to generate
 * @param avgNeighbours - the average number of rooms that are neighbours
 * @params clustering [0-100] - 0 no clustering, connections are more or less random; 100 - high clustering will connect to immediate neighbours
 */
void generateBuildingFile(int rooms, int avgNeighbours, int clustering, string file)
{

    writeTriples(generateBuildingTriples(rooms, avgNeighbours, clustering), prefixes, file);
};

// typedef vector<array<string, 3>>  Triples;

void triplesToFile(vector<array<string, 3>> triples, map<string, string> prefixes){

};