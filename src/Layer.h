#pragma once

#include "Game.h"
#include "Space.h"
#include "CharacterObserver.h"

class Game;

class Layer : public CharacterObserver
{
public:
	Layer(Game* game);
	virtual void init() {};
	virtual void processControls() {};
	virtual void update() {};
	virtual void draw() {};

	Space* space;
	Game* game;
};
