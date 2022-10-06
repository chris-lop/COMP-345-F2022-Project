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

// Prints Territory Info
void Territory::toString()
{

    cout << "Name: " << *(this->TerritoryName)
         << "| Continent: " << *(this->continent) << " "
         << "| Owner: " << this->territoryOwner->getName() << " "
         << "| Army: " << *(this->armyAmount)
         << "| Adjacent territories: " << endl;

    for (auto i : this->AdjTerritories)
    {
        std::cout << " [" << *i->TerritoryName << "] ";
    }
    cout << "\n"
         << endl;
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

vector<Territory *> MapLoader::loadMap(string path)
{

    // string contents;
    unordered_map<string, string *> umapContinents;

    string line;
    vector<Territory *> territories;
    ifstream file(path);
    ofstream cout("maploader_log.txt");
    // for filling adjacent territories in array
    bool validCheck = false;
    while (getline(file, line))
    {

        try
        {
            // if file is empty return error
            if (!file)
            {
                throw "Error invalid file: Empty file";
            }
        }
        catch (string err)
        {
            std::cout << err;
            // exit(1);
        }

        if (line.find("[Territories]") != std::string::npos)
        {
            validCheck = true;
        }
        if (validCheck == true)
        {
            vector<string> territory;

            cout << "\n";
            string delim = ",";

            auto start = 0U;
            auto end = line.find(delim);
            while (end != std::string::npos)
            {
                territory.push_back((line.substr(start, end - start)));
                cout << line.substr(start, end - start) << std::endl;
                start = end + delim.length();
                end = line.find(delim, start);
            }
            territory.push_back(line.substr(start, end));
            cout << line.substr(start, end) << "\n";

            if (territory.size() > 1)
            {
                umapContinents.insert(std::make_pair(territory[0], new string(territory[3])));

                Territory *newTerritory = new Territory();

                auto search = umap.find(territory[0]);
                if (search == umap.end())
                {

                    string *nameToPointer = new string(territory[0]);
                    newTerritory->TerritoryName = nameToPointer;
                    string *continentToPointer = new string(territory[3]);
                    newTerritory->continent = continentToPointer;

                    umap.insert(std::make_pair(territory[0], newTerritory));
                    territories.push_back(newTerritory);
                }
                else
                {
                    newTerritory = search->second;
                }

                for (int i = 4; i < territory.size(); i++)
                {
                    // std::cout << territory[i];
                    if (territory[i].find("\r") != string::npos)
                    {
                        // std::cout << territory[i].find("\r") << "\n";
                        territory[i].erase(territory[i].find("\r"), 1);
                    }

                    search = umap.find(territory[i]);

                    if (search == umap.end())
                    {
                        Territory *adj = new Territory();
                        string *toPointer = new string(territory[i]);
                        adj->TerritoryName = toPointer;

                        umap.insert(std::make_pair(territory[i], adj));
                        newTerritory->AdjTerritories.push_back(adj);
                        territories.push_back(adj);
                    }
                    else
                    {
                        newTerritory->AdjTerritories.push_back(search->second);
                    }
                }
            }
        }
    }

    // Set corresponding territories with their continents
    for (auto territory : territories)
    {
        auto search = umapContinents.find(*(territory->TerritoryName));
        territory->continent = search->second;
    }
    return territories;
}

// Destructor

MapLoader::~MapLoader()
{
}