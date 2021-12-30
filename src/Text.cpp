#include "Text.h"

Text::Text(string fontname, int size, string content, SDL_Color color, float x, float y, Game* game) {
	this->font = game->getFont(fontname, size);
	this->content = content;
	this->color = color;
	this->x = x;
	this->y = y;
	this->game = game;
}

void Text::draw() {
	SDL_Surface* surface = TTF_RenderText_Blended(font, content.c_str(), color);

	SDL_Rect textRect;
	textRect.x = x;
	textRect.y = y;
	textRect.w = surface->w;
	textRect.h = surface->h;

	SDL_Texture* texture = SDL_CreateTextureFromSurface(game->renderer, surface);
	SDL_RenderCopy(game->renderer, texture, NULL, &textRect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}