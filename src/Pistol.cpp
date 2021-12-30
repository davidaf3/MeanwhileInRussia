#include "Pistol.h"
#include "Bullet.h"
#include "WAVAudio.h"

Pistol::Pistol(Game* game, Character* holder, int ammo) :
		Gun("res/guns/desert_hawk.png", 13, 10, game, holder, 3, ammo, pistolMagSize, pistolFireRate, 1, pistolReloadLength) {
	this->shotSound = game->getWAV("res/sounds/pistol.wav");
	this->reloadSound = game->getWAV("res/sounds/gun_reload.wav");
}

Projectile* Pistol::createProjectile(float x, float y, float aim) {
	return new Bullet(x, y, game, 12 * cos(aim), 12 * -sin(aim), pistolDamage, pistolHeadshotDamage, holder);
}

string Pistol::getName() {
	return "Pistola";
}