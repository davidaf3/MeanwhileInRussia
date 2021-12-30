#pragma once
#include "OnAirPlayerState.h"

class WallJumpingPlayerState :
    public OnAirPlayerState
{
public:
    int jumpFrames = 0;
    static int const totalJumpFrames = 10;
    void moveX(Player* player, int orientation) override;
    void moveY(Player* player, int orientation) override;
    void beforeStateChange(Player* player) override;
    static WallJumpingPlayerState* instance(Game* game);
private:
    static WallJumpingPlayerState* _instance;
    WallJumpingPlayerState(Game* game);
    void doUpdate(Player* player) override;
};

