#include "Shotgun.h"
#include "ShotgunShell.h"
#include "WAVAudio.h"

Shotgun::Shotgun(Game* game, Character* holder, int ammo) :
		Gun("res/guns/ShootGun.png", 28, 7, game, holder, 5, ammo, sgMagSize, sgFireRate, 1, sgReloadLength) {
	this->shotSound = game->getWAV("res/sounds/shotgun.wav");
	this->reloadSound = game->getWAV("res/sounds/shotgun_reload.wav");
	this->fileWidth = 32;
	this->fileHeight = 8;
}

Projectile* Shotgun::createProjectile(float x, float y, float aim) {
	return new ShotgunShell(x, y, game, 10 * cos(aim), 10 * -sin(aim), sgDamage, sgHeadshotDamage, holder);
}

string Shotgun::getName() {
	return "Escopeta";
}

int Shotgun::getNumber() {
	return 2;
}