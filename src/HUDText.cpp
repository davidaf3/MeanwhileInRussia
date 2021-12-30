#include "HUDText.h"

HUDText::HUDText(string iconFilename, int iconFileWidth, int iconFileHeight, int iconWidth, int iconHeight, bool iconLeft,
        bool anchorLeft, float x, float y, string initialContent, Game* game) {
	this->font = game->getFont("res/sans.ttf", 26);
	this->fontOutline = game->getFont("res/sans.ttf", 26, 2);
    this->iconTexture = game->getTexture(iconFilename);
    this->iconFileWidth = iconFileWidth;
    this->iconFileHeight = iconFileHeight;
    this->iconWidth = iconWidth;
    this->iconHeight = iconHeight;
    this->x = x;
    this->y = y;
    this->iconLeft = iconLeft;
	this->anchorLeft = anchorLeft;
	this->content = initialContent;
    this->game = game;
}

void HUDText::draw() {
	// Para que parezca que el texto tiene borde, creamos dos texturas a partir
	// del texto, una con letras más gruesas que la otra, y las fusionamos
	SDL_Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	SDL_Color borderColor;
	borderColor.r = 0;
	borderColor.g = 0;
	borderColor.b = 0;
	borderColor.a = 255;

	SDL_Surface* surface = TTF_RenderText_Blended(font, content.c_str(), color);
	SDL_Surface* borderSurface = TTF_RenderText_Blended(fontOutline, content.c_str(), borderColor);

	if (surface != NULL && borderSurface != NULL) {
		SDL_Rect borderRect;
		borderRect.x = TEXT_BORDER;
		borderRect.y = TEXT_BORDER;
		borderRect.w = borderSurface->w;
		borderRect.h = borderSurface->h;

		SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
		SDL_BlitSurface(surface, NULL, borderSurface, &borderRect);
		SDL_FreeSurface(surface);

		SDL_Rect textRect;
		textRect.x = x + (iconLeft ? iconWidth + textIconSeparation : -iconWidth - textIconSeparation - borderSurface->w);
		textRect.y = y - borderSurface->h / 2 - TEXT_BORDER;
		textRect.w = borderSurface->w;
		textRect.h = borderSurface->h;

		SDL_Texture* texture = SDL_CreateTextureFromSurface(game->renderer, borderSurface);
		SDL_FreeSurface(borderSurface);
		SDL_RenderCopy(game->renderer, texture, NULL, &textRect);
		SDL_DestroyTexture(texture);
	}

	SDL_Rect iconSource;
	iconSource.x = 0;
	iconSource.y = 0;
	iconSource.w = iconFileWidth;
	iconSource.h = iconFileHeight;

	SDL_Rect iconDest;
	iconDest.x = x - (iconLeft ? 0 : iconWidth);
	iconDest.y = y - iconHeight / 2;
	iconDest.w = iconWidth;
	iconDest.h = iconHeight;

	SDL_RenderCopyEx(game->renderer,
		iconTexture, &iconSource, &iconDest, 0, NULL, SDL_FLIP_NONE);
}

void HUDText::onCharacterDead(Character* character, GunCollectable* droppedGun) {
	onCharacterDeadLambda(this, character, droppedGun);
}

void HUDText::onEnemyKilled() {
	onEnemyKilledLambda(this);
}

void HUDText::onCharacterFire(Projectile* projectile) {
	onCharacterFireLambda(this, projectile);
}

void HUDText::onCharacterAmmoChange(Character* character) {
	onCharacterAmmoChangeLambda(this, character);
}

void HUDText::onCharacterHealthChange(Character* character) {
	onCharacterHealthChangeLambda(this, character);
}

void HUDText::onCharacterFocusChange(Character* character) {
	onCharacterFocusChangeLambda(this, character);
}