#pragma once
#include "Actor.h"
#include "Projectile.h"
#include "Audio.h"

class GunCollectable;

class Character;

class Gun :
    public Actor
{
public:
    Gun(string filename, int width, int height, Game* game, Character* holder, int cannonHeight, 
        int ammo, int magSize, int fireRate, int ammoPerShot, int reloadLength);
    Gun(string filename, float x, float y, int width, int height, Game* game, int cannonHeight,
        int ammo, int magSize, int fireRate, int ammoPerShot, int reloadLength);
    virtual ~Gun();
    virtual void update();
    virtual bool canShoot();
    virtual void reload(int ammo);
    virtual void unload(int ammo);
    virtual Projectile* createProjectile(float x, float y, float aim);
    virtual Projectile* shoot(float aim);
    void draw(float scrollX = 0, float scrollY = 0) override;

    virtual void cancelReload();
    virtual void holster();
    virtual GunCollectable* drop();

    virtual int getLineOfSight();
    void notifyHolderObservers();
    virtual string getName();
    virtual int getNumber();
    virtual string getAmmoString();

    Character* holder;
    float tilt;
    float centerToCannon; // Distancia entre el centro del arma y la punta del cañón
    float centerToCannonAngle; // Ángulo que forma la recta que une el centro del arma y la punta del cañón con el eje X
    int cannonHeight;
    int ammo;
    int nextReloadAmmo = 0;
    int magSize;
    int fireRate;
    int lastShot;
    int ammoPerShot;
    int reloadLength;
    int reloadTime;

    virtual float calculateX();
    virtual float calculateY();

    virtual void playShotSound();
    virtual void playReloadSound();
    Audio* shotSound = NULL;
    Audio* reloadSound = NULL;
    Audio* outOfAmmoSound;
};

