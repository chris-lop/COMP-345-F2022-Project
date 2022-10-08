#include <iostream> 
#include "Orders.h"
#include <algorithm>

using std::cout;
using std::endl;


void testOrdersLists(){
    cout <<"### Test Orders ###" << endl;
    Order *order = new Order();
    cout << "Creating an Order object: " << *order << endl;

    Order *order2 = new Order();
    cout << "Creating an Order object: " << *order2 << endl;

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
    OrdersList* list = new OrdersList();
    list->addOrder(order);    
    list->addOrder(order2);
    list->addOrder(deploy);
    list->addOrder(deploy2);
    list->addOrder(advance);
    list->addOrder(bomb);
    list->addOrder(blockade);
    list->addOrder(airlift);
    list->addOrder(negotiate);


    for (int i=0; i<list->getOrder().size(); ++i) {
        std::cout << *list->getOrder().at(i) << ' ';
    }

    cout << "\n\n### validate() method ###" << endl;
   
    deploy->setValid(true);
    cout << "Set the \"valid\" paarameter of deploy to true: " << deploy->getValid() << endl;
    cout << "Run the valid() method for deploy: " << deploy->validate() << endl;

    bomb->setValid(false);
    cout << "\nSet the \"valid\" paarameter of bomb to false: " << bomb->getValid() << endl;
    cout << "Run the valid() method for bomb: " << bomb->validate() << endl;


    cout << "\n\n### execute() method ###" << endl;

    cout << "Run the execute() method for deploy: " << endl;
    deploy->execute();

    cout << "Run the execute() method for bomb: " <<  endl;
    bomb->execute();

    cout << "\n\n### move() method ###" << endl;
    int index;
    cout << "Move order2 to position 5" << endl;
    index = 5;
    list->move(order2,index);
    for (int i=0; i<list->getOrder().size(); ++i) {
        std::cout << *list->getOrder().at(i) << ' ';
    }

    cout << "\nMove negotiate to position 1" << endl;
    index = 1;

    list->move(negotiate,index);
    for (int i=0; i<list->getOrder().size(); ++i) {
        std::cout << *list->getOrder().at(i) << ' ';
    }



    cout << "\n\n### remove() method ###" << endl;
    cout << "Remove order2" << endl;
    list->remove(order2);
    for (int i=0; i<list->getOrder().size(); ++i) {
        std::cout << *list->getOrder().at(i) << ' ';
    }

    cout << "\nRemove deploy2" << endl;
    list->remove(deploy2);
    for (int i=0; i<list->getOrder().size(); ++i) {
        std::cout << *list->getOrder().at(i) << ' ';
    }

    delete order, order2, deploy2, deploy, advance, 
            bomb, blockade, airlift, negotiate;

}

