#include <iostream>
#include <algorithm>
#include <cmath>
#include "Orders.h"
#include "Map.h"
#include "Cards.h"
#include "Player.h"

using std::vector;

/*
 * Player class
 */
// Default constructor
Player::Player()
{
    this->name = "Null";
    this->trt = {};
    this->h = new Hand();
    this->olst = new OrdersList();
    this->army_unit = 0;
}
// Constructor with name parameter
Player::Player(std::string name)
{
    this->name = name;
    this->trt = {};
    this->h = new Hand();
    this->olst = new OrdersList();
    this->army_unit = 0;
}
// Constructor without reinforcement pool

Player::Player(std::string name, std::vector<Territory *> trt, Hand *h, OrdersList *olst)
{
    this->name = name;
    this->trt = trt;
    this->h = h;
    this->olst = olst;
    this->army_unit = 0;
}
// Constructor with all parameters
Player::Player(std::string name, std::vector<Territory *> trt, Hand *h, OrdersList *olst, int army_unit)
{
    this->name = name;
    this->trt = trt;
    this->h = h;
    this->olst = olst;
    this->army_unit = army_unit;
}

// Destructor
Player::~Player()
{
    for (Territory *t : trt)
    {
        delete (t);
    }
    delete h;
    delete olst;
}

// Copy constructor
Player ::Player(const Player &p1)
{
    this->name = std::string(p1.name);

    // copy the territory vector
    for (Territory t : p1.trt)
    {
        Territory *t1 = new Territory(t);
        this->trt.push_back(t1);
    }

    this->h = new Hand(*p1.h);
    this->olst = new OrdersList(*p1.olst);
}

// Getter for name
std::string Player::get_name()
{
    return this->name;
}
// Getter for trt
std::vector<Territory *> Player::get_trt()
{
    return this->trt;
}
// Getter for olst
OrdersList *Player::get_olst()
{
    return this->olst;
}
// Getter for hand
Hand *Player::get_Phand()
{
    return this->h;
}
// Getter for army_unit
int Player::get_armyUnit()
{
    return this->army_unit;
}

// Checks if this player has a negotiation with the other
bool Player::hasNegotiationWith(Player *o)
{
    return any_of(negotiatedPlayers.begin(), negotiatedPlayers.end(), [o](Player *p)
                  { return p == o; });
}

// Setter for name
void Player::set_Pname(std::string name)
{
    this->name = name;
}
// Setter for territory list
void Player::set_Trt(std::vector<Territory *> trt)
{
    this->trt = trt;
}
// Setter for order list
void Player::set_Olst(OrdersList *newolst)
{
    this->olst = newolst;
}
// Setter for hand
void Player::set_Player_Hand(Hand *h)
{
    this->h = h;
}
// Setter for army_unit
//  ALSO: clears the list of negotiated players,
//  since it's the start of a turn
void Player::set_armyUnit(int army_unit)
{
    if (army_unit > this->army_unit)
    {
        negotiatedPlayers.clear();
    }
    this->army_unit = army_unit;
}

void Player::addNegotiatedPlayer(Player *p)
{
    negotiatedPlayers.push_back(p);
}

// Player stream operators
std::ostream &operator<<(std::ostream &strm, const Player &p)
{
    strm << "This player is: " << p.name << std::endl;
    strm << "The list of territory owned: " << std::endl;

    for (Territory *t : p.trt)
    {
        string t_name = *(t->getTerritoryName());
        strm << t_name << "\t";
    }
    strm << "\n";
    strm << "The number of army units owned: " << p.army_unit << std::endl;
    strm << "Player's current list of orders: ";
    // strm << p.olst;
    strm << std::endl;
    return strm;
}
std::istream &operator>>(std::istream &in, Player &p)
{
    std::cout << "Enter player name: ";
    in >> p.name;
    return in;
}

// method corrected from assignment 1
// toDefend()
// issue a list of territories to be defended by the player based on the player owned territories
std::vector<Territory *> Player::toDefend()
{

    // new vector of Territory to be returned as result
    std::vector<Territory *> result_defend;

    for (Territory *t : this->trt)
    {

        // traverse the list of adjacent territories for each t
        for (Territory *t_adj : t->getAdjTerritories())
        {
            // verify if each territory in the adjacent territories list is in the list of territories owned

            if ((std::find(trt.begin(), trt.end(), t_adj)) != trt.end())
            {
                // The adjacent territory was found in the list of owned territories
                // We don't need to defend the territory t
                continue;
            }

            // The adjacent territory was not found, thus, the territory t must be defended
            else
            {
                // if the territory to defend was already added, skip
                if ((std::find(result_defend.begin(), result_defend.end(), t)) != result_defend.end())
                {
                    continue;
                }
                // if not, add to the result vector
                else
                {
                    result_defend.push_back(t);
                }
            }
        }
    }
    return result_defend;
}

