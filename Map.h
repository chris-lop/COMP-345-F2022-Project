#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <map>
#include "Player.h"

class Player;

using namespace std;

void testLoadMaps();

// ------------------ //
//  TERRITORY CLASS   //
// ------------------ //
class Territory
{
public:
    //--------------//
    //  ATTRIBUTES  //
    //--------------//

    // Territory Name
    string *TerritoryName;
    // Adjacent territories
    vector<Territory *> AdjTerritories;

    // Continent to which territory belongs to
    string *continent;

    // Player to which territory belongs to
    Player* territoryOwner;

    // Amount of troops in a given territory
    int *armyAmount;

    //----------------//
    //  CONSTRUCTORS  //
    //----------------//

    // Default Constructor
    Territory();

    // Parameterized Constructor
    Territory(string *, string *, vector<Territory *>, Player *, int *);

    // Copy Constructor
    Territory(const Territory *);

    // Destructor
    ~Territory();

    // Assignment Operator
    Territory &operator=(const Territory &);

    //-----------//
    //  GETTERS  //
    //-----------//
    string *getTerritoryName();
    string *getContinent();
    Player *getTerritoryOwner();
    int *getArmy();
    vector<Territory *> getAdjTerritories();

    //-----------//
    //  SETTERS  //
    //-----------//
    void setTerritoryName(string *);
    void setContinent(string *);
    void setTerritoryOwner(Player *);
    void setArmy(int *);
    void setAdjTerritories(vector<Territory *>);

    // Stream insertion operator
    friend ostream& operator<<(ostream& strm, const Territory& territory);
};

// ------------ //
//  MAP CLASS   //
// ------------ //
class Map
{
    
    public:
        //--------------//
        //  ATTRIBUTES  //
        //--------------//

        // Variable for number of territories (nodes)   
        int TerritoryNb;
        vector<Territory*> territories;
        map<string, int> continentsList;
    
        //----------------//
        //  CONSTRUCTORS  //
        //----------------//

        // Default Constructor
        Map();

        // Parameterized Constructor
        Map(int);

        // Copy Constructor        
        Map(const Map*);

        // Destructor
        ~Map();

        // Assignment Operator
        Map& operator = (const Map&);

        // Validate method
        bool validate(vector<Territory *>);

};

//  MAP Loader CLASS   //
class MapLoader
{
public:
    // Unordered Map used for graph initialization
    unordered_map<string, Territory *> umap;

    // Attributes
    // vector<Territory> Territories;

    // Default Constructor
    MapLoader();

    // std::vector<Territory> loadMap();
    Map* loadMap(string);

    // Destructor
    ~MapLoader();
};