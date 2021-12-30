#pragma once
#include "AutomaticGun.h"
class RicochetGun :
    public AutomaticGun
{
public:
    RicochetGun(Game* game, Character* holder, int ammo);
    Projectile* doCreateProjectile(float x, float y, float aim) override;
    string getName() override;
    int getNumber() override;
    float calculateX() override;

    static const int rgMagSize = 16;
    static const int rgFireRate = 6;
    static const int rgReloadLength = 48;
    static const int rgDamage = 25;
    static const int rgHeadshotDamage = 50;
    static const int rgRecoil = 10;
    static const int rgMinAccuracy = 70;
};

