#include "SniperRifle.h"
#include "SniperBullet.h"
#include "Character.h"
#include "WAVAudio.h"

SniperRifle::SniperRifle(Game* game, Character* holder, int ammo) :
		Gun("res/guns/awp.png", 39, 9, game, holder, 5, ammo, sMagSize, sFireRate, 1, sReloadLength) {
	this->shotSound = game->getWAV("res/sounds/sniper_rifle.wav");
	this->reloadSound = game->getWAV("res/sounds/ak_reload.wav");
}

Projectile* SniperRifle::createProjectile(float x, float y, float aim) {
	return new SniperBullet(x, y, game, 20 * cos(aim), 20 * -sin(aim), sDamage, sHeadshotDamage, holder);
}

string SniperRifle::getName() {
	return "AWP";
}

int SniperRifle::getNumber() {
	return 5;
}

void SniperRifle::draw(float scrollX, float scrollY) {
	Gun::draw(scrollX, scrollY);
	// Dibuja el laser
	float tiltPlusCenterToCannon = tilt + (tilt > -M_PI / 2 && tilt < M_PI / 2 ? centerToCannonAngle : -centerToCannonAngle);
	float cannonX = x + (centerToCannon + 2) * cos(tiltPlusCenterToCannon) - scrollX;
	float cannonY = y + (centerToCannon + 2) * -sin(tiltPlusCenterToCannon) - scrollY;

	SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 100);
	SDL_RenderDrawLine(game->renderer, cannonX, cannonY,
		cannonX + WIDTH * cos(tilt), cannonY + WIDTH * -sin(tilt));
}

int SniperRifle::getLineOfSight() {
	return WIDTH;
}

float SniperRifle::calculateY() {
	return holder->y + 20 * -sin(holder->aim) + height / 2 - cannonHeight / 2;
}