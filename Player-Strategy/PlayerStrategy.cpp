#include "PlayerStrategy.h"
#include "../Player.h"

PlayerStrategy::PlayerStrategy(Player* p): p(p){}

PlayerStrategy::~PlayerStrategy() {
    // Freeing the Player* is the job of the player's owner,
    // and the Player has the job of freeing its PlayerStrategy
}