#include "Map.h"
#include "Player.h"
#include <iostream>
#include <string.h>
#include <vector>
#include <list>
#include <map>
using namespace std;


// ------------------------------ //
// TERRITORY CLASS IMPLEMENTATION //
// ------------------------------ //

// Default Constructor
Territory::Territory()
{
    this->TerritoryName = new string("default territory");
    this->continent = new string("default continent");
    this->territoryOwner = new Player();
    this->armyAmount = new int(0);
    this->AdjTerritories = vector<Territory *>{};
}

// Parameterized Constructor
Territory::Territory(string *name, string *continent, vector<Territory *> territories, Player *player, int *army)
{
    this->TerritoryName = name;
    this->continent = continent;
    this->AdjTerritories = territories;
    this->territoryOwner = player;
    this->armyAmount = army;
}

// Copy Constructor
Territory::Territory(const Territory *territory)
{
    this->TerritoryName = territory->TerritoryName;
    this->continent = territory->continent;
    this->territoryOwner = territory->territoryOwner;
    this->armyAmount = territory->armyAmount;
    this->AdjTerritories = territory->AdjTerritories;
}

// Assignment Operator
Territory &Territory::operator=(const Territory &territory)
{
    this->TerritoryName = territory.TerritoryName;
    this->continent = territory.continent;
    this->territoryOwner = territory.territoryOwner;
    this->armyAmount = territory.armyAmount;
    return *this;
}

// Destructor
Territory::~Territory()
{
    territoryOwner = NULL;

}

// Getter for TerritoryName
string *Territory::getTerritoryName()
{
    return TerritoryName;
}

// Setter for TerritoryName
void Territory::setTerritoryName(string *newName)
{
    this->TerritoryName = newName;
}

// Getter for Continent
string *Territory::getContinent()
{
    return continent;
}

// Setter for Continent
void Territory::setContinent(string *newContinent)
{
    this->continent = newContinent;
}

// Getter for TerritoryOwner
Player *Territory::getTerritoryOwner()
{
    return territoryOwner;
}

// Setter for TerritoryOwner
void Territory::setTerritoryOwner(Player *newPlayer)
{
    this->territoryOwner = newPlayer;
}

// Getter for Army
int *Territory::getArmy()
{
    return armyAmount;
}

// Setter for Army
void Territory::setArmy(int *newAmount)
{
    this->armyAmount = newAmount;
}

vector<Territory *> Territory::getAdjTerritories() {
    return AdjTerritories;
}

void Territory::setAdjTerritories(vector<Territory *> newAdjacent) {
    AdjTerritories = newAdjacent;
}

// operator<<
ostream& operator<<(ostream& strm, const Territory& territory) {
        strm << "Name: " << *(territory.TerritoryName)
         << "| Continent: " << *(territory.continent) << " "
         << "| Owner: " << territory.territoryOwner->get_name() << " "
         << "| Army: " << *(territory.armyAmount)
         << "| Adjacent territories: " << endl;

    for (auto i : territory.AdjTerritories)
    {
        strm << " [" << *i->TerritoryName << "] ";
    }
    strm << "\n"
         << endl;
    return strm;    
}

// ------------------------ //
// MAP CLASS IMPLEMENTATION //
// ------------------------ //

// Default Constructor
Map::Map()
{
    this->TerritoryNb = 0;
}

// Parameterized Constructor
Map::Map(int TerritoryNb)
{
    this->TerritoryNb = TerritoryNb;
}

// Copy Constructor
Map::Map(const Map *map)
{
    this->TerritoryNb = map->TerritoryNb;
}

// Assignment Operator
Map& Map::operator=(const Map& map)
{
    this->TerritoryNb = map.TerritoryNb;
    return *this;
}

// Destructor
Map::~Map()
{
    //the map loader deletes territories
}

//search method to find index of the territory in the territory vector
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

