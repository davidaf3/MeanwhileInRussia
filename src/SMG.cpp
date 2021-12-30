#include "SMG.h"
#include "Bullet.h"
#include "WAVAudio.h"

SMG::SMG(Game* game, Character* holder, int ammo) :
	AutomaticGun("res/guns/mag.png", 14, 12, game, holder, 5, ammo, smgMagSize, smgFireRate, 1, smgReloadLength, 
		smgMinAccuracy, smgRecoil) {
	this->shotSound = game->getWAV("res/sounds/smg.wav");
	this->reloadSound = game->getWAV("res/sounds/gun_reload.wav");
}

Projectile* SMG::doCreateProjectile(float x, float y, float aim) {
	return new Bullet(x, y, game, 13 * cos(aim), 13 * -sin(aim), smgDamage, smgHeadshotDamage, holder);
}

string SMG::getName() {
	return "MAC-10";
}

int SMG::getNumber() {
	return 1;
}