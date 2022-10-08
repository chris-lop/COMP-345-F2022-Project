#include "Map.h"
#include <iostream>
#include <list>
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
    for (auto i : graph->territories)
    {
        cout << *i;
    }

    // Verification...
    // 1. the map is a connected graph
    // 2. continents are connected subgraphs
    // 3. each country belongs to one and only one continent
    cout << "Now Verifying Map validity... \n";
    
    // Create visited vector and mark all the territories as not visited
    vector<bool> visited;
    visited.resize(graph->territories.size(), false);
 
    // Create a queue for BFS and a counter to track the amount of visited territories
    list<Territory> queue;
    int ctr = 0;
 
    // Set node at index 0 as visited and enqueue it into queue
    visited[0] = true;
    queue.push_back(*graph->territories[0]);
 
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
        cout << "Map is a connected graph!";
    }
    else
    {
        cout << "Map is NOT a connected graph!";
    }

    // Calling Destructors
    delete m;
    delete ml;
}