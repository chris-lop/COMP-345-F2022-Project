#include <iostream>
#include <vector>
#include "Player.h"
#include "Cards.h"


void testPlayer() {

    /*  1.Assigning values to each vectors used as parameter in Player obj
    * 
    * 1.1 vector <Territoryt*>
    * Assigning random (int)values to different Territory obj and create a vector<Territory*> my_trt
    * my_trt is a vector representing a list of pointers to each of the territories owned by the player
    * 0 represents no adjacent territory
    * 
    */
    int arr1[] = { 10, 0 };
    int arr2[] = { 7, 15 };
    int arr3[] = { 3, 8 };
    int arr4[] = { 11, 5 };
    int arr5[] = { 9, 2 };
    Territoryt* t1 = new Territoryt(1, arr1);
    Territoryt* t2 = new Territoryt(3, arr2);
    Territoryt* t3 = new Territoryt(7, arr3);
    Territoryt* t4 = new Territoryt(8, arr4);
    Territoryt* t5 = new Territoryt(13, arr5);

    std::vector<Territoryt*> my_trt;
    my_trt.push_back(t1);
    my_trt.push_back(t2);
    my_trt.push_back(t3);
    my_trt.push_back(t4);
    my_trt.push_back(t5);

    /*1.2 Hand
    * Integrate classes in Cards.h to create a Hand to assign to the player
    * Use of draw() and addCard() method to assign random cards
    */

    Deck* d = new Deck();
    Hand* my_hand= new Hand();
    for (int i = 0; i < 3; i++) {
        my_hand->addCard(d->draw());
    }
 

    /*1.3 vector <Ordert*>
    * Assigning random (string)values to different Ordert obj and create a vector<Ordert*> my_olst
    * my_olst is a vector representing a list of pointers to each of the order owned by the player
    *
    */

    Ordert* o1 = new Ordert("advance");
    Ordert* o2 = new Ordert("negotiate");
    Ordert* o3 = new Ordert("deploy");

    std::vector<Ordert*> my_olst;
    my_olst.push_back(o1);
    my_olst.push_back(o2);
    my_olst.push_back(o3);

    
    /*2. Create a random player for testing purpose
    * A player must own a list of territories, a hand of cards, and a list of order.
    */
    std::cout << "\n### Test Player ### \n" << std::endl;

    Player* p = new Player("Player_random", my_trt, my_hand, my_olst);

    std::cout << *p;

    //verifying that integration was done properly
    Hand* testh = p->get_Phand();
    std::cout << "Player's current hand of cards: " << *testh << std::endl;
  
    
    /*3. Testing methods for Player class
    * 
    *
    *3.1 toDefend()
    * Calling function toDefend() to list all territories the player p must defend
    * verify whether adjacent territories belongs to player p and print only territories where adjacent territories also belong to p
    * For this test, 0 represents no adjacent territories (refer 1.1).
    */
    
    std::cout << "\n \n # Calling toDefend() # \n\n Result should be: all territories but 7. \n 7 is the only territory for which this player owns all adjacent territories. \n" << std::endl;
    
    std::vector <Territoryt*> defend_list = p->toDefend();
    std::cout << "The player " << p->get_name() << " must defend the following territories: ";
    for(Territoryt* tp: defend_list){
        std::cout<< tp->get_t() << "\t";
    }

    /*3.2 toAttack()
    * Calling function toAttack() to list all territories the player p can attack
    * verify whether adjacent territories belongs to player p or not and print adjacent territories that don't belong to p
    * For this test, 0 represents no adjacent territories (refer 1.1).
    */

    std::cout << "\n \n # Calling toAttack() # \n\n Result should be: 2, 5, 9, 10, 11, and 15. \n These are the adjacent territories currently not owned by the player. \n" << std::endl;
    std::cout << "The player " << p->get_name() << " can attack the following territories: ";
    std::vector <Territoryt*> attack_list = p->toAttack();
    for(Territoryt* tp: attack_list){
        std::cout<< tp->get_t() << "\t";
    }

    /*3.3 issueOrder()
    * Calling function issueOrder() to add a new order to the existing list of orders owned by the player p
    * 
    */
    std::cout << "\n \n # Calling issueOrder() # \n" << std::endl;
    p->issueOrder();

    //calling destructor on player and deck
    delete p; 
    delete d;

    std::cout << "\n \n### End of Player Test ### \n" << std::endl;
}
