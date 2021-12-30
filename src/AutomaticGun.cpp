#include "AutomaticGun.h"

AutomaticGun::AutomaticGun(string filename, int width, int height, Game* game, Character* holder, int cannonHeight,
        int ammo, int magSize, int fireRate, int ammoPerShot, int reloadLength, int minAccuracy, int recoil) : 
            Gun(filename, width, height, game, holder, cannonHeight, ammo, magSize, fireRate, ammoPerShot, reloadLength) {
    this->minAccuracy = minAccuracy;
    this->recoil = recoil;
}

void AutomaticGun::update() {
    Gun::update();
    accuracy = accuracy + 2 < 100 ? accuracy + 2 : 100;
}

Projectile* AutomaticGun::createProjectile(float x, float y, float aim) {
    float dispersion = (100 - (float) accuracy) / 100.0;
    float newAim = aim + (rand() % 100 / 100.0 - 0.5) * dispersion;
    Projectile* projectile = doCreateProjectile(x, y, newAim);
    accuracy = accuracy - recoil > minAccuracy ? accuracy - recoil : minAccuracy;
    return projectile;
}

Projectile* AutomaticGun::doCreateProjectile(float x, float y, float aim) {
    return NULL;
}