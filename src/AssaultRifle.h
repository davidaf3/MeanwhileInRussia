#pragma once
#include "AutomaticGun.h"
class AssaultRifle :
    public AutomaticGun
{
public:
    AssaultRifle(Game* game, Character* holder, int ammo);
    Projectile* doCreateProjectile(float x, float y, float aim) override;
    int getLineOfSight() override;
    string getName() override;
    int getNumber() override;

    float calculateY() override;

    static const int arMagSize = 30;
    static const int arFireRate = 8;
    static const int arReloadLength = 47;
    static const int arDamage = 36;
    static const int arHeadshotDamage = 150;
    static const int arRecoil = 25;
    static const int arMinAccuracy = 30;
};

