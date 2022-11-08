#include <iostream>
#include "CommandProcessor.h"
#include "FileCommandProcessorAdapter.h"
using namespace std;

//checks the user input whether console or file and then tests out the CommandProcessor and FileCommandProcessorAdapter classes
void testCommandProcessor(){
      cout<<"enter console or file to start."<<endl;
    string choice;
    do{
    cin>>choice;
    if(choice=="console"){
   CommandProcessor* p=new CommandProcessor();
   p->start();
    }
    else
    if(choice=="file")
{
FileCommandProcessorAdapter* f=new FileCommandProcessorAdapter();
f->start();
}
else
cout<<"invalid entry. valid input: console, file."<<endl;
}
while(choice!="console"&&choice!="file");
}
