#include "hash-map.cpp"
#include "graph-matrix.cpp"
#include "rdf-types.h"
#include <algorithm>
#include <vector>
#include <set>
#include <math.h>
/**
 * Generate the covid risk for each person
 */

struct RoomRisk
{
    RoomRisk(int _n = 0, float _r = 0.0, set<int> _f = {})
    {
        no = _n;
        risk = _r;
        from = _f;
    };

    int no = 0;
    float risk = 0.0;
    set<int> from = {};
};

struct RoomDimensions
{
    RoomDimensions(int _w = 0, int _l = 0)
    {
        width = _w;
        length = _l;
    };
    int width = 0;
    int length = 0;
};

struct IndividualRiskDetails
{
    // IndividualRiskDetails(float _risk = 0.0, int _startLocation = 0)
    // {
    //     risk = _risk;
    //     startLocation = _startLocation;
    // };
    float risk;
    int startLocation;
    friend ostream& operator<<(ostream& os, const IndividualRiskDetails& dt) 
    {
        os << dt.risk << "-" << dt.startLocation;
        return os;
    };
};

struct IndividualAndRisk 
{
    IndividualAndRisk(string _individual = "", float _risk = 0.0)
    {
        risk = _risk;
        individual = _individual;
    };
    
    float risk = 0.0;
    string individual;
    // Since we are using this to determine those *most likely
    // to be exposed to COVID* the most important thing to be
    // sorting by here is risk of infection
    bool operator<(const IndividualAndRisk& ind)
    {   
        return ((this->risk) < ind.risk);
    };
    friend ostream& operator<<(ostream& os, const IndividualAndRisk& dt) 
    {
        os << dt.individual << "-" << dt.risk;
        return os;
    };
};

Map<string, IndividualRiskDetails> personRisks(Triples personTriples, GraphMatrix<string> graph)
{
    int s = personTriples.size() / 3;
    Map<string, IndividualRiskDetails> individuals(s > 0 ? s : 1);

    cout << "inside person risks" << endl;
    cout << "there are " << personTriples.size() << " triples" << endl;
    cout << "there are " << graph.nodeCount() << " nodes" << endl;

    for (Triple t : personTriples)
    {
        cout << t[0] << " " << t[1] << " " << t[2] << endl;
        
        if (t[1] == "http://example.org/risk")
        {
            float risk = stof(t[2]);
            if (individuals.hasKey(t[0]))
            {
                individuals.add(t[0], {risk : risk, startLocation : individuals.get(t[0]).startLocation});
            }
            else
            {
                individuals.add(t[0], {risk : risk, startLocation : -1});
            };
        }
        else if (t[1] == "http://architecture#located")
        {
            if (individuals.hasKey(t[0]))
            {
                individuals.add(t[0], {risk : individuals.get(t[0]).risk, startLocation : graph.nameToId(t[2])});
                // individuals.get(t[0]).risk = graph.nameToId(t[2]);
            }
            else
            {
                individuals.add(t[0], {risk : 0.0, startLocation : graph.nameToId(t[2])});
            };
        };
    };
    return individuals;
};

struct CumulativeRisk {
    CumulativeRisk(float _totalRisk = 0.0, int _no = 1)
    {
        totalRisk = _totalRisk;
        no = _no;
    };
    void operator+(const float &risk)
    {
        totalRisk += risk;
        no += 1;
    };
    float totalRisk = 0.0;
    int no = 1;
};

Map<int, RoomRisk> initRisk(GraphMatrix<string> graph, Map<string, IndividualRiskDetails> &individualRisk)
{
    cout << "-------------------------------------------------------------------------init risk called " << endl;
    cout << individualRisk.size() << endl;
    
    Map<int, CumulativeRisk> risks(graph.nodeCount());
    // Would be equal to the number of people in the file as with the
    // current setup we have exactly 3 people in the file. Obviously
    // this is not really scalable to a larger application - for instance
    // if we wanted to add more data to the persons file - but we don't
    // really care about that here anyway.

    individualRisk.print();

    for (Pair<string, IndividualRiskDetails> r : individualRisk.getPairs())
    {
        cout << "inside for" << endl;
        if (risks.hasKey(r.value.startLocation))
        {
            CumulativeRisk c = risks.get(r.value.startLocation);
            risks.add(r.value.startLocation, CumulativeRisk(c.totalRisk + r.value.risk, c.no + 1));
            // risks.get(r.value.startLocation).push_back(r.value.risk);
        }
        else
        {
            risks.add(r.value.startLocation, CumulativeRisk(r.value.risk));
        };
    };

    // int s = personTriples.size() / 3;
    // Map<string, IndividualRiskDetails> individuals(s > 0 ? s : 1);
    // // risks.reserve(graph.size());

    // for (Triple t : personTriples)
    // {
    //     if (t[1] == "http://example.org/risk")
    //     {
    //         // Get the room that the person is located
    //         // to start off with
    //         int located = graph.nameToId(t[0]);

    //         // Converts string to float
    //         float risk = stof(t[2]);

    //         if (risks.hasKey(located))
    //         {
    //             risks.get(located).push_back(risk);
    //         }
    //         else
    //         {
    //             risks.add(located, {risk});
    //         };

    //         if (individuals.hasKey(t[0]))
    //         {
    //             individuals.get(t[0]).risk = risk;
    //         }
    //         else
    //         {
    //             individuals.add(t[0], IndividualRiskDetails(risk));
    //         };
    //     };
    // };

    Map<int, RoomRisk> roomRisks;

    for (Pair<int, CumulativeRisk> risks : risks.getPairs())
    {

        // float total = 0.0;

        // for (float f : risks.value)
        // {
        //     total += f;
        // };

        roomRisks.add(risks.key, RoomRisk(risks.value.no, ((float)risks.value.totalRisk) / ((float)(risks.value.no)), {risks.key}));
    };

    return roomRisks;
};

