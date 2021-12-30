#pragma once
#include "Game.h"

class Text
{
public:
	Text(string fontname, int size, string content, SDL_Color color, float x, float y, Game* game);
	void draw();
	TTF_Font* font;
	SDL_Color color;
	string content;
	float x;
	float y;
	Game* game;
};

