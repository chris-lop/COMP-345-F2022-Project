#include <iostream> 
#include "Orders.h"
#include <algorithm>

using std::cout;
using std::endl;

//Testing everything implemented in Orders.cpp
void testOrdersLists(){
    //create different orders objects
    cout <<"### Test Orders ###" << endl;
    
    Deploy *deploy = new Deploy();
    cout << "Creating a Deploy object: " << *deploy << endl;

    Deploy *deploy2 = new Deploy();
    cout << "Creating a Deploy object: " << *deploy2 << endl;

    Advance *advance = new Advance();
    cout << "Creating an Advance object: " << *advance << endl;

    Bomb *bomb = new Bomb();
    cout << "Creating a Bomb object: " << *bomb << endl;

    Blockade *blockade = new Blockade();
    cout << "Creating a Blockade object: " << *blockade << endl;

    Airlift *airlift = new Airlift();
    cout << "Creating an Airlift object: " << *airlift << endl;

    Negotiate *negotiate = new Negotiate();
    cout << "Creating a Negotiate object: " << *negotiate << endl;


    cout << "\n\n### OrdersList Test ###" << endl;
    cout << "Creating an OrdersList object and adding all the orders to it:" << endl;
    //create an OrdersList object to store all the orders in
    OrdersList* list = new OrdersList();
    //Insert all the orders into the list
    list->addOrder(deploy);
    list->addOrder(deploy2);
    list->addOrder(advance);
    list->addOrder(bomb);
    list->addOrder(blockade);
    list->addOrder(airlift);
    list->addOrder(negotiate);


    //print the list
    for (int i=0; i<list->getOrder().size(); ++i) {
        std::cout << *list->getOrder().at(i) << ' ';
    }

    cout << "\n\n### validate() method ###" << endl;
   //make deploy as valid = true and then validate the deploy
    deploy->setValid(true);
    cout << "Set the \"valid\" paarameter of deploy to true: " << deploy->getValid() << endl;
    cout << "Run the valid() method for deploy: " << deploy->validate() << endl;

   //make bomb as valid = true and then validate the bomb object
    bomb->setValid(false);
    cout << "\nSet the \"valid\" paarameter of bomb to false: " << bomb->getValid() << endl;
    cout << "Run the valid() method for bomb: " << bomb->validate() << endl;


    cout << "\n\n### execute() method ###" << endl;

    //execute deploy
    cout << "Run the execute() method for deploy: " << endl;
    deploy->execute();

    //execute bomb
    cout << "Run the execute() method for bomb: " <<  endl;
    bomb->execute();


    cout << "\n\n### move() method ###" << endl;
    int index;
    //Move order2 to position 5
    cout << "Move bomb to position 5" << endl;
    index = 5;
    list->move(bomb,index);
    //print the list
    for (int i=0; i<list->getOrder().size(); ++i) {
        std::cout << *list->getOrder().at(i) << ' ';
    }

    //Move negotiate to position 1
    cout << "\nMove negotiate to position 1" << endl;
    index = 1;

    list->move(negotiate,index);
    //print the list
    for (int i=0; i<list->getOrder().size(); ++i) {
        std::cout << *list->getOrder().at(i) << ' ';
    }


    //remove order2 from the list
    cout << "\n\n### remove() method ###" << endl;
    cout << "Remove bomb" << endl;
    list->remove(bomb);
    //print the list
    for (int i=0; i<list->getOrder().size(); ++i) {
        std::cout << *list->getOrder().at(i) << ' ';
    }

    //remove deploy2 from the list
    cout << "\nRemove deploy2" << endl;
    list->remove(deploy2);
    //print the list
    for (int i=0; i<list->getOrder().size(); ++i) {
        std::cout << *list->getOrder().at(i) << ' ';
    }

    //delete all the orders objects
    delete list;

}

