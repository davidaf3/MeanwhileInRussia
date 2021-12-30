#pragma once
#include "Game.h"

class InputController
{
public:
	InputController(Game* game);
	void init();
	void processControls();
	void inputToControls(SDL_Event event);

	Game* game;

	bool controlShoot = false;
	bool controlReload = false;
	bool controlContinue = false;
	bool controlCrouch = false;
	bool controlGetUp = false;
	bool controlJump = false;
	bool controlSelectGun = false;
	bool controlNextGun = false;
	bool controlPreviousGun = false;
	bool toggleFocus = false;

	int selectedGun = 1;
	int controlAimX = 0;
	int controlAimY = 0;
	int controlMoveX = 0;

	static const int halfCursorSide = 10;
};
