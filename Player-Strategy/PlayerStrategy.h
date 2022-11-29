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

class AggressivePlayerStrategy : public PlayerStrategy {
public:
    AggressivePlayerStrategy(Player* p);
    virtual ~AggressivePlayerStrategy();

    virtual void issueOrder();
    virtual std::vector <Territory*> toAttack();
    virtual std::vector <Territory*> toDefend();
};

class NeutralPlayerStrategy : public PlayerStrategy {
public:
    NeutralPlayerStrategy(Player* p);
    virtual ~NeutralPlayerStrategy();

    virtual void issueOrder();
    virtual std::vector <Territory*> toAttack();
    virtual std::vector <Territory*> toDefend();
};

// A3 free function
void testPlayerStrategies();