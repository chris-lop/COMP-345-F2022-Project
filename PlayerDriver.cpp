#include <iostream>
#include <vector>
#include "Player.h"


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
    Territoryt* t1 = new Territoryt(1, arr1);
    Territoryt* t2 = new Territoryt(3, arr2);
    Territoryt* t3 = new Territoryt(7, arr3);
    Territoryt* t4 = new Territoryt(8, arr4);
    Territoryt* t5 = new Territoryt(13, arr1);

    std::vector<Territoryt*> my_trt;
    my_trt.push_back(t1);
    my_trt.push_back(t2);
    my_trt.push_back(t3);
    my_trt.push_back(t4);
    my_trt.push_back(t5);

    /*1.2 vector <Card*>
    * Assigning random (string)values to different Card obj and create a vector<Card*> my_hand
    * my_hand is a vector representing a list of pointers to each of the cards owned by the player
    *
    */

    Cardt* c1 = new Cardt("bomb");
    Cardt* c2 = new Cardt("reinforcement");
    Cardt* c3 = new Cardt("airlift");

    std::vector<Cardt*> my_hand;
    my_hand.push_back(c1);
    my_hand.push_back(c2);
    my_hand.push_back(c3);

    /*1.3 vector <Order*>
    * Assigning random (string)values to different Order obj and create a vector<Order*> my_olst
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
  
 
    
    /*3. Testing methods for Player class
    * 
    *
    *3.1 toDefend()
    * Calling function toDefend() to list all territories the player p must defend
    * verify whether adjacent territories belongs to player p and print only territories where adjacent territories also belong to p
    * For this test, 0 represents no adjacent territories (refer 1.1).
    */
    
    std::cout << "\n \n # Calling toDefend() # \n" << std::endl;
    
    p->toDefend();

    /*3.2 toAttack()
    * Calling function toDefend() to list all territories the player p can attack
    * verify whether adjacent territories belongs to player p or not and print adjacent territories that don't belong to p
    * For this test, 0 represents no adjacent territories (refer 1.1).
    */

    std::cout << "\n \n # Calling toAttack() # \n" << std::endl;
    p->toAttack();

    std::cout << "\n \n # Calling issueOrder() # \n" << std::endl;
    p->issueOrder();

    std::cout << "\n \n### End of Player Test ### \n" << std::endl;
}
