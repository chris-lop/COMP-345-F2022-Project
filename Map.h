#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <map>
#pragma once

using namespace std;

void testLoadMaps();

// ----------------------- //
// TEMPORARY PLAYER CLASS  //
// ----------------------- //
class PlayerT
{
        //--------------//
        //  ATTRIBUTES  //
        //--------------//

        //Player name
        string name;

    public:
        //----------------//
        //  CONSTRUCTORS  //
        //----------------//

        //Default Constructor
        PlayerT();

        //Destructor
        ~PlayerT();

        //Assignment Operator        
        PlayerT& operator = (const PlayerT&);

        //-----------//
        //  GETTERS  //
        //-----------//
        string getName();     
        
        //-----------//
        //  SETTERS  //
        //-----------//
        void setName(string);
};

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
    PlayerT *territoryOwner;

    // Amount of troops in a given territory
    int *armyAmount;

    //----------------//
    //  CONSTRUCTORS  //
    //----------------//

    // Default Constructor
    Territory();

    // Parameterized Constructor
    Territory(string *, string *, vector<Territory *>, PlayerT *, int *);

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
    PlayerT *getTerritoryOwner();
    int *getArmy();
    vector<Territory *> getAdjTerritories();

    //-----------//
    //  SETTERS  //
    //-----------//
    void setTerritoryName(string *);
    void setContinent(string *);
    void setTerritoryOwner(PlayerT *);
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
        void validate(vector<Territory *>);

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