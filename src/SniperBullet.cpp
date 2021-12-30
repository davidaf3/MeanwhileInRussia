#include "SniperBullet.h"

SniperBullet::SniperBullet(float x, float y, Game* game, float vx, float vy, int damage, int headshotDamage, Character* owner) :
	Bullet(x, y, game, vx, vy, damage, headshotDamage, owner) {}

void SniperBullet::hit(Character* character) {
	int currentTTL = timeToLive;
	Bullet::hit(character);
	// La bala no se destruye al impactar a un personaje
	timeToLive = currentTTL;
}