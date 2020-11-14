#include "hash-map.cpp"
#include "graph-matrix.cpp"
#include "rdf-types.h"
#include <algorithm>
#include <vector>
#include <set>
/**
 * Generate the covid risk for each person
 */

struct RoomRisk
{
    int no = 0;
    float risk = 0.0;
    set<int> from = {};
};

struct RoomDimensions
{
    int width = 0;
    int length = 0;
};

Map<int, RoomRisk> initRisk(GraphMatrix<string> graph, Triples personTriples)
{
    Map<int, vector<float>> risks(graph.nodeCount());
    // risks.reserve(graph.size());

    for (Triple t : personTriples)
    {
        if (t[1] == "http://example.org/risk")
        {
            // Get the room that the person is located
            // to start off with
            int located = graph.nameToId(t[0]);
            
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

    Map<int, RoomRisk> roomRisks;

    for (Pair<int, vector<float>> risks : risks.getPairs())
    {
        
        float total = 0.0;

        for (float f : risks.value)
        {
            total += f;
        };
        
        roomRisks.add(risks.key, {
            no : risks.value.size(),
            risk : total / risks.value.size(),
            from : {risks.key}
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

// float increasedRisk
/**
 * Generates the risk of covid exposure when starting in each room
 * (note that this is a dynamic programming solution and we have)
 * additionally reduced computation time by calculating risk increase by
 * room rather than by individual.
 */
Map<int, float> generateCovidRisk(GraphMatrix<string> graph, Map<int, RoomRisk> initRisks, Map<int, int> nextRoom, Map<int, RoomDimensions> roomDims)
{
    // Can start with these initialised
    int timestamp = 0;

    // Map<int, float> roomRiskAvg;
    // Map<int, int> roomCount;

    Map<int, Map<int, RoomRisk>> transit;
    Map<int, float> exposureRisk;

    for (int i : transit.keys())
    {
        exposureRisk.add(i, 0.0);
    };

    // Map<int, int> nextRoom;
    // Map<int, int> nextRoomDistance;

    transit.add(0, initRisks);

    while (transit.size() > 0)
    {
        if (transit.hasKey(timestamp))
        {
            Map<int, RoomRisk> data = transit.get(timestamp);

            for (Pair<int, RoomRisk> p : data.getPairs())
            {
                int next = nextRoom.get(p.key);
                RoomDimensions roomDim = roomDims.get(p.key);
                float risk = roomRisk(roomDim.width, roomDim.length, p.value.no, p.value.risk);

                // Updating the risk value
                for (int i : p.value.from)
                {
                    float prevRisk = exposureRisk.get(i);
                    // This works since we have designed the
                    // hash map to ovveride existing values
                    exposureRisk.add(i, prevRisk + (1.0 - prevRisk) * risk);
                    // exposureRisk.add(i, p.value.risk);
                };

                // p.value.no
                // p.value.risk

                if (next != -1)
                {
                    int nextTime = timestamp + graph._edgeLength(p.key, next);
                    
                    if (!transit.hasKey(nextTime))
                    {
                        Map<int, RoomRisk> temp;
                        transit.add(nextTime, temp);
                    };

                    if (!transit.get(nextTime).hasKey(next))
                    {
                        transit.get(nextTime).add(next, {
                            no : 0,
                            risk : 0.0,
                            from : {}
                        });
                    };

                    RoomRisk prev = transit.get(nextTime).get(next);

                    prev.from.insert(p.value.from.begin(), p.value.from.end());

                    transit.get(nextTime).add(next, {
                        no : prev.no + p.value.no,
                        risk : (prev.risk * ((float(prev.no))) + p.value.risk * (float(p.value.no))) / float(prev.no + p.value.no),
                        from : prev.from
                    });

                };
            };
            // data[2]
            transit.remove(timestamp);
            timestamp++;
        };
    };

    return exposureRisk;
    // while (true)
    // {
    //     Map<int, float> roomRiskTemp;
    //     Map<int, int> roomCountTemp;

    //     for (int i = 0; i < graph.nodeCount(); i++)
    //     {
    //         if
    //     };
    // };

    // Map<string, int> risk;
    // for (int i = 0;)
};



Map<string, float> generateIndividualrisk(GraphMatrix<string> graph, Map<int, RoomRisk> initRisks, Map<int, int> nextRoom, Map<int, RoomDimensions> roomDims)
{
    
};