#include <vector>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "../rdf-io/writer.cpp"
#include <random>

using namespace std;

/**
 * This file is used to generate test files for the software -
 * command line options include those to 
 */

int main(int argc, char *argv[]){

};

/**
 * Randomly generate a number over a given
 * mean and variance but re-sample if the
 * numner is less than or equal to zero
 * @param mean mean of the distribution to sample over
 * @param variance to sample over
 */
int genPositive(int mean, double variance)
{
    std::default_random_engine generator;
    std::normal_distribution<int> distribution(mean, variance);

    int out;
    // Generate a number of neighbours that is strictly positive
    while ((out = distribution(generator)) <= 0)
    {
    };

    return out;
};

/**
 * Room with x-y coordinate location
 * @param room room ID
 * @param x x-coordinate of room
 * @param y y-coordinate of room
 */
struct PositionRoom
{
    // Room Id
    int room;
    // Room x-coord
    int x;
    // Room y-coord
    int y;
};

struct WeightedValue
{
    int value;
    double weight;
};

typedef vector<WeightedValue> WeightedValues;

/**
 * Generates random double in a given range
 */
double randDouble(double min, double max)
{
    return min + ((double)rand() / RAND_MAX) * (max - min);
};

/**
 * Generates a set of random numbers in a given range 
 * TODO make more efficient using variant of the Fisher-Yates shuffle
 * https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle#Fisher_and_Yates.27_original_method
 * Also has the side-effecting behavior of removing the selected value from the values array so that
 * we can do multiple-non repeated selections
 */
int weightedPick(WeightedValues &values)
{
    double totalWeight = 0;

    for (int i = 0; i < values.size(); i++)
    {
        totalWeight += values[i].weight;
    };

    // Radomly generated point at which to produce a
    // cumulative sum to
    double randCum = randDouble(0, totalWeight);
    int index = -1;

    while (randCum >= 0)
    {
        index++;
        randCum -= values[index].weight;
    };

    int value = values[index].value;

    return value;
};

/**
 * Selects *n* values from a set of m > n random inputs
 * @param values The weighted values
 * @param n the number of values to select
 */
vector<int> weightedPicks(WeightedValues &values, int n)
{
    vector<int> picks;
    // for (int i = 0; i < n; i++)
    // {
    //     // picks.push_back(weightedPicks(values))
    // };

    return picks;
};

/**
 * Converts the distance between 2 rooms and the clustering factor
 * into a weight
 * @param distance Distance between 2 buildings
 * @param clustering factor of hallways
 * @param closest building has 1 order, farthest has noRooms
 * @param noRooms The total number of rooms
 */
double weight(double distance, double clustering, int order, int noRooms, int noNeighbours, double farthestDistance)
{
    // At 1 we are totally dependent on the ordering
    double cluster = order <= noRooms ? 1 : 0;
    // At 0.5 we are totally dependent on the distance
    double distance = 1 - (distance/farthestDistance);
    // At 0 we are totall random
    double random = 1;

    // Weight according to the *clustering* input value
    return clustering < 0.5 
        ?   (distance * clustering + (0.5 - clustering) * random ) * 2 
        :   ( (clustering - 0.5) * cluster + (1 - clustering) * distance ) * 2;
};

/**
 * Generates the triples for a sample building dataset
 * @param rooms number of rooms to generate
 * @param avgNeighbours the average number of rooms that are neighbours
 * @param variance variance in the number of neighbours
 * @param clustering [0 - 1]; 0 no clustering, connections are more or less random; 1 - high clustering will connect to immediate neighbours
 * @param exits the number of exits for the building
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
    int bound = int(sqrt(rooms)); // Bound on room coords

    for (int i = 0; i < rooms; i++)
    {
        positionedRooms.push_back({
            room : i,
            x : rand() % bound,
            y : rand() % bound
        });
    };

    // void createPath(int l, int r)
    // {

    //     int distance = int(
    //         sqrt(
    //             pow(positionedRooms[l].x - positionedRooms[r].x, 2) +
    //             pow(positionedRooms[l].y - positionedRooms[r].y, 2)));

    //     triples.push_back({"http://example.org/room#" + l,
    //                        "http://architecture#hasPathTo",
    //                        "http://example.org/room#" + r});

    //     // TODO: CHECK IF WE WANT TRANSITIVITY - if so uncomment code below
    //     // triples.push_back({"http://example.org/room#" + r,
    //     //                    "http://architecture#hasPathTo",
    //     //                    "http://example.org/room#" + l});
    // };

    // For now we just place the paths randomly?
    // Use taken type code from above?

    // TODO: MAKE SURE THAT THEIR IS ALWAYS A PATHWAY TO AN EXIT!!
};

/**
 * Generates the file for a sample dataset of people
 * @param noPeople to be generated
 * @param noRooms to that people are put into
 * @param file name of file to write to
 */

// TODO: WORK WITH UNEVEN DISTRIBUTIONS OF PEOPLE
void generatePeopleFile(int noPeople, int noRooms, Prefixes prefixes, string file)
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
// void generateBuildingFile(int rooms, int avgNeighbours, int clustering, string file)
// {

//     writeTriples(generateBuildingTriples(rooms, avgNeighbours, clustering), defaultPrefixes, file);
// };

int main() {
    cout << "Tests running ..." << endl;
    cout << "Tests complete ..." << endl << endl;
    cout <<  "Gee .. wasn't that fast, I guess we will have to wait until all the algorithms" << endl;
    cout <<  "are written to see how long this actually takes" << endl;
    return 0;
}