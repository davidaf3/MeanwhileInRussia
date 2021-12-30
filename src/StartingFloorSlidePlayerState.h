#pragma once
#include "PlayerState.h"
class StartingFloorSlidePlayerState :
    public PlayerState
{
public:
    void update(Player* player) override;
    void jump(Player* player) override;
    void moveX(Player* player, int orientation) override;
    void moveY(Player* player, int orientation) override;
    void draw(Player* player, float scrollX, float scrollY) override;
    static StartingFloorSlidePlayerState* instance(Game* game, Space* space);
    Space* space;
private:
    static StartingFloorSlidePlayerState* _instance;
    StartingFloorSlidePlayerState(Game* game);
};

