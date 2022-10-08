#include "Map.h"
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

// ------------------------------------- //
// TEMPORARY PLAYER CLASS IMPLEMENTATION //
// ------------------------------------- //

// Default Constructor
PlayerT::PlayerT()
{
    this->name = "Player x";
}

//Destructor
PlayerT::~PlayerT()
{

}

//Assignment Operator
PlayerT& PlayerT::operator=(const PlayerT& player)
{
    this->name = player.name;
    return *this;
}

//Player Name Getter
string PlayerT::getName()
{
    return this->name;
}

//Player Name Setter
void PlayerT::setName(string pname)
{
    this->name = pname;
}


// ------------------------------ //
// TERRITORY CLASS IMPLEMENTATION //
// ------------------------------ //

// Default Constructor
Territory::Territory()
{
    this->TerritoryName = new string("default territory");
    this->continent = new string("default continent");
    this->territoryOwner = new PlayerT();
    this->armyAmount = new int(0);
    this->AdjTerritories = vector<Territory *>{};
}

// Parameterized Constructor
Territory::Territory(string *name, string *continent, vector<Territory *> territories, PlayerT *player, int *army)
{
    this->TerritoryName = name;
    this->continent = continent;
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
PlayerT *Territory::getTerritoryOwner()
{
    return territoryOwner;
}

// Setter for TerritoryOwner
void Territory::setTerritoryOwner(PlayerT *newPlayer)
{
    this->territoryOwner = newPlayer;
}

// Setter for ADJTerritories
// void Territory::setAdjTerritories(vector<Territory *> territories)
// {
//     this->AdjTerritories = &territories;
// }

// Getter for Army
// vector<Territory> Territory::getAdjTerritories()
// {
//     return AdjTerritories;
// }

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

ostream& operator<<(ostream& strm, const Territory& territory) {
        strm << "Name: " << *(territory.TerritoryName)
         << "| Continent: " << *(territory.continent) << " "
         << "| Owner: " << territory.territoryOwner->getName() << " "
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
    this->adjMatrix = NULL;
}

// Parameterized Constructor
Map::Map(int TerritoryNb)
{
    this->TerritoryNb = TerritoryNb;
    adjMatrix = new bool* [TerritoryNb];
    //initialize the 2d array with false
    for (int i = 0; i < TerritoryNb; i++) {
        adjMatrix[i] = new bool[TerritoryNb];
        for (int j = 0; j < TerritoryNb; j++)
            adjMatrix[i][j] = false;
    }
}

// Copy Constructor
Map::Map(const Map *map)
{
    this->TerritoryNb = map->TerritoryNb;
    this->adjMatrix = map->adjMatrix;
}



// Assignment Operator
Map& Map::operator=(const Map& map)
{
    this->adjMatrix = map.adjMatrix;
    this->TerritoryNb = map.TerritoryNb;
    return *this;
}

// Adds an edge between two territories
void Map::addEdge(int i, int j)
{
    adjMatrix[i][j] = true;
    adjMatrix[j][i] = true;
}

// Removes an edge between two territories
void Map::removeEdge(int i, int j)
{
    adjMatrix[i][j] = false;
    adjMatrix[j][i] = false;
}

// Prints Adjancency Matrix
void Map::toString()
{
    cout << "    ";
    for (int i = 0; i < TerritoryNb; i++) {
        cout << i << " ";
    }

    cout << "\n";

    cout << endl;
    for (int i = 0; i < TerritoryNb; i++) {
        cout << i << "   ";
        for (int j = 0; j < TerritoryNb; j++)
            cout << adjMatrix[i][j] << " ";
        cout << "\n";
    }
}

// Destructor
Map::~Map()
{
    for (int i = 0; i < this->TerritoryNb; i++)
        delete[] adjMatrix[i];
    delete[] adjMatrix;
}

// Verify whether a graph is connected or not
/*
void Map::Validate()
{
    
}
*/

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
}