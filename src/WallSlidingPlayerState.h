#pragma once
#include "PlayerState.h"
#include "Animation.h"

class Game;

class WallSlidingPlayerState :
    public PlayerState
{
public:
    void update(Player* player) override;
    void draw(Player* player, float scrollX, float scrollY) override;
    void jump(Player* player) override;
    Animation* inverseAnimation;
    static WallSlidingPlayerState* instance(Game* game);
private:
    static WallSlidingPlayerState* _instance;
    WallSlidingPlayerState(Game* game);
};

