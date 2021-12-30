#pragma once

#include "Actor.h"

typedef struct Level Level;

class Tile : public Actor
{
public:
	Tile(string filename, int tileNum, float x, float y, int tilesetWidth, int tilesetHeight, Game* game, Level* level);
	int tileNum;
	Level* level;
	void draw(float scrollX = 0, float scrollY = 0) override;
};