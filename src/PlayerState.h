#pragma once
#include "Animation.h"

class Space;

class Player;

class Projectile;

class PlayerState
{
public:
	virtual void draw(Player* player, float scrollX, float scrollY);
	virtual void update(Player* player);
	virtual void moveX(Player* player, int orientation);
	virtual void moveY(Player* player, int orientation);
	virtual void jump(Player* player);
	virtual void crouch(Player* player, Space* space);
	virtual void getUp(Player* player, Space* space);
	virtual bool isHeadshot(Player* player, Projectile* projectile);
	virtual void selectGun(Player* player, int n);
	virtual void selectNextGun(Player* player);
	virtual void selectPreviousGun(Player* player);
	virtual void reload(Player* player);
	virtual void startFocus(Player* player);
	virtual void onDead(Player* player);

	virtual void beforeStateChange(Player* player);
	virtual void afterStateChange(Player* player);

	Animation* animation;
};

