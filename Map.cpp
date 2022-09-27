#include "Map.h"
#include <iostream>
using namespace std;

//-------------------------------
// TERRITORY CLASS IMPLEMENTATION
//-------------------------------

// Getters
int Territory::getVal()
{
    return this->val;
}

Territory* Territory::getNext()
{
    return this->next;
}

// Setters
void Territory::setVal(int aVal)
{
    this->val = aVal;
}

void Territory::setNext(Territory* aTerritory)
{
    this->next = aTerritory;
}


//-------------------------------
// MAP CLASS IMPLEMENTATION
//-------------------------------

// insertNode inserts new nodes into adjacency list from given graph
Territory* Map::insertNode(int value, Territory* head)
{
    Territory* newTerritory = new Territory;
    newTerritory->setVal(value);
    newTerritory->setNext(head);
    return newTerritory;
}

// Constructor
Map::Map(edge edges[], int n, int N)
{
    // allocate new node
    head = new Territory*[N]();
    this->N = N;
    // initialize head pointer for all vertices
    for (int i = 0; i < N; ++i)
        head[i] = nullptr;

    // construct directed graph by adding edges to it
    for (unsigned i = 0; i < n; i++)
    {
        int start_ver = edges[i].start_ver;
        int end_ver = edges[i].end_ver;
        // insert in the beginning
        Territory* newTerritory = insertNode(end_ver, head[start_ver]);
            
        // point head pointer to new node
        head[start_ver] = newTerritory;
    }
}
// Destructor
Map::~Map()
{
for (int i = 0; i < N; i++)
    delete[] head[i];
    delete[] head;
}

// validate method that checks if map is connected graph, checks if continents are connected subgraphs and checks if each country belongs to one and only one continent
// void validate()
// {}

// print all adjacent vertices of given vertex
void printNeighbours(Territory* ptr, int i)
{
    while (ptr != nullptr)
    {
        cout << "(" << i << ", " << ptr->getVal() << ") ";
        ptr = ptr->getNext();
    }
    cout << endl;
}