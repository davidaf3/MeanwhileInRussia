#pragma once
#include "PlayerState.h"
#include "Animation.h"

class IdlePlayerState :
    public PlayerState
{
public:
    void update(Player* player) override;
    void crouch(Player* player, Space* space) override;
    static IdlePlayerState* instance(Game* game);
private:
    static IdlePlayerState* _instance;
    IdlePlayerState(Game* game);
};

