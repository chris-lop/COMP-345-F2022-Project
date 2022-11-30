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
    virtual bool issueOrder() = 0;
    virtual std::vector <Territory*> toAttack() = 0;
    virtual std::vector <Territory*> toDefend() = 0;
};

class AggressivePlayerStrategy : public PlayerStrategy {
public:
    AggressivePlayerStrategy(Player* p);
    virtual ~AggressivePlayerStrategy();

    virtual bool issueOrder();
    virtual std::vector <Territory*> toAttack();
    virtual std::vector <Territory*> toDefend();
};

class NeutralPlayerStrategy : public PlayerStrategy {
public:
    NeutralPlayerStrategy(Player* p);
    virtual ~NeutralPlayerStrategy();

    virtual bool issueOrder();
    virtual std::vector <Territory*> toAttack();
    virtual std::vector <Territory*> toDefend();
};

class HumanPlayerStrategy : public PlayerStrategy {
public:
    HumanPlayerStrategy(Player* p);
    virtual ~HumanPlayerStrategy();

    virtual bool issueOrder();
    virtual std::vector <Territory*> toAttack();
    virtual std::vector <Territory*> toDefend();
    // Variable to keep track of reinforcement
    int deployed_unit = 0;
};

class BenevolentPlayerStrategy : public PlayerStrategy {
public:
    BenevolentPlayerStrategy(Player* p);
    virtual ~BenevolentPlayerStrategy();

    virtual bool issueOrder();
    virtual std::vector <Territory*> toAttack();
    virtual std::vector <Territory*> toDefend();
    // Variable to keep track of reinforcement
    int deployed_unit = 0;
};

class CheaterPlayerStrategy: public PlayerStrategy {
public:
    CheaterPlayerStrategy(Player* p);
    virtual ~CheaterPlayerStrategy();

    virtual bool issueOrder();
    virtual std::vector <Territory*> toAttack();
    virtual std::vector <Territory*> toDefend();
private:
    int previousArmyNumber;
};

// A3 free function
void testPlayerStrategies();