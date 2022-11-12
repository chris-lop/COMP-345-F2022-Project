#include "Map.h"
#include <iostream>
using namespace std;

void testLoadMaps()
{
    // test read of file
    Map *m = new Map();
    MapLoader *ml = new MapLoader();
    Map *m1 = new Map();
    MapLoader *ml1 = new MapLoader();
    Map *m2 = new Map();
    MapLoader *ml2 = new MapLoader();

    auto graph = ml->loadMap("./3D.map");
    auto graph1 = ml1->loadMap("./Mongol Empire 1294.map");
    auto graph2 = ml2->loadMap("./_22_ PAC-MAN.map");

    // CHECK for map validity
    if (graph->territories.size() == 0)
    {
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
    m->validate(graph1->territories);
    m->validate(graph2->territories);

    // Calling Destructors
    delete m;
    delete ml;
    delete m1;
    delete m2;
    delete ml1;
    delete ml2;
    delete graph;
    delete graph1;
    delete graph2;
}