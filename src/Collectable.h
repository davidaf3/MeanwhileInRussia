#pragma once
#include "Actor.h"
#include "Player.h"

class Collectable :
    public Actor
{
public:
    Collectable(string filename, float x, float y, int width, int height, Game* game);
    virtual ~Collectable();
    virtual void update();
    virtual void collect(Player* player);
};

