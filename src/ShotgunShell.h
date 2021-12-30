#pragma once
#include "Projectile.h"
#include "Pellet.h"

class ShotgunShell :
    public Projectile
{
public:
    ShotgunShell(float x, float y, Game* game, float vx, float vy, int damage, int headshotDamage, Character* owner);
    void update() override;
    void draw(float scrollX = 0, float scrollY = 0) override;
    bool isOverlap(Actor* actor) override;
    virtual void hit(Character* character) override;
    void addToSpace(Space* space) override;
    void move(float deltaX, float deltaY) override;
    Pellet* pellets[10];
};