// toAttack()
// issue a list of territories that can be attacked by the player based on the player owned territories
std::vector<Territory *> Player::toAttack()
{
    // vector territory to be returned as result
    std::vector<Territory *> result_attack;

    for (Territory *t : this->trt)
    {
        // traverse the list of adjacent territories for each territory t
        for (Territory *t_adj : t->getAdjTerritories())
        {

            if ((std::find(trt.begin(), trt.end(), t_adj)) != trt.end())
            {
                // The adjacent territory was found in the list of owned territories
                // We don't need to attack the territory t
                continue;
            }

            // The adjacent territory was not found in owned territories, thus, the territory t_adj can be attacked
            else
            {
                // if the territory to attack was already added, skip
                if ((std::find(result_attack.begin(), result_attack.end(), t_adj)) != result_attack.end())
                {
                    continue;
                }
                // if not, add to the result vector
                else
                {
                    result_attack.push_back(t_adj);
                }
            }
        }
    }

    return result_attack;
}

//add a new order input by user to the existing list
void Player::issueOrder()
{
    // issueOrder Starting Message
    cout << this->get_name() << "'s Turn to play:" << endl;

    // Variable to keep track of reinforcement
    int deployed_units = 0;

    // Vector to keep track of issued orders
    vector <string> issued_orders;

    while (true)
    {
        // If reinforcement pool of player isn't empty, player can only use Deploy orders
        if (this->get_armyUnit()-deployed_units != 0)
        {
            // Deployment Starting Message
            cout << "You still have army units in your reinforcement pool!" << endl;
            cout << "You currently have: " << this->get_armyUnit()-deployed_units << " units in your reinforcement pool!" << endl;
            cout << "You must deploy these units before issuing any other orders." << endl << endl;
            
            // Saving player's defendable territories using toDefend() method
            vector <Territory*> trt_defend = this->toDefend();

            // Displaying player's defendable territories 
            cout << "Defendable Territories: " << endl;
            int trt_defend_ctr = 0;

            for(Territory* t: trt_defend)
            {
                trt_defend_ctr++;
                cout << "[" << trt_defend_ctr << "]: " << *t->getTerritoryName() << endl;
            }

            // Ask for which territory player wants to deploy units to
            cout << "\nSelect a territory to reinforce (1-" << trt_defend_ctr << "):" << endl;
            int trt_defend_choice = 1;
            cout << "Territory Selected: " << *trt_defend[trt_defend_choice-1]->getTerritoryName() << endl << endl;

            // Ask user for how many units he wants to reinforce this territory with
            cout << "How many units do you want to reinforce this territory with? (Max: " << this->get_armyUnit() << ")" << endl;
            int trt_defend_army_amount = this->get_armyUnit();
            cout << "Amount of Units: " << trt_defend_army_amount << endl << endl;

            // Increment deployed_units by this value
            deployed_units = deployed_units + trt_defend_army_amount;

            // Create Deploy order with data above
            Deploy* d = new Deploy(trt_defend[trt_defend_choice-1], this, trt_defend_army_amount);

            // Add deploy order to player's order list
            this->get_olst()->addOrder(d); 

            // Add to issed orders vector for display later
            issued_orders.push_back("Deploy | To: "+*trt_defend[trt_defend_choice-1]->getTerritoryName()+" | "+to_string(trt_defend_army_amount)+" units");
            
        }
        // Else, the reinforcement pool is empty, let player give other orders
        else
        {
            // Boolean variable to check if player possesses airlift card
            bool hasAirlift;
            bool hasBomb;
            bool hasBlockade;
            bool hasdiplomacy;
            
            // Check through a player's hand and check if he has order cards
            for (Card* c : this->get_Phand()->cardList())
            {
                // If player has airlift card, save it in boolean variable
                if (c->getType() == "Airlift" || c->getType() == "airlift")
                {
                    hasAirlift = true;
                    break;
                }
                // If player has bomb card, save it in boolean variable 
                if (c->getType() == "Bomb" || c->getType() == "bomb")
                {
                    hasBomb = true;
                    break;
                }
                // If player has blockade card, save it in boolean variable
                if (c->getType() == "Blockade" || c->getType() == "blockade")
                {
                    hasBlockade = true;
                    break;
                }
                // If player has diplomacy card, save it in boolean variable 
                if (c->getType() == "Diplomacy" || c->getType() == "diplomacy")
                {
                    hasdiplomacy = true;
                    break;
                }
            }

            // Diplay player options for further orders
            cout << "Select which type of order you want to issue:" << endl;
            cout << "[1]: Advance" << endl;
            
            // If player has airlift card, print out the option to issue that order
            if (hasAirlift)
            {
                cout << "[2]: Airlift" << endl;
            }
            // If player has bomb card, print out the option to issue that order
            if (hasBomb)
            {
                cout << "[3]: Bomb" << endl;
            }
            // If player has blockade card, print out the option to issue that order
            if (hasBlockade)
            {
                cout << "[4]: Blockade" << endl;
            }
            // If player has diplomacy card, print out the option to issue that order
            if (hasdiplomacy)
            {
                cout << "[5]: Negotiate" << endl;
            }

            // Save user choice
            cout << "\nPlease enter a choice: " << endl;
            int order_option;
            cout << "Choice Selected: " << "[" << order_option << "]" << endl << endl;

            // Switch case to issue order depending on user choice
            switch(order_option) 
            {
                // Advance case
                case 1:
                    {
                        // Advance order starting message, make user choose between moving units or attacking enemy
                        cout << "Starting an Advance Order!" << endl;
                        cout << "Do you want to move units to a friendly territory or attack an enemy territory? (MOV/ATK)" << endl;
                        
                        // Save user input to variable
                        string advance_choice;
                        cout << "Choice Selected: " << "[" << advance_choice << "]" << endl << endl;

                        // Declaration of trt_defend_ctr and trt_defend vector
                        vector <Territory*> trt_defend;
                        int trt_defend_ctr;

                        // If initial choice was MOV, use defendable territories vector
                        if (advance_choice=="MOV")
                        {
                            // Saving player's defendable territories using toDefend() method
                            trt_defend = this->toDefend();

                            // Displaying player's defendable territories 
                            cout << "Defendable Territories: " << endl;
                            trt_defend_ctr = 0;

                            for(Territory* t: trt_defend)
                            {
                                trt_defend_ctr++;
                                cout << "[" << trt_defend_ctr << "]: " << *t->getTerritoryName() << endl;
                            }
                        }
                        // Else, if initial choice was ATK, use attackable territories vector
                        else if (advance_choice=="ATK")
                        {
                            // Saving player's attackable territories using toAttack() method
                            vector <Territory*> trt_defend = this->toAttack();

                            // Displaying player's attackable territories 
                            cout << "Attackable Territories: " << endl;
                            trt_defend_ctr = 0;

                            for(Territory* t: trt_defend)
                            {
                                trt_defend_ctr++;
                                cout << "[" << trt_defend_ctr << "]: " << *t->getTerritoryName() << endl;
                            }
                        }

                        // Ask for which territory player wants to move units to and save user input into variable
                        cout << "\nSelect a territory to move units to (1-" << trt_defend_ctr << "):" << endl;
                        int trt_defend_choice;
                        cout << "Territory Selected: " << *trt_defend[trt_defend_choice-1]->getTerritoryName() << endl << endl;

                        // Look through this territory's adjacent territories
                        // print out the territories belonging to the player and the amount of units in these territories
                        trt_defend_ctr = 0;
                        vector <Territory*> trt_source;
                        for(Territory* t: trt_defend[trt_defend_choice-1]->getAdjTerritories())
                        {
                            if (t->getTerritoryOwner()->get_name() == this->get_name())
                            {
                                trt_defend_ctr++;
                                cout << "[" << trt_defend_ctr << "]: " << *t->getTerritoryName() << " | Troops available: " << *t->getArmy() << endl;
                                trt_source.push_back(t);
                            }
                        }

                        // Ask for which territory player wants to move units from and save user input into variable
                        cout << "\nSelect a territory to move units from (1-" << trt_defend_ctr << "):" << endl;
                        int trt_source_choice;
                        cout << "Territory Selected: " << trt_source[trt_source_choice-1]->getTerritoryName() << endl << endl;

                        // Ask for how many units user wants to move and save user input into variable
                        cout << "How many units do you want to reinforce this territory with? (Max: " << *trt_source[trt_source_choice-1]->getArmy() << ")" << endl;
                        int trt_defend_army_amount;
                        cout << "Amount of Units: " << trt_defend_army_amount << endl << endl;

                        // Create Advance order with data above
                        Advance* a = new Advance(trt_source[trt_source_choice-1], trt_defend[trt_defend_choice-1], this , trt_defend_army_amount);

                        // Add deploy order to player's order list
                        this->get_olst()->addOrder(a);

                        // Add to issed orders vector for display later
                        issued_orders.push_back("Advance | From: "+*trt_source[trt_source_choice-1]->getTerritoryName()+" | To: "+*trt_defend[trt_defend_choice-1]->getTerritoryName()+" | "+to_string(trt_defend_army_amount)+" units");
                        break;
                    }
                
                // Airlift case
                case 2:
                    {
                        // Airlift order starting message
                        cout << "Starting an Airlift Order!" << endl;

                        // Saving player's defendable territories using toDefend() method
                        vector <Territory*> trt_defend = this->toDefend();

                        // Displaying player's defendable territories 
                        cout << "Defendable Territories: " << endl;
                        int trt_defend_ctr = 0;

                        for(Territory* t: trt_defend)
                        {
                            trt_defend_ctr++;
                            cout << "[" << trt_defend_ctr << "]: " << *t->getTerritoryName() << endl;
                        }

                        // Ask for which territory player wants to Airlift units to and save user input into variable
                        cout << "\nSelect a territory to Airlift units to (1-" << trt_defend_ctr << "):" << endl;
                        int trt_defend_choice;
                        cout << "Territory Selected: " << trt_defend[trt_defend_choice-1]->getTerritoryName() << endl << endl;

                        // Print out this player's other territories
                        trt_defend_ctr = 0;
                        
                        for(Territory* t: trt_defend)
                        {
                            trt_defend_ctr++;

                            // If the current territory is the territory selected for defense, skip it
                            if (trt_defend_ctr == trt_defend_choice)
                            {
                                continue;
                            }

                            cout << "[" << trt_defend_ctr << "]: " << *t->getTerritoryName() << endl;
                        }

                        // Ask for which territory player wants to move units from and save user input into variable
                        cout << "\nSelect a territory to move units from:" << endl;
                        int trt_source_choice;
                        cout << "Territory Selected: " << trt_defend[trt_defend_choice-1]->getTerritoryName() << endl << endl;

                        // Ask for how many units user wants to move and save user input into variable
                        cout << "How many units do you want to Airlift? (Max: " << *trt_defend[trt_defend_choice-1]->getArmy() << ")" << endl;
                        int trt_defend_army_amount;
                        cout << "Amount of Units: " << trt_defend_army_amount << endl << endl;

                        // Create Airlift order with data above
                        Airlift* a = new Airlift(trt_defend[trt_source_choice-1], trt_defend[trt_defend_choice-1], this , trt_defend_army_amount);

                        // Add Airlift order to player's order list
                        this->get_olst()->addOrder(a);

                        // Add to issed orders vector for display later
                        issued_orders.push_back("Airlift | From: "+*trt_defend[trt_source_choice-1]->getTerritoryName()+" | To: "+*trt_defend[trt_defend_choice-1]->getTerritoryName()+" | "+to_string(trt_defend_army_amount)+" units");
                        break;
                    }

                // Bomb case
                case 3:
                    {
                        // Bomb order starting message
                        cout << "Starting an Bomb Order!" << endl;

                        // Saving player's attackable territories using toAttack() method
                        vector <Territory*> trt_attack = this->toAttack();

                        // Displaying player's attackable territories 
                        cout << "Attackable Territories: " << endl;
                        int trt_attack_ctr = 0;

                        for(Territory* t: trt_attack)
                        {
                            trt_attack_ctr++;
                            cout << "[" << trt_attack_ctr << "]: " << *t->getTerritoryName() << endl;
                        }

                        // Ask for which territory player wants to Bomb
                        cout << "\nSelect a territory to Bomb (1-" << trt_attack_ctr << "):" << endl;
                        int trt_attack_choice;
                        cout << "Territory Selected: " << trt_attack[trt_attack_choice-1]->getTerritoryName() << endl << endl;

                        // Create Bomb order with data above
                        Bomb* b = new Bomb(trt_attack[trt_attack_choice-1], this);

                        // Add Bomb order to player's order list
                        this->get_olst()->addOrder(b);

                        // Add to issued orders vector for display later
                        issued_orders.push_back("Bomb | Target: "+*trt_attack[trt_attack_choice-1]->getTerritoryName());
                        break;
                    }

                // Blockade case
                case 4:
                    {
                        // Blockade order starting message
                        cout << "Starting an Blockade Order!" << endl;

                        // Saving player's defendable territories using toDefend() method
                        vector <Territory*> trt_defend = this->toDefend();

                        // Displaying player's defendable territories 
                        cout << "Defendable Territories: " << endl;
                        int trt_defend_ctr = 0;

                        for(Territory* t: trt_defend)
                        {
                            trt_defend_ctr++;
                            cout << "[" << trt_defend_ctr << "]: " << *t->getTerritoryName() << endl;
                        }

                        // Ask for which territory player wants to Blockade
                        cout << "\nSelect a territory to Blockade (1-" << trt_defend_ctr << "):" << endl;
                        int trt_defend_choice;
                        cout << "Territory Selected: " << trt_defend[trt_defend_choice-1]->getTerritoryName() << endl << endl;

                        // Create Blockade order with data above
                        Blockade* blc = new Blockade(trt_defend[trt_defend_choice-1], this);

                        // Add Blockade order to player's order list
                        this->get_olst()->addOrder(blc);

                        // Add to issued orders vector for display later
                        issued_orders.push_back("Blockade | Target: "+*trt_defend[trt_defend_choice-1]->getTerritoryName());
                        break;
                    }

                // Negotiate case
                case 5:
                    {
                        // Negotiate order starting message
                        cout << "Starting a Negotiate Order!" << endl;

                        // Saving player's attackable territories using toAttack() method
                        vector <Territory*> trt_attack = this->toAttack();

                        // Extracting Players from territory List
                        map<string, int> temporaryPlayerMap;

                        // For each territory, insert its owner in the player map
                        for (Territory *aTerritory : trt_attack)
                        {
                            temporaryPlayerMap.insert(pair<string, int>(aTerritory->getTerritoryOwner()->get_name(), 0));
                        }

                        // Player vector to store neighbouring players
                        vector <string> temporaryPlayerList;

                        // Insert each individual player in temporaryPlayerList
                        for(map<string,int>::iterator it = temporaryPlayerMap.begin(), end = temporaryPlayerMap.end(); it != end; it = temporaryPlayerMap.upper_bound(it->first))
                        {
                            temporaryPlayerList.push_back(it->first);
                        }

                        // Displaying player's attackable territories owners
                        cout << "Players to Negotiate with: " << endl;
                        int trt_attack_ctr = 0;

                        for(string s: temporaryPlayerList)
                        {
                            trt_attack_ctr++;
                            cout << "[" << trt_attack_ctr << "]: " << temporaryPlayerList[trt_attack_ctr-1] << endl;
                        }

                        // Ask for which player to Negotiate with
                        cout << "\nSelect a player to Negotiate with (1-" << trt_attack_ctr << "):" << endl;
                        int trt_attack_choice;
                        

                        // Find player and create a ptr to this player
                        Player *aTarget;
                        for (Territory *aTerritory : trt_attack)
                        {
                            // If player name selected matches the current territory's owner name, make ptr point to this player and stop for loop
                            if (temporaryPlayerList[trt_attack_choice-1]==aTerritory->getTerritoryOwner()->get_name())
                            {
                                aTarget = aTerritory->getTerritoryOwner();
                                break;
                            }
                        }

                        // Print out selected player name
                        cout << "Player Selected: " << aTarget->get_name() << endl << endl;

                        // Create Negotiate order with data above
                        Negotiate* neg = new Negotiate(this, aTarget);

                        // Add Bomb order to player's order list
                        this->get_olst()->addOrder(neg);

                        // Add to issued orders vector for display later
                        issued_orders.push_back("Negotiate | Target: "+aTarget->get_name());
                        break;
                    }
            }
        }
        // Warning message
        cout << "Warning! " << this->get_name() << "'s turn has ended." << endl;

        // Print issued orders
        cout << "Issued Orders:" << endl;
        for (string s : issued_orders)
        {
            cout << s << endl;
        }
        cout << endl;

        // Break out of outter while loop
        break;
    }
}
