#pragma once
#include "PlayerState.h"
#include "Animation.h"
#include "Audio.h"

class Game;

class OnAirPlayerState :
    public PlayerState
{
public:
    void update(Player* player) override;
    void jump(Player* player) override;
    void beforeStateChange(Player* player) override;
    static OnAirPlayerState* instance(Game* game);
    Audio* fallAudio;
private:
    static OnAirPlayerState* _instance;
protected:
    OnAirPlayerState(Game* game);
    virtual void doUpdate(Player* player);
};
