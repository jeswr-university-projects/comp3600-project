# COMP 3600 Project

## Usage
The following instructions have been tested on a Debain distribution of Linux.

To compile the project
```
g++ -std=c++11 main.cpp escape_planner
```

To calculate the escape paths for *all* entities in a building
```
escape_planner building_x_architectrue.ttl people_y_building_x.ttl
```

To calculate the escape paths for *specified* entities in a building
```
escape_planner building_x_architectrue.ttl persons_x_building_x.ttl ex:Alice http://example.org/Bob
```

| arg         | Description                                                                                      |
| ----------- | -------------------------------------------------------------------------------------------------|
| p           | Calculate and write paths                                                                        |
| r           | Calculate and write risk of catching COVID - This can only be called *after* -p has been called  |
| s           | Show timing diagnostics                                                                          |

If none are specified, `-pr` is run

## Note on testing files
TODO: Provide some alternatives for IRI's from testing files that can be used to run
TODO: Add information about the size of various testing files - person files etc
TODO: Create a "generate diagonstics function"

## Description
In the event of a fire in a large populated office space during the year 2020, two primary risk factors are present; the risk of burns from the fire, and the risk of COVID-19 transmission as large crowds exit the building en-masse. The company that owns the building has commissioned an app that is to be installed on each employees phone. In the event of a fire within the building, it will tell employees exactly when and where to move so as to exit the office safely whilst minimizing the likelihood of COVID-19 transmission.

## Functionalities
- Read the RDF/XML file which contains the map of all rooms and passageways. Each room can have a unique IRI identifier and the `ex:hasPathTo` predicate indicates that there is a passage leading from room A to room B. Construct and save this graph/region information\footnote{Possible addition instead of having 1 fixed time to evacuate the whole building - Read the RDF/XML file which contains the predicted times at which the fire will start burning in each room and determine escape routes based on this information. If this is the case we could use information about the geometry of the building in conjunction with convex hull.}. The graph can be represented in memory as a hash map. In addition, dynamic metadata such as the *number* of people in each room and *expected* number of infected people in each room could be included.
- Read an RDF/XML file that contains the location of each employee and write (dynamically modify) annotations indicating where they need to move at each timestamp such that the expected number COVID-19 transmissions is minimized whilst all employees are still safely evacuated from the fire. Minimum spanning trees can be used to identify routes that would best spread out the employees (reducing the risk of transmission) and Dijkstra's algorithm can be used to determine the best route through the building on an individual level.
- There are `n` rooms available in the nearby hotel quarantine facility. Find the `n` people most likely to be infected following the evacuation so that they can be quarantined\footnote{Possible extension - additionally find all individuals with `x%` probability of infection and alert them via the app that they need to self isolate if they are not already in hotel quarantine.}. This could be best solved using dynamic programming methods to first identify the *routes* that would result in the greatest likelihoods of transmission (this part may involve some modified version of Dijkstra's algorithm) and then match these with residents that traversed these routes (may involve use of hash maps). A basic (fallback) method to do this would be to calculate the likelihood of infection for each resident being infected and add this value along with an identifier for each resident to an AVL tree. We can then efficiently gather the `n` ids with the highest estimated infection value from the tree. The fallback could still use dynamic programming to recursively calculate the change in expected infection levels across each timestamp.

## Assumptions
- The rooms and passageways are discrete regions. Time is broken into discrete (integer) units and the time taken to move through a given hallway/room is the same for all employees.
- The area of each room, and length of each passageway are provided as inputs. The the location of each individual is provided as input.
- If a group of individuals are in a room, then every uninfected person has an equal chance of being infected at that point in a time. This probability is a (given) function of the area of the room, number of people in the room and, if known, the expected number of infected individuals within the room.
- Escaping the fire in (within a given time) \textit{always} takes precedence over minimizing transmission levels.

## Potential Issues
- Running this algorithm with a large number of entities (e.g. `>10000`) may result in additional memory requirements (i.e. `>2`GB of RAM as given in the usage section).
- Given that the second functionality is trying to optimize paths for a group of entities rather than for an individual entity, it may not be possible to find the optimal solution using the algorithms taught in this class. If that is the case, we could add the constraint that the app acts as an 'agent' for each person which uses Dijkstra's algorithm to determine the best path through the building on a per-entity basis.

## Usage
This software is being developed on Linux machine (SMP Debian 4.19.132-1) in C++11. The 64-bit machine being used has a Intel(R) Core(TM) i5-7200U CPU @ 2.50GHz and has 8GB of RAM. We intend for this software to be run on a Linux machine with at least 2GB of RAM.
