#include "RicochetGun.h"
#include "RicochetBullet.h"
#include "Character.h"
#include "WAVAudio.h"

RicochetGun::RicochetGun(Game* game, Character* holder, int ammo) :
	AutomaticGun("res/guns/ricochet_gun.png", 24, 15, game, holder, 3, ammo, rgMagSize, rgFireRate, 1, rgReloadLength, 
		rgMinAccuracy, rgRecoil) {
	this->shotSound = game->getWAV("res/sounds/ricochet_gun.wav");
	this->reloadSound = game->getWAV("res/sounds/gun_reload.wav");
	this->fileWidth = 50;
	this->fileHeight = 31;
}

Projectile* RicochetGun::doCreateProjectile(float x, float y, float aim) {
	return new RicochetBullet(x, y, game, 12 * cos(aim), 12 * -sin(aim), rgDamage, rgHeadshotDamage, holder);
}

string RicochetGun::getName() {
	return "Rebotadora";
}

int RicochetGun::getNumber() {
	return 6;
}

float RicochetGun::calculateX() {
	return holder->x + 10 * cos(holder->aim);
}