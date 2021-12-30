#pragma once
#include "OnAirPlayerState.h"

class Game;

class JumpingPlayerState :
    public OnAirPlayerState
{
public:
    void draw(Player* player, float scrollX, float scrollY) override;
    void beforeStateChange(Player* player) override;
    static JumpingPlayerState* instance(Game* game);
private:
    static JumpingPlayerState* _instance;
    JumpingPlayerState(Game* game);
    void doUpdate(Player* player) override;
};
