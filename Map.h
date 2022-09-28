#include <string>
using namespace std;

// ----------------------- //
// TEMPORARY PLAYER CLASS  //
// ----------------------- //
class Player
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
        Player();

        //Destructor
        ~Player();

        //Assignment Operator        
        Player& operator = (const Player&);

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
        //--------------//
        //  ATTRIBUTES  //
        //--------------//

        // Territory Name
        string TerritoryName;

        // Continent to which territory belongs to
        string continent;

        // Player to which territory belongs to
        Player* territoryOwner;

        //Amount of troops in a given territory
        int armyAmount;

    public:
        //----------------//
        //  CONSTRUCTORS  //
        //----------------//

        // Default Constructor
        Territory();

        // Parameterized Constructor          
        Territory(string, string, Player*, int);

        // Copy Constructor              
        Territory(const Territory*);

        // Destructor
        ~Territory();

        // Assignment Operator
        Territory& operator = (const Territory&);

        //-----------//
        //  GETTERS  //
        //-----------//
        string getTerritoryName();
        string getContinent();
        Player* getTerritoryOwner();
        int getArmy();

        //-----------//
        //  SETTERS  //
        //-----------//
        void setTerritoryName(string);
        void setContinent(string);
        void setTerritoryOwner(Player*);
        void setArmy(int);

        // Prints Territory Info
        void toString();
};

// ------------ //
//  MAP CLASS   //
// ------------ //
class Map
{
        //--------------//
        //  ATTRIBUTES  //
        //--------------//

        //Adjancency Matrix
        bool** adjMatrix;

        // Variable for number of territories (nodes)   
        int TerritoryNb;
    
    public:
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

        //---------------------//
        //  OTHER OPERATIONS  //
        //-------------------//

        // Adds an edge between two territories
        void addEdge(int, int);

        // Removes an edge between two territories
        void removeEdge(int, int);

        // Prints Adjancency Matrix
        void toString();

        // Verifies...
        // 1. the map is a connected graph
        // 2. continents are connected subgraphs
        // 3. each country belongs to one and only one continent
        // void Validate();
};