#pragma once
#include "PlayerState.h"
class CrouchedPlayerState :
    public PlayerState
{
public:
    void jump(Player* player) override;
    void moveX(Player* player, int orientation) override;
    void moveY(Player* player, int orientation) override;
    void getUp(Player* player, Space* space) override;
    void afterStateChange(Player* player) override;
    void beforeStateChange(Player* player) override;
    static CrouchedPlayerState* instance(Game* game);
private:
    static CrouchedPlayerState* _instance;
    CrouchedPlayerState(Game* game);
};

