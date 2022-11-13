#include <iostream> 
#include "LoggingObserver.h"
#include "CommandProcessor.h"
#include "GameEngine.h"
#include "Orders.h"
#include <algorithm>

using std::cout;
using std::endl;

void testOrdersLists(){
    cout << "---- PART 5 TESTS ----" << endl;
    cout << "Creating a Command object of loadmap" << endl;
    Command* command = new Command("loadmap", "");
    cout << "Checking if Command is a subclass of Subject and ILoggable"<<endl;
    if(dynamic_cast<Subject*>(command) && dynamic_cast<ILoggable*>(command)){
        cout << "The command object is a subclass of Subject and ILoggable" << endl;
    }
    else{
        cout << "The command object is NOT a subclass of Subject and ILoggable" << endl;
    }

    cout << "\nCreating a CommandProcessor object" << endl;
    CommandProcessor* commandProcessor = new CommandProcessor();
    cout << "Checking if CommandProcessor is a subclass of Subject and ILoggable"<<endl;
    if(dynamic_cast<Subject*>(commandProcessor) && dynamic_cast<ILoggable*>(commandProcessor)){
        cout << "The CommandProcessor object is a subclass of Subject and ILoggable" << endl;
    }
    else{
        cout << "The CommandProcessor object is NOT a subclass of Subject and ILoggable" << endl;
    }

    cout << "\nCreating an Order object of Deploy" << endl;
    Deploy* order = new Deploy();
    cout << "Checking if Deplooy is a subclass of Subject and ILoggable"<<endl;
    if(dynamic_cast<Subject*>(order) && dynamic_cast<ILoggable*>(order)){
        cout << "The Order object is a subclass of Subject and ILoggable" << endl;
    }
    else{
        cout << "The Order object is NOT a subclass of Subject and ILoggable" << endl;
    }

    cout << "\nCreating an OrdersList object" << endl;
    OrdersList* ordersList = new OrdersList();
    cout << "Checking if OrdersList is a subclass of Subject and ILoggable"<<endl;
    if(dynamic_cast<Subject*>(ordersList) && dynamic_cast<ILoggable*>(ordersList)){
        cout << "The OrdersList object is a subclass of Subject and ILoggable" << endl;
    }
    else{
        cout << "The OrdersList object is NOT a subclass of Subject and ILoggable" << endl;
    }

    cout << "\nCreating a GameEngine object" << endl;
    GameEngine* gameEngine = new GameEngine();
    cout << "Checking if GameEngine is a subclass of Subject and ILoggable"<<endl;
    if(dynamic_cast<Subject*>(gameEngine) && dynamic_cast<ILoggable*>(gameEngine)){
        cout << "The GameEngine object is a subclass of Subject and ILoggable" << endl;
    }
    else{
        cout << "The GameEngine object is NOT a subclass of Subject and ILoggable" << endl;
    }

    cout << "\nTesting the observer pattern's notify(this) in Command::saveEffect()" << endl;
    command->saveEffect("testing");
    cout << "\nTesting the observer pattern's notify(this) in CommandProcessor::saveCommand()" << endl;
    commandProcessor->saveCommand(command);
    cout << "\nTesting the observer pattern's notify(this) in Order::execute()" << endl;
    // order->execute();
    cout << "\nTesting the observer pattern's notify(this) in OrderList::addOrder()" << endl;
    ordersList->addOrder(order);
    cout << "\nTesting the observer pattern's notify(this) in GameEngine::transition()" << endl;
    gameEngine->setState("start");
    gameEngine->transition();
}




