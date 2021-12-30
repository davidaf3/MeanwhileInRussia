#pragma once
#include "Projectile.h"
#include "Animation.h"
#include "Audio.h"

class BFGProjectile :
    public Projectile
{
public:
    BFGProjectile(float x, float y, Game* game, float vx, float vy, int damage, int headshotDamage, Character* owner);
    void update() override;
    void draw(float scrollX = 0, float scrollY = 0) override;
    void hit(Character* character) override;
    void onCollision() override;
    void explode();

    Animation* explosion;
    int explosionTimer = 30;
    bool exploded = false;

    Audio* explosionSound;
};

