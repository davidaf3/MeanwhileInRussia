#pragma once
#include "Bullet.h"
class SniperBullet :
    public Bullet
{
public:
    SniperBullet(float x, float y, Game* game, float vx, float vy, int damage, int headshotDamage, Character* owner);
    void hit(Character* character) override;
};
