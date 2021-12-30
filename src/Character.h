#pragma once
#include "Actor.h"
#include "Gun.h"
#include "Projectile.h"
#include "CharacterObserver.h"
#include "Audio.h"
#include <list>

class Space;

class Character :
    public Actor
{
public:
    Character(string filename, float x, float y, int width, int height, int health, Game* game, int headHeight);
    virtual ~Character();
    void update();
    virtual void doUpdate();
    void draw(float scrollX = 0, float scrollY = 0) override;
    virtual void doDraw(float scrollX, float scrollY);

    void shoot();
    virtual void reload();

    virtual void takeHit(int damage);
    virtual void setHealth(int health);
    virtual bool isHeadshot(Projectile* projectile);
    void onDead();
    virtual void doOnDead();
    int health;
    int maxHealth;
    bool isDead = false;
    bool hitRight = false;
    bool hitLeft = false;
    int headHeight;

    float lastVy;

    float aim;
    void aimAt(int x, int y);
    bool isLookingRight();
    Gun* gun;

    Audio* hitSound;

    list<CharacterObserver*> observers;

    virtual string getAmmoString();
    virtual string getHealthString();
    virtual string getFocusString();
};

