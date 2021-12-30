#pragma once
#include "AutomaticGun.h"
class SMG :
    public AutomaticGun
{
public:
    SMG(Game* game, Character* holder, int ammo);
    Projectile* doCreateProjectile(float x, float y, float aim) override;
    string getName() override;
    int getNumber() override;

    static const int smgMagSize = 32;
    static const int smgFireRate = 4;
    static const int smgReloadLength = 48;
    static const int smgDamage = 15;
    static const int smgHeadshotDamage = 50;
    static const int smgRecoil = 15;
    static const int smgMinAccuracy = 60;
};
