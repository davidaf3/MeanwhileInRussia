#pragma once
#include "PlayerState.h"
#include "Animation.h"
#include "Audio.h"

class RunningPlayerState :
    public PlayerState
{
public:
    void update(Player* player) override;
    void crouch(Player* player, Space* space) override;
    void beforeStateChange(Player* player) override;
    void afterStateChange(Player* player) override;
    static RunningPlayerState* instance(Game* game);
    Audio* stepsSound;
private:
    static RunningPlayerState* _instance;
    RunningPlayerState(Game* game);
};



