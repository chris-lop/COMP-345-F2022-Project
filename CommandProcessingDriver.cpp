#include <iostream>
#include "CommandProcessor.h"
#include "FileCommandProcessorAdapter.h"
using namespace std;

//checks the user input whether console or file and then tests out the CommandProcessor and FileCommandProcessorAdapter classes
void testCommandProcessor(){
 cout<<"enter console or file<filename> to start."<<endl;
    string choice;
    string start;
    string end;
    
    do{
    cin>>choice;
 
 
    start=choice.substr(0,5);
    end=choice.substr(choice.length()-1);
    
    if(choice=="console"){
   CommandProcessor* p=new CommandProcessor();
   p->start();
    }
    else
    if(start=="file<"&&end==">")
{
FileCommandProcessorAdapter* f=new FileCommandProcessorAdapter();
int i=choice.find(">");
f->set_f_name(choice.substr(5,i-5));
f->start();
}
else
cout<<"invalid entry. valid input: console, file<filename>."<<endl;
}
while(choice!="console"&&(start!="file<"||end!=">"));


}
