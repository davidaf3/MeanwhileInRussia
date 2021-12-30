#pragma once
#include "Collectable.h"
#include "Audio.h"

class Medkit :
    public Collectable
{
public:
    Medkit(float x, float y, Game* game);
    void collect(Player* player) override;

    static const int healthRecovered = Player::maxHealth / 5;
};

