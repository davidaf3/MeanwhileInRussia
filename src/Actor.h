#pragma once

#include "Game.h"

class Actor
{
public:
	Actor(string filename, float x, float y, int width, int height, Game* game);
	~Actor();
	virtual void draw(float scrollX = 0, float scrollY = 0);
	virtual bool isOverlap(Actor* actor);
	bool isOverlap(float x, float y, float width, float height);
	bool isInRender(float scrollX = 0, float scrollY = 0);
	bool containsPoint(int pointX, int pointY);
	virtual bool gravity();
	bool collisionTop;
	bool collisionDown;
	bool collisionLeft;
	bool collisionRight;
	bool outRight;
	bool outLeft;
	SDL_Texture* texture;
	float x;
	float y;
	float vx;
	float vy;
	int width;
	int height;
	int fileWidth;
	int fileHeight;
	Game* game;
};
