#pragma once
#include "Gun.h"
class AutomaticGun :
    public Gun
{
public:
    AutomaticGun(string filename, int width, int height, Game* game, Character* holder, int cannonHeight,
        int ammo, int magSize, int fireRate, int ammoPerShot, int reloadLength, int minAccuracy, int recoil);
    void update() override;
    Projectile* createProjectile(float x, float y, float aim) override;
    virtual Projectile* doCreateProjectile(float x, float y, float aim);

    int accuracy = 100;
    int minAccuracy;
    int recoil;
};

