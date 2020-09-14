\section{\fontsize{11}{11} Description}
In the event of a fire in a large populated office space during the year 2020, two primary risk factors are present; the risk of burns from the fire, and the risk of COVID-19 transmission as large crowds exit the building en-masse. The company that owns the building has commissioned an app that is to be installed on each employees phone. In the event of a fire within the building, it will tell employees exactly when and where to move so as to exit the office safely whilst minimizing the likelihood of COVID-19 transmission.

\section{Functionalities}

\begin{itemize}[noitemsep]
    \item {Read the RDF/XML file which contains the map of all rooms and passageways. Each room can have a unique IRI identifier and the \texttt{ex:hasPathTo} predicate indicates that there is a passage leading from room A to room B. Construct and save this graph/region information\footnote{Possible addition instead of having 1 fixed time to evacuate the whole building - Read the RDF/XML file which contains the predicted times at which the fire will start burning in each room and determine escape routes based on this information. If this is the case we could use information about the geometry of the building in conjunction with convex hull.}. The graph can be represented in memory as a hash map. In addition, dynamic metadata such as the \textit{number} of people in each room and \textit{expected} number of infected people in each room could be included.
     }
        
    \item{ 
        Read an RDF/XML file that contains the location of each employee and write (dynamically modify) annotations indicating where they need to move at each timestamp such that the expected number COVID-19 transmissions is minimized whilst all employees are still safely evacuated from the fire. Minimum spanning trees can be used to identify routes that would best spread out the employees (reducing the risk of transmission) and Dijkstra's algorithm can be used to determine the best route through the building on an individual level.
    }
    
    \item{
        There are $n$ rooms available in the nearby hotel quarantine facility. Find the $n$ people most likely to be infected following the evacuation so that they can be quarantined\footnote{Possible extension - additionally find all individuals with $x\%$ probability of infection and alert them via the app that they need to self isolate if they are not already in hotel quarantine.}. This could be best solved using dynamic programming methods to first identify the \textit{routes} that would result in the greatest likelihoods of transmission (this part may involve some modified version of Dijkstra's algorithm) and then match these with residents that traversed these routes (may involve use of hash maps). A basic (fallback) method to do this would be to calculate the likelihood of infection for each resident being infected and add this value along with an identifier for each resident to an AVL tree. We can then efficiently gather the $n$ ids with the highest estimated infection value from the tree. The fallback could still use dynamic programming to recursively calculate the change in expected infection levels across each timestamp.
    }
    
\end{itemize}

\section{Assumptions}

\begin{itemize}[noitemsep]
    \item {
        The rooms and passageways are discrete regions. Time is broken into discrete (integer) units and the time taken to move through a given hallway/room is the same for all employees.
    }
    
    \item {
        The area of each room, and length of each passageway are provided as inputs. The the location of each individual is provided as input.
    }
    \item {
        If a group of individuals are in a room, then every uninfected person has an equal chance of being infected at that point in a time. This probability is a (given) function of the area of the room, number of people in the room and, if known, the expected number of infected individuals within the room.
    }
    \item {
        Escaping the fire in (within a given time) \textit{always} takes precedence over minimizing transmission levels.
    }
\end{itemize}

\section{Potential Issues}

\begin{itemize}[noitemsep]
    \item Running this algorithm with a large number of entities (e.g. $>10000$) may result in additional memory requirements (i.e. $>2$GB of RAM as given in the usage section).
    \item {
        Given that the second functionality is trying to optimize paths for a group of entities rather than for an individual entity, it may not be possible to find the optimal solution using the algorithms taught in this class. If that is the case, we could add the constraint that the app acts as an `agent' for each person which uses Dijkstra's algorithm to determine the best path through the building on a per-entity basis.
    }
\end{itemize}

\section{Usage}
This software is being developed on Linux machine (SMP Debian 4.19.132-1) in C++11. The 64-bit machine being used has a Intel(R) Core(TM) i5-7200U CPU @ 2.50GHz and has 8GB of RAM. We intend for this software to be run on a Linux machine with at least 2GB of RAM.



\end{document}

 Brief description: A software that helps people find the shortest paths that satisfies physical distancing all the way through.
Assumptions:

    The rooms and hallway are discretized into regions. Information about the regions, size, #people allowed per region, #people currently in each region, and connectivity between regions are provided as inputs
    Physical distancing requirement is specified in terms of maximum #people per region
    The number of people in a region does not change between the time a query is made until a valid path is provided and the person executed the path to completion

Functionalities:

    I/O: Read, construct the data structure, and save the region information
    Dynamically modify information about #people in each area
    Given multiple queries in the form of the initial and goal rooms, identify the shortest paths for each query, such that physical distance are always satsified.

Note: When a person move from one area to the next, the #people in relevant regions changes. 



n this milestone, you will need to write a project proposal describing the software application you will develop for the final project. Specifically, you need to submit the following:1.  A description of the software application you will develop, together with assumptions and at least three func-tionalities. You can provide more than three functionalities, but we will mark only three of them. Therefore, if you provided more than three functionalities, please identify three of them that you would like us to mark.As a project proposal, you need to write the description at a level that allows your fellow students in this class to understand the difficulty of the problem. We do understand that you might want to change functionalities as we cover more materials.  You will still beable to update two of the three functionalities in Milestone-2, and to update one of the functionalities in theFinal Deliverables.2.  The programming language you plan to use and whether the software will run on Windows or Linux
