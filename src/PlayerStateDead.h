#pragma once
#include "PlayerState.h"
class PlayerStateDead :
    public PlayerState
{
public:
	void update(Player* player) override;
	void draw(Player* player, float scrollX = 0, float scrollY = 0) override;
	void moveX(Player* player, int orientation) override;
	void moveY(Player* player, int orientation) override;
	void jump(Player* player) override;
	void selectGun(Player* player, int n) override;
	void selectNextGun(Player* player) override;
	void selectPreviousGun(Player* player) override;
	void reload(Player* player) override;
	void startFocus(Player* player) override;
	static PlayerStateDead* instance();
private:
	static PlayerStateDead* _instance;
	PlayerStateDead();
};
