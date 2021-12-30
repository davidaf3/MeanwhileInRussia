#pragma once
#include "Collectable.h"
#include "Audio.h"

class FokusnoffBottle :
    public Collectable
{
public:
    FokusnoffBottle(float x, float y, Game* game);
    void collect(Player* player) override;

    static const int focusRecovered = Player::maxFocus / 3;
};
