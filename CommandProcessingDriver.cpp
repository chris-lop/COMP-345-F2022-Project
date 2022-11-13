#include <iostream>
#include "CommandProcessor.h"
using namespace std;

// checks the user input whether console or file and then tests out the CommandProcessor and FileCommandProcessorAdapter classes
void testCommandProcessor(string choice)
{

    // cin>>choice;
    // if the user chooses console then they will be prompted to enter the commands
    if (choice.find("console") == 0)
    {
        CommandProcessor *p = new CommandProcessor();
        p->start();
    }
    else
        // if the use chooses file then the commands will be read from the file
        if (choice.find("file") == 0)
        {
            FileCommandProcessorAdapter *f = new FileCommandProcessorAdapter();
            f->set_f_name("commands.txt");
            f->start();
        }
        else
            cout << "invalid entry. valid input: console, file<filename>." << endl;
}
