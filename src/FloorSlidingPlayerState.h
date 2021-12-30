#pragma once
#include "PlayerState.h"
class FloorSlidingPlayerState :
    public PlayerState
{
public:
    void update(Player* player) override;
    void jump(Player* player) override;
    void moveX(Player* player, int orientation) override;
    void moveY(Player* player, int orientation) override;
    void draw(Player* player, float scrollX, float scrollY) override;
    bool isHeadshot(Player* player, Projectile* projectile) override;
    void afterStateChange(Player* player) override;
    void beforeStateChange(Player* player) override;
    static FloorSlidingPlayerState* instance(Game* game);

    Space* space;
    int orientation = 1;
    bool slideEnded = false;
    int reduceSpeedTime = 5;
    static const int initialSpeed = 5;
    static const int endSpeed = 1;
    static const int reduceSpeedInterval = 5;
private:
    static FloorSlidingPlayerState* _instance;
    FloorSlidingPlayerState(Game* game);
};

