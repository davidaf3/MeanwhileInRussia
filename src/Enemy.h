#pragma once
#include "Character.h"
#include "Animation.h"
#include "EnemyState.h"

class Enemy :
    public Character
{
public:
    Enemy(float x, float y, Game* game, int nGun, Character* objective, string kind, int health, float aim);
    ~Enemy() override;
    void doDraw(float scrollX, float scrollY) override;
    void doUpdate() override;
    void changeState(EnemyState* newState);
    void doOnDead() override;
    string kind;
    Character* objective;
    EnemyState* state;

    Animation* aliveAnimation;
    Animation* shotFrontAnimation;
    Animation* shotBehindAnimation;
    Animation* deadAnimation;
};

