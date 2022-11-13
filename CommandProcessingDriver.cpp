#include <iostream>
#include "CommandProcessor.h"
using namespace std;

//checks the user input whether console or file and then tests out the CommandProcessor and FileCommandProcessorAdapter classes
void testCommandProcessor(){
    //asks user to choose how to enter the input
    cout<<"enter console or file<filename> to start."<<endl;
    string choice;
    string copy;
    
    do{
        //cin>>choice;
        getline(cin,choice);
        copy = choice;
        //if the user chooses console then they will be prompted to enter the commands
        if(choice=="console"){
            CommandProcessor* p=new CommandProcessor();
            p->start();
        }
        else
        //if the use chooses file then the commands will be read from the file 
        if(choice.find("file") == 0) {
            FileCommandProcessorAdapter* f=new FileCommandProcessorAdapter();
            f->set_f_name("commands.txt");
            f->start();
        }
        else
            cout<<"invalid entry. valid input: console, file<filename>."<<endl;
        }
        //keeps on repeating until user selects either console or file
    while(choice!="console"&&copy.find("file") == string::npos);

    cout<<"------SECOND GAME TEST -------"<<endl;

    cout<<"enter console or file<filename> to start."<<endl;

    do{
        //cin>>choice;
        getline(cin,choice);
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

