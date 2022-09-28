#include "Map.cpp"
#include <iostream>
using namespace std;

int main() {
    // Territories for testing
    Territory* t0 = new Territory("Canada", "Americas", new Player(), 10);
    Territory* t1 = new Territory("USA", "Americas", new Player(), 5);
    Territory* t2 = new Territory("Mexico", "Americas", new Player(), 25);
    Territory* t3 = new Territory("Cuba", "Americas", new Player(), 99);
    Territory* t4 = new Territory("France", "Europe", new Player(), 12);
    Territory* t5 = new Territory("England", "Europe", new Player(), 23);
    Territory* t6 = new Territory("Nigeria", "Africa", new Player(), 67);
    Territory* t7 = new Territory("Egypt", "Africa", new Player(), 84);
    Territory* t8 = new Territory("China", "Asia", new Player(), 21);
    Territory* t9 = new Territory("Australia", "Oceania", new Player(), 87);

    //Insert territories into array of territories
    Territory tArray[10];
    tArray[0] = *t0;
    tArray[1] = *t1;
    tArray[2] = *t2;
    tArray[3] = *t3;
    tArray[4] = *t4;
    tArray[5] = *t5;
    tArray[6] = *t6;
    tArray[7] = *t7;
    tArray[8] = *t8;
    tArray[9] = *t9;
    
    // Print territory info
    for (int i = 0; i < 10; i++)
    {   
        cout << "[Territory #" << i <<"] ";
        tArray[i].toString();
    }
    cout << endl;

    // Map Creation
    Map* map = new Map(10);

    // Adding edges between Territories
    map->addEdge(0, 1);
    map->addEdge(0, 4);
    map->addEdge(1, 2);
    map->addEdge(1, 5);
    map->addEdge(2, 3);
    map->addEdge(2, 6);
    map->addEdge(3, 7);
    map->addEdge(4, 5);
    map->addEdge(5, 6);
    map->addEdge(5, 8);
    map->addEdge(6, 7);
    map->addEdge(8, 9);

    // Print Map
    map->toString();
    
    // Validate() Method section
    
    
    // Destructors
    delete map;
    delete t0;
    delete t1;
    delete t2;
    delete t3;
    delete t4;
    delete t5;
    delete t6;
    delete t7;
    delete t8;
    delete t9;
    
}