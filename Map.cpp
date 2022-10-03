#include "Map.h"
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

// ------------------------------------- //
// TEMPORARY PLAYER CLASS IMPLEMENTATION //
// ------------------------------------- //

// Default Constructor
Player::Player()
{
    this->name = "Player x";
}

//Destructor
Player::~Player()
{

}

//Assignment Operator
Player& Player::operator=(const Player& player)
{
    this->name = player.name;
    return *this;
}

//Player Name Getter
string Player::getName()
{
    return this->name;
}

//Player Name Setter
void Player::setName(string pname)
{
    this->name = pname;
}

// ------------------------------ //
// TERRITORY CLASS IMPLEMENTATION //
// ------------------------------ //

// Default Constructor
Territory::Territory()
{
    this->TerritoryName = "default territory";
    this->continent = "default continent";
    this->territoryOwner = new Player();
    this->armyAmount = 0;
}

// Parameterized Constructor
Territory::Territory(string name, string continent, Player* player, int army)
{
    this->TerritoryName = name;
    this->continent = continent;
    this->territoryOwner = player;
    this->armyAmount = army;
}

// Copy Constructor
Territory::Territory(const Territory* territory)
{
    this->TerritoryName = territory->TerritoryName;
    this->continent = territory->continent;
    this->territoryOwner = territory->territoryOwner;
    this->armyAmount = territory->armyAmount;
}

// Assignment Operator
Territory& Territory::operator=(const Territory& territory)
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
string Territory::getTerritoryName()
{
    return TerritoryName;
}

// Setter for TerritoryName
void Territory::setTerritoryName(string newName)
{
    this->TerritoryName = newName;
}

// Getter for Continent
string Territory::getContinent()
{
    return continent;
}

// Setter for Continent
void Territory::setContinent(string newContinent)
{
    this->continent = newContinent;
}

// Getter for TerritoryOwner
Player* Territory::getTerritoryOwner()
{
    return territoryOwner;
}

// Setter for TerritoryOwner
void Territory::setTerritoryOwner(Player* newPlayer)
{
    this->territoryOwner = newPlayer;
}

// Getter for Army
int Territory::getArmy()
{
    return armyAmount;
}

// Setter for Army
void Territory::setArmy(int newAmount)
{
    this->armyAmount = newAmount;
}

// Prints Territory Info
void Territory::toString()
{
    cout << "Name: " << this->TerritoryName << " "
    << "| Continent: " << this->continent << " "
    << "| Owner: " << this->territoryOwner->getName() << " "
    << "| Army: " << this->armyAmount << " " << endl;
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

vector<Territory> MapLoader::loadMap()
{

    // string contents;
    string line;
    vector<Territory> territories;
    ifstream file("./3D.map");
    ofstream cout("maploader_log.txt");

    bool validCheck = false;
    while (getline(file, line))
    {
        if (line.find("[Territories]") != std::string::npos)
        {
            validCheck = true;
        }
        if (validCheck == true)
        {
            vector<string> territory;

            cout << "\n";
            string delim = ",";

            uint start = 0U;
            int end = line.find(delim);
            while (end != std::string::npos)
            {
                territory.push_back(line.substr(start, end - start));
                cout << line.substr(start, end - start) << std::endl;
                start = end + delim.length();
                end = line.find(delim, start);
            }
            territory.push_back(line.substr(start, end));
            cout << line.substr(start, end) << "\n";

            if (territory.size() > 1)
            {
                Territory *t = new Territory(territory[0], territory[3], new Player(), 10);
                territories.push_back(t);
            }
        } // else throw error
    }
    for (Territory i : territories)
    {
        i.toString();
    }
    return territories;
}

Map MapLoader::setUpMatrix(vector<Territory> t)
{
    Map *map = new Map(t.size());
    string line;
    vector<vector<string> > territories;
    ifstream file("./3D.map");
    // ofstream cout("maploader_log.txt");
 
    bool validCheck = false;
    while (getline(file, line))
    {
        if (line.find("[Territories]") != std::string::npos)
        {
            validCheck = true;
        }
        if (validCheck == true)
        {
            vector<string> territory;

            string delim = ",";

            uint start = 0U;
            int end = line.find(delim);
            while (end != std::string::npos)
            {
                territory.push_back(line.substr(start, end - start));
                start = end + delim.length();
                end = line.find(delim, start);
            }
            territory.push_back(line.substr(start, end));

            if (territory.size() > 1)
            {
                territories.push_back(territory);
            }
        }
    }
    // cout << t[0];
    // cout << "\n\n\n";
    // cout << territories[0].size();
    // cout << "\n\n\n";
    for (int i = 0; i < territories.size(); i++)
    {
        for (int j = 0; j < territories[i].size(); j++)
        {

            cout << territories[i][j];
        }
        cout << "\n";
    }
    for (int i = 0; i < t.size(); i++)
    {

        if (territories[i][0] == t[i].getTerritoryName())
        {
            for (int j = 4; j < territories[i].size(); j++)
            {

                for (int x = 0; x < t.size(); x++)
                {
                    if (territories[i][j] == t[x].getTerritoryName())
                    {
                        map->addEdge(i, x);
                    }
                }
            }
        }
    }
    // }
    return map;
}

// Destructor

MapLoader::~MapLoader()
{
    // Territories.clear();
}