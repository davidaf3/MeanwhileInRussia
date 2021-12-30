#pragma once
#include "Projectile.h"
class Pellet :
    public Projectile
{
public:
    Pellet(float x, float y, Game* game, float vx, float vy, int damage, int headshotDamage, Character* owner);
};
