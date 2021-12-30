#include "MachineGun.h"
#include "Character.h"
#include "Bullet.h"
#include "WAVAudio.h"

MachineGun::MachineGun(Game* game, Character* holder, int ammo) :
	AutomaticGun("res/guns/m249.png", 29, 11, game, holder, 8, ammo, mgMagSize, mgFireRate, 1, mgReloadLength,
		mgMinAccuracy, mgRecoil) {
	this->shotSound = game->getWAV("res/sounds/machine_gun.wav");
	this->reloadSound = game->getWAV("res/sounds/m249_reload.wav");
	this->fileWidth = 100;
	this->fileHeight = 38;
}

Projectile* MachineGun::doCreateProjectile(float x, float y, float aim) {
	return new Bullet(x, y, game, 13 * cos(aim), 13 * -sin(aim), mgDamage, mgHeadshotDamage, holder);
}

int MachineGun::getLineOfSight() {
	return WIDTH / 2;
}

string MachineGun::getName() {
	return "M249";
}

int MachineGun::getNumber() {
	return 4;
}

float MachineGun::calculateY() {
	return holder->y + 20 * -sin(holder->aim) + height / 2 - cannonHeight / 2;
}