#pragma once
#include "Gun.h"

class Pistol :
    public Gun
{
public:
    Pistol(Game* game, Character* holder, int ammo);
    Projectile* createProjectile(float x, float y, float aim) override;
    string getName() override;

    static const int pistolMagSize = 9;
    static const int pistolFireRate = 20;
    static const int pistolReloadLength = 48;
    static const int pistolDamage = 25;
    static const int pistolHeadshotDamage = 100;
};

