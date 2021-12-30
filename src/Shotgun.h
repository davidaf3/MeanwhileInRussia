#pragma once
#include "Gun.h"
class Shotgun :
    public Gun
{
public:
    Shotgun(Game* game, Character* holder, int ammo);
    Projectile* createProjectile(float x, float y, float aim) override;
    string getName() override;
    int getNumber() override;

    static const int sgMagSize = 5;
    static const int sgFireRate = 30;
    static const int sgReloadLength = 165;
    static const int sgDamage = 10;
    static const int sgHeadshotDamage = 20;
};

