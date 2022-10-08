#include "Map.h"
#include <iostream>
#include <list>
#include <map>
using namespace std;

int searchResult(std::vector<Territory *> tList, Territory t)
{
    int index = -1;
    for (int i = 0; i < tList.size(); i++)
    {   
        string s1 = *tList[i]->getTerritoryName();
        string s2 = *t.getTerritoryName();

        if (s1 ==  s2)
        {
            index = i;
            break;
        }
    }
    return index;
}

void testLoadMaps()
{
    // test read of file
    Map *m = new Map();
    MapLoader *ml = new MapLoader();

    auto graph = ml->loadMap("./3D.map");
    // CHECK for map validity
    if (graph->territories.size() == 0) {
        std::cerr << "### ERROR ###\nNo territories loaded from file\n";
        return;
    }
    for (auto i : graph->territories)
    {
        cout << *i;
    }

    // Verification...
    // 1. the map is a connected graph
    // 2. continents are connected subgraphs
    // 3. each country belongs to one and only one continent
    cout << "Now Verifying Map validity... \n";

    //----------------------------//
    // VERIFYING CONDITION #1     //
    //----------------------------//

    // Create visited vector and mark all the territories as not visited
    vector<bool> visited;
    visited.resize(graph->territories.size(), false);
 
    // Create a queue for BFS and a counter to track the amount of visited territories
    list<Territory> queue;
    int ctr = 0;
 
    // Set node at index 0 as visited and enqueue it into queue
    visited[0] = true;
    queue.push_back(*graph->territories[0]);
    
    // Start of BFS
    while(!queue.empty())
    {
        // Dequeue territory from queue
        Territory t = queue.front();
        queue.pop_front();

        // Get all adjacent territories of the dequeued territory t. If a adjacent has not been visited, then mark it visited and enqueue it
        for (auto adjacent: t.AdjTerritories)
        {
            int index = searchResult(graph->territories, adjacent);
            if (!visited[index])
            {
                visited[index] = true;
                queue.push_back(adjacent);
            }
        }
    }

    // Search through visited vector and increase couter to count amount of territories visited
    for (int i = 0; i < visited.size(); i++)
    {
        if (visited[i] == true)
        {
            ctr++;
        }
    }

    // If the counter is equal to the amount of territories in the graph, then the graph is a connected graph.
    // Else, the graph is NOT a connected graph.
    if (ctr == graph->territories.size())
    {
        cout << "Map is a connected graph!\n";
    }
    else
    {
        cout << "Map is NOT a connected graph!\n";
    }

    //----------------------------//
    // VERIFYING CONDITION #2     //
    //----------------------------//

    // Create Multimap to find number of continents and territories per continent and a simple map to store final result
    multimap<string, int> continents;
    map<string, int> continentList;
    ctr = 0;

    // For each territory, insert the amount
    for (Territory *aTerritory : graph->territories)
    {
        continents.insert(pair<string, int>(*aTerritory->getContinent(), ctr));
        ctr++;
    }

   // Insert each continent along with its number of territories in a <string, int> vector
   for(multimap<string,int>::iterator it = continents.begin(), end = continents.end(); it != end; it = continents.upper_bound(it->first))
   {
    continentList.insert(pair<string, int>(it->first, continents.count(it->first)));
   }


    // Create visited2 vector and mark all the territories as not visited
    vector<bool> visited2;
 
    // Create a queue2 for BFS and a counter2 to track the amount of visited territories
    list<Territory> queue2;
    int ctr2;

    // Create a Territory ptr to point to starting territory for BFS
    Territory* startingTerritory;

    // Start of Check for Validation of #2

    // For each unique continent...
    for (auto pair : continentList) {
        // Resize visited2 vector to number of territories in map
        visited2.resize(graph->territories.size(), false);

        // Set all values in visited2 to false
        for (auto i : visited2) {
            i = false;
        }

        // Set ctr2 equal to 0
        ctr2 = 0;

        // Find the first territory in territories list that belongs to the current continent
        string currentContinent = pair.first;

        for (Territory *aTerritory : graph->territories)
        {
            if (*aTerritory->getContinent() == currentContinent)
            {
                startingTerritory = aTerritory;
                break;
            }
        }

        // Set node at index 0 as visited and enqueue it into queue
        int anIndex = searchResult(graph->territories, startingTerritory);
        visited2[anIndex] = true;
        queue2.push_back(*startingTerritory);

        // Start of BFS
        while(!queue2.empty())
        {
            // Dequeue territory from queue
            Territory t = queue2.front();
            queue2.pop_front();

            // Get all adjacent territories of the dequeued territory t. If a adjacent has not been visited, then mark it visited and enqueue it
            for (auto adjacent: t.AdjTerritories)
            {
                if (*adjacent->getContinent() == currentContinent)
                {
                    int index = searchResult(graph->territories, adjacent);
                    if (!visited2[index])
                    {
                        visited2[index] = true;
                        queue2.push_back(adjacent);
                    }
                }
            }
        }

        // Search through visited vector and increase couter to count amount of territories visited
        for (int i = 0; i < visited2.size(); i++)
        {
            if (visited2[i] == true)
            {
                ctr2++;
            }
        }

        // If the counter is equal to the amount of territories in the graph, then the graph is a connected graph.
        // Else, the graph is NOT a connected graph.
        if (ctr2 == pair.second)
        {
            cout << "Continent " << currentContinent << " is a connected subgraph!\n";
        }
        else
        {
            cout << "Continent " << currentContinent << " is NOT a connected subgraph!\n";
        }
    }
    
        
    // Calling Destructors
    delete m;
    delete ml;
}