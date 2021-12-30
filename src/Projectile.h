#pragma once
#include "Actor.h"
#include "Audio.h"

class Space;

class Character;

class Projectile :
    public Actor
{
public:
    Projectile(string filename, float x, float y, int width, int height, Game* game, float vx, float vy, 
        int damage, int headshotDamage, Character* owner);
    virtual ~Projectile();
    virtual void update();
    virtual void draw(float scrollX = 0, float scrollY = 0) override;
    virtual void hit(Character* character);
    virtual void onCollision();
    virtual void addToSpace(Space* space);
    virtual void removeFromSpace(Space* space);
    virtual void move(float deltaX, float deltaY);
    float getTipY();
    float getTipX();
    bool gravity() override;
    int timeToLive;
    float initialWidth;
    float initialHeight;
    int damage;
    int headshotDamage;
    Character* owner;
};

