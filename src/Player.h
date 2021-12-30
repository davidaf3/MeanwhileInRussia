#pragma once
#include "Character.h"
#include "PlayerState.h"
#include "Space.h"
#include "Audio.h"
#include <set>

class Player :
    public Character
{
public:
	Player(float x, float y, set<int> gunsInventory, map<string, int> ammoInventory, int nGun, Game* game);
	~Player() override;
	void doUpdate() override;
	void doDraw(float scrollX = 0, float scrollY = 0) override;
	void doOnDead() override;
	bool isHeadshot(Projectile* projectile) override;
	void jump();
	void crouch(Space* space);
	void getUp(Space* space);
	void moveX(int orientation);
	void moveY(int orientation);

	void selectGun(int n);
	void selectNextGun();
	void selectPreviousGun();
	void reload() override;
	int getAmmoForCurrentGun();
	
	PlayerState* state;
	void changeState(PlayerState* newState);

	static const int standingHeight = 48;
	static const int standingWidht = 18;
	static const int crouchedHeight = 36;
	static const int floorSlidingHeight = 22;
	static const int floorSlidingWidth = 46;
	static const int headHeight = 14;

	static const int maxHealth = 1000;
	static const int maxFocus = 100;
	static const int focusReloadStep = 15;

	bool focus = false;
	int focusLeft;
	int lastFocusReload = 0;

	void startFocus();
	void stopFocus();
	void setFocusLeft(int focusLeft);

	Animation* shotFrontAnimation;
	Animation* shotBehindAnimation;
	Animation* deadAnimation;

	Audio* weaponSwitchSound;
	Audio* drinkAudio;
	Audio* healAudio;
	Audio* pickupAudio;

	Gun* gunsInventory[8];
	map<string, int> ammoInventory;

	string getAmmoString() override;
	string getFocusString() override;
};

