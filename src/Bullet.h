#pragma once
#include "Projectile.h"
class Bullet :
    public Projectile
{
public:
    Bullet(float x, float y, Game* game, float vx, float vy, int damage, int headshotDamage, Character* owner);
};

