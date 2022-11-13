#include <iostream>
#include "CommandProcessor.h"
using namespace std;

//checks the user input whether console or file and then tests out the CommandProcessor and FileCommandProcessorAdapter classes
void testCommandProcessor(){
    cout<<"enter console or file<filename> to start."<<endl;
    string choice;
    string copy;
    
    do{
        cin>>choice;
        copy = choice;
        if(choice=="console"){
            CommandProcessor* p=new CommandProcessor();
            p->start();
        }
        else
        if(choice.find("file") == 0) {
            FileCommandProcessorAdapter* f=new FileCommandProcessorAdapter();
            f->set_f_name("commands.txt");
            f->start();
        }
        else
            cout<<"invalid entry. valid input: console, file<filename>."<<endl;
        }
    while(choice!="console"&&copy.find("file") == string::npos);

    cout<<"------SECOND GAME TEST -------"<<endl;

    cout<<"enter console or file<filename> to start."<<endl;

    do{
        cin>>choice;
        copy = choice;
        if(choice=="console"){
            CommandProcessor* p=new CommandProcessor();
            p->start();
        }
        else
        if(choice.find("file") == 0) {
            FileCommandProcessorAdapter* f=new FileCommandProcessorAdapter();
            f->set_f_name("commands.txt");
            f->start();
        }
        else
            cout<<"invalid entry. valid input: console, file<filename>."<<endl;
        }
    while(choice!="console"&&copy.find("file") == string::npos);



}

