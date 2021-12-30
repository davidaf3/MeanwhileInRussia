#pragma once
#include "Gun.h"
class BFG :
    public Gun
{
public:
    BFG(Game* game, Character* holder);
    BFG(Game* game, float x, float y);
    void init();
    Projectile* createProjectile(float x, float y, float aim) override;
    string getName() override;
    int getNumber() override;
    string getAmmoString() override;

    static const int bfgMagSize = 1;
    static const int bfgFireRate = 150;
    static const int bfgReloadLength = 0;
    static const int bfgDamage = 100;
    static const int bfgHeadshotDamage = 100;
};

