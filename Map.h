#include <string>

// edges (paths between territories)
struct edge
{
    int start_ver, end_ver, weight;
};

// nodes (territories)
class Territory
{
    private:
        int val;
        Territory* next;
        // Void pointer to continent
        void *myContinent;

    public:
        // Getters
        int getVal();

        Territory* getNext();

        // Setters
        void setVal(int aVal);

        void setNext(Territory* aTerritory);
};

// Continents
class Continent
{
    private:
        std::string Name;
        int NbTerritories;
        Territory *TerritoryList[];
};

// Map class
class Map
{
    // number of nodes in the graph
    int N;

    // insertNode inserts new nodes into adjacency list from given graph
    Territory* insertNode(int value, Territory* head);

    public:
    Territory **head;

    // Constructor
    Map(edge edges[], int n, int N);

    // Destructor
    ~Map();
};