#include<string>
#include <iostream>
#include "Player.h"
class GameEngine
{
   
    
public:
  void start();
   void loaded();
   void validated();
   void assign();
   void issue();
   void execute();
   void win();
};
class Order
{
   private:
   std::string order;
   public:
   Order();
   //destructor
   ~Order();
   //constructor 
   Order(std::string name);
   
    friend std::ostream& operator << (std::ostream& strm, const Order& ord);
    friend std::istream& operator >> (std::istream& in, Order& ord);
};

