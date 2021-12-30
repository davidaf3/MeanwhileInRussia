#pragma once
#include "Bullet.h"
class RicochetBullet :
    public Projectile
{
public:
    RicochetBullet(float x, float y, Game* game, float vx, float vy, int damage, int headshotDamage, Character* owner);
    void onCollision() override;

    int lastVx;
    int lastVy;
};

