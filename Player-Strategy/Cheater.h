#include "PlayerStrategy.h"
#include "../Player.h"
#include <vector>

class Cheater: public PlayerStrategy {
public:
    Cheater(Player* p);
    virtual ~Cheater();

    virtual void issueOrder();
    virtual std::vector <Territory*> toAttack();
    virtual std::vector <Territory*> toDefend();
};