#include "Map.h"
#include <iostream>
using namespace std;

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
    m->validate(graph->territories);

    // Calling Destructors
    delete m;
    delete ml;
    delete graph;
}