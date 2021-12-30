#pragma once

#include "Game.h"

class Animation
{
public:
	Animation(string filename, float actorWidth, float actorHeight,
		float fileWidth, float fileHeight,
		int updateFrecuence, int totalFrames, bool loop, Game* game);
	bool update();
	void draw(float x, float y, bool flip);
	void reset();

	SDL_Texture* texture;
	bool loop;
	float actorWidth;
	float actorHeight;
	float fileWidth;
	float fileHeight;
	int updateFrecuence;
	int totalFrames;
	int updateTime;
	int currentFrame;
	float frameWidth;
	float frameHeigt;
	SDL_Rect source;
	Game* game;
};