//validate  method to validate map
void Map::validate(vector<Territory *> territories)
{
    cout << "Now Verifying Map validity... \n";

    //----------------------------//
    // VERIFYING CONDITION #1     //
    //----------------------------//

    // Create visited vector and mark all the territories as not visited
    vector<bool> visited;
    visited.resize(territories.size(), false);

    // Create a queue for BFS and a counter to track the amount of visited territories
    list<Territory> queue;
    int ctr = 0;

    // Set node at index 0 as visited and enqueue it into queue
    visited[0] = true;
    queue.push_back(*territories[0]);
    
    // Start of BFS
    while(!queue.empty())
    {
        // Dequeue territory from queue
        Territory t = queue.front();
        queue.pop_front();

        // Get all adjacent territories of the dequeued territory t. If a adjacent has not been visited, then mark it visited and enqueue it
        for (auto adjacent: t.AdjTerritories)
        {
            int index = searchResult(territories, adjacent);
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
    if (ctr == territories.size())
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
    for (Territory *aTerritory : territories)
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
        visited2.resize(territories.size(), false);

        // Set all values in visited2 to false
        for (auto i : visited2) {
            i = false;
        }

        // Set ctr2 equal to 0
        ctr2 = 0;

        // Find the first territory in territories list that belongs to the current continent
        string currentContinent = pair.first;

        for (Territory *aTerritory : territories)
        {
            if (*aTerritory->getContinent() == currentContinent)
            {
                startingTerritory = aTerritory;
                break;
            }
        }

        // Set node at index 0 as visited and enqueue it into queue
        int anIndex = searchResult(territories, startingTerritory);
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
                    int index = searchResult(territories, adjacent);
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
    
    //----------------------------//
    // VERIFYING CONDITION #3     //
    //----------------------------//

    // Set all values in visited2 to false and set ctr2 to 0
    for (auto i : visited2)
    {
            i = false;
    }

    ctr2 = 0;

    // For each territory, check they are only pointing to one and only one continent
    for (int j = 0; j<territories.size(); j++)
    {
        string aContinent = *territories[j]->getContinent();
        if (!aContinent.empty())
        {
            visited2[j] = true;
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

    // If the visited2 vector contains only true for every territory, each territory belongs to one and only one continent
    if (ctr2 == territories.size())
    {
        cout << "Each territory belongs to one and only one continent! \n";
    }
    else
    {
        cout << "Each territory DOES NOT belong to one and only one continent! \n";
    }
}

// Default constructor
MapLoader::MapLoader()
{
    // this->Territories = vector<Territory>{};
}

/**
 * @brief Loads a map from the specified file
 * 
 * @param path Path of file to load
 * @return Map* A Map of the file. This is empty
 * if some error occured while loading the map.
 */
Map* MapLoader::loadMap(string path)
{
    
    unordered_map<string, string *> umapContinents;

    string line;
    vector<Territory *> territories;
    ifstream file(path);
    ofstream cout("maploader_log.txt");
    try
    {
        // if file is empty return error
        if (!file)
        {
            throw "Error invalid file: Empty file";
        }
        // This loop checks that the file contains a [Continents] and [Territories] line
        bool checkContinents = false, checkTerritories = false;
        while (getline(file,line))
        {
            if(line.find("[Continents]")!=string::npos)
            {
                checkContinents = true;
            }
            if(line.find("[Territories]")!=string::npos)
            {
                checkTerritories = true;
            }

        }
        if (checkContinents == false)
        {
            throw "Error invalid file: No continent";
        }
        if (checkTerritories == false)
        {
            throw "Error invalid file: No Territories";
        }
    }
    catch (char const* err)
    {
        std::cerr << err << endl;
        // Return an empty map on error
        return new Map();
        // exit(1);
    }
    // Close and re-open the file to load it again
    file.close();
    file.open(path);
    while (getline(file, line))
    {

        if (line.find("[Territories]") != std::string::npos)
        {
            // Once [Territories] is found, the rest are all territory declarations
            // So get lines until EOF
            while (getline(file, line))
            {
                vector<string> territory;

                cout << "\n";
                string delim = ",";

                auto start = 0U;
                auto end = line.find(delim);

                // Tokenize the territory line by commas into a vector<string>
                while (end != std::string::npos)
                {
                    territory.push_back((line.substr(start, end - start)));
                    cout << line.substr(start, end - start) << std::endl;
                    start = end + delim.length();
                    end = line.find(delim, start);
                }
                territory.push_back(line.substr(start, end));
                cout << line.substr(start, end) << "\n";

                // If line contained a territory description, continue
                if (territory.size() > 1)
                {
                    umapContinents.insert(std::make_pair(territory[0], new string(territory[3])));

                    Territory *newTerritory = new Territory();

                    auto search = umap.find(territory[0]);
                    if (search == umap.end())
                    {
                        // If the territory isn't in the umap, add it to umap and the territories vector
                        string *name = new string(territory[0]);
                        newTerritory->TerritoryName = name;
                        string *continent = new string(territory[3]);
                        newTerritory->continent = continent;

                        umap.insert(std::make_pair(territory[0], newTerritory));
                        territories.push_back(newTerritory);
                    }
                    else
                    {
                        // If the territory is already in the umap, grab a reference to it.
                        newTerritory = search->second;
                    }

                    // Add the adjacencies
                    for (int i = 4; i < territory.size(); i++)
                    {
                        // remove anything after a carriage return in the string
                        if (territory[i].find("\r") != string::npos)
                        {
                            territory[i].erase(territory[i].find("\r"), 1);
                        }
                        // Find the adjacent territories in the map
                        search = umap.find(territory[i]);

                        if (search == umap.end())
                        {
                            // If the adjacent territory isn't already in the map, add it
                            Territory *adj = new Territory();
                            string *toPointer = new string(territory[i]);
                            adj->TerritoryName = toPointer;

                            umap.insert(std::make_pair(territory[i], adj));
                            newTerritory->AdjTerritories.push_back(adj);
                            territories.push_back(adj);
                        }
                        else
                        {
                            // If the adjacent territory is in the map, add it to the list
                            // of adjacent territories
                            newTerritory->AdjTerritories.push_back(search->second);
                        }
                    }
                }
            }
        }
    }

    // Set each territory's continent
    for (auto territory : territories)
    {
        auto search = umapContinents.find(*(territory->TerritoryName));
        territory->continent = search->second;
    }
    Map *graph = new Map();
    graph->territories = territories;
    return graph;
}

// Destructor
MapLoader::~MapLoader()
{
    for(auto& i:umap){
        delete i.second;
    }
}