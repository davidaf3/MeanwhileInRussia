#pragma once
#include "Collectable.h"
#include "Gun.h"
#include "Audio.h"

class GunCollectable :
    public Collectable
{
public:
    GunCollectable(Gun* gun);
    ~GunCollectable() override;
    void collect(Player* player) override;
    void update() override;
    void draw(float scrollX = 0, float scrollY = 0) override;
    Gun* gun;
};