/**
 * This is a *heuristic* used to determine the likely
 * risk of catching covid in a room *assuming* that 
 * given individual does *not already* have covid
 */
float roomRisk(int w, int h, int no, float avg)
{
    cout << w << " " << h << " " << no << endl;
    
    
    float density = (float(no - 1)) / ((float)(w * h));
    cout << " density is " << density;
    cout << " avergae is" << avg << endl;
    return density * avg;
};

// float increasedRisk
/**
 * Generates the risk of covid exposure when starting in each room
 * (note that this is a dynamic programming solution and we have)
 * additionally reduced computation time by calculating risk increase by
 * room rather than by individual.
 */
Map<int, float> generateCovidRisk(GraphMatrix<string> &graph, Map<int, RoomRisk> &initRisks, Map<int, int> &nextRoom, Map<int, RoomDimensions> &roomDims)
{
    // Can start with these initialised
    int timestamp = 0;

    cout << endl << endl;
    cout << "generate covid risk called" << endl;
    cout << "the size of initirisks is" << initRisks.size() << endl;

    // Map<int, float> roomRiskAvg;
    // Map<int, int> roomCount;

    Map<int, Map<int, RoomRisk>> transit;
    Map<int, float> exposureRisk;

    for (int i : initRisks.keys())
    {
        exposureRisk.add(i, 0.000000000000000000);
    };

    // Map<int, int> nextRoom;
    // Map<int, int> nextRoomDistance;

    transit.add(0, initRisks);

    cout << "the size of initirisks is" << initRisks.size() << endl;

    while (transit.size() > 0)
    {
        cout << "the transit size is " << transit.size() << endl;
        
        if (transit.hasKey(timestamp))
        {
            Map<int, RoomRisk> data = transit.get(timestamp);
            cout << "inside haskey" << endl;

            for (Pair<int, RoomRisk> p : data.getPairs())
            {
                cout << "inside pair loop" << endl;
                // Note that if this condition is false then we are 
                // in the pathological case where there is no escape
                // path from a particular room
                if (nextRoom.hasKey(p.key))
                {

                
                int next = nextRoom.get(p.key);
                RoomDimensions roomDim = roomDims.get(p.key);
                float risk = roomRisk(roomDim.width, roomDim.length, p.value.no, p.value.risk);

                cout << "------------------------------------------------------------------------------------next is " << next << endl;

                // Updating the risk value
                for (int i : p.value.from)
                {
                    float prevRisk = exposureRisk.get(i);
                    // This works since we have designed the
                    // hash map to ovveride existing values
                    exposureRisk.add(i, prevRisk + (1.0 - prevRisk) * risk);
                    // exposureRisk.add(i, p.value.risk);
                    cout << "----------------------------------------------------------------- updating exposure risk risk:" << risk << " prevrisk:" << prevRisk << endl;
                };

                if (next != -1)
                {
                    int nextTime = timestamp + graph._edgeLength(p.key, next);

                    if (!transit.hasKey(nextTime))
                    {
                        Map<int, RoomRisk> temp;
                        transit.add(nextTime, temp);
                    };

                    // if (!transit.get(nextTime).hasKey(next))
                    // {
                    //     transit.get(nextTime).add(next, RoomRisk());
                    // };

                    RoomRisk prev = transit.get(nextTime).hasKey(next) ? transit.get(nextTime).get(next) : RoomRisk();

                    prev.from.insert(p.value.from.begin(), p.value.from.end());

                    transit.get(nextTime).add(next, RoomRisk(prev.no + p.value.no,
                                                             (prev.risk * ((float(prev.no))) + p.value.risk * (float(p.value.no))) / float(prev.no + p.value.no),
                                                             prev.from));
                };
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

// Map<string, float> generateIndividualrisk(GraphMatrix<string> graph, Map<int, RoomRisk> initRisks, Map<int, int> nextRoom, Map<int, RoomDimensions> roomDims)
// {

// };