#include "hash-map.cpp"
#include "graph-matrix.cpp"
#include "rdf-types.h"
#include <vector>
/**
 * Generate the covid risk for each person
 */

struct RoomRisk
{
    int no = 0;
    float risk = 0.0;
    set<int> from;
};

struct RoomDimensions
{
    int width = 0;
    int length = 0;
};

Map<int, RoomRisk> initRisk(GraphMatrix<string> graph, Triples personTriples, Map<string, int> location)
{
    Map<int, vector<float>> risks;
    risks.reserve(graph.size());

    for (Triples t : personTriples)
    {
        if (t[1] == "http://example.org/risk")
        {
            // Get the room that the person is located
            // to start off with
            int located = location.get(t[0]);
            // Converts string to float
            float risk = stof(t[2]);

            if (risks.hasKey(located))
            {
                risks.get(located).push_back(risk);
            }
            else
            {
                risks.add(located, {risk});
            }
        };
    };

    Map<int, roomRisk> roomRisks;

    for (Pair<int, vector<float>> risks : risks.getPairs())
    {
        
        float total = 0.0;

        for (float f : risks.value)
        {
            total += f;
        };
        
        roomRisks.add(risks.key, {
            no : risks.value.size(),
            risk : total / risks.value.size()
        });
    };
};

/**
 * This is a *heuristic* used to determine the likely
 * risk of catching covid in a room *assuming* that 
 * given individual does *not already* have covid
 */
float roomRisk(int w, int h, int no, float avg)
{
    float density = (float(no - 1)) / ((float)(w * h));
    return density * avg;
};

Map<string, int> generateCovidRisk(GraphMatrix<string> graph, Map<int, RoomRisk> initRisks)
{
    // Can start with these initialised
    int timestamp = 0;

    // Map<int, float> roomRiskAvg;
    // Map<int, int> roomCount;

    Map<int, Map<int, RoomRisk>> transit;
    Map<int, float> exposureRisk;

    Map<int, int> nextRoom;
    // Map<int, int> nextRoomDistance;

    while (transit.size() > 0)
    {
        if (transit.hasKey(timestamp))
        {
            Map<int, RoomRisk> data = transit.get(timestamp);

            for (Pair<int, RoomRisk> p : data.getPairs())
            {
                int next = nextRoom.get(p.key);

                for (int i : p.value.from)
                {
                    exposureRisk.add(i, p.value.risk);
                };

                // p.value.no
                // p.value.risk

                if (next != -1)
                {
                    D
                };
            };
            // data[2]
            transit.remove(timestamp);
            timestamp++;
        };
    };

    while (true)
    {
        Map<int, float> roomRiskTemp;
        Map<int, int> roomCountTemp;

        for (int i = 0; i < graph.nodeCount(); i++)
        {
            if
        };
    };

    Map<string, int> risk;
    for (int i = 0;)
};