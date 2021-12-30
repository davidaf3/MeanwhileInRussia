#pragma once
#include "Gun.h"
class SniperRifle :
    public Gun
{
public:
    SniperRifle(Game* game, Character* holder, int ammo);
    Projectile* createProjectile(float x, float y, float aim) override;
    void draw(float scrollX = 0, float scrollY = 0) override;
    int getLineOfSight() override;
    string getName() override;
    int getNumber() override;

    float calculateY() override;

    static const int sMagSize = 10;
    static const int sFireRate = 35;
    static const int sReloadLength = 47;
    static const int sDamage = 100;
    static const int sHeadshotDamage = 200;
};

