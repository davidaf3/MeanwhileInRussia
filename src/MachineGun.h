#pragma once
#include "AutomaticGun.h"
class MachineGun :
    public AutomaticGun
{
public:
    MachineGun(Game* game, Character* holder, int ammo);
    Projectile* doCreateProjectile(float x, float y, float aim) override;
    int getLineOfSight() override;
    string getName() override;
    int getNumber() override;

    float calculateY() override;

    static const int mgMagSize = 100;
    static const int mgFireRate = 6;
    static const int mgReloadLength = 270;
    static const int mgDamage = 35;
    static const int mgHeadshotDamage = 90;
    static const int mgRecoil = 15;
    static const int mgMinAccuracy = 0;
};

