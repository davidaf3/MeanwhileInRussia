#include "AssaultRifle.h"
#include "Character.h"
#include "Bullet.h"
#include "WAVAudio.h"

AssaultRifle::AssaultRifle(Game* game, Character* holder, int ammo) :
	AutomaticGun("res/guns/AK-47.png", 28, 14, game, holder, 9, ammo, arMagSize, arFireRate, 1, arReloadLength,
		arMinAccuracy, arRecoil) {
	this->shotSound = game->getWAV("res/sounds/ak_47.wav");
	this->reloadSound = game->getWAV("res/sounds/ak_reload.wav");
	this->fileWidth = 64;
	this->fileHeight = 32;
}

Projectile* AssaultRifle::doCreateProjectile(float x, float y, float aim) {
	return new Bullet(x, y, game, 13 * cos(aim), 13 * -sin(aim), arDamage, arHeadshotDamage, holder);
}

int AssaultRifle::getLineOfSight() {
	return WIDTH / 2;
}

string AssaultRifle::getName() {
	return "AK-47";
}

float AssaultRifle::calculateY() {
	return holder->y + 20 * -sin(holder->aim) + height / 2 - cannonHeight / 2;
}

int AssaultRifle::getNumber() {
	return 3;
}