#pragma once
#include <vector>

class Player;
class Territory;

class PlayerStrategy {
protected:
    Player *p;
public:
    PlayerStrategy(Player* p);
    virtual ~PlayerStrategy();
    virtual void issueOrder() = 0;
    virtual std::vector <Territory*> toAttack() = 0;
    virtual std::vector <Territory*> toDefend() = 0;
};