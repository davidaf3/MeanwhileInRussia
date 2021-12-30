#include "BFG.h"
#include "BFGProjectile.h"
#include "WAVAudio.h"

BFG::BFG(Game* game, Character* holder) :
		Gun("res/guns/bfg.png", 33, 14, game, holder, 5, 1, bfgMagSize, bfgFireRate, 0, bfgReloadLength) {
	init();
}

BFG::BFG(Game* game, float x, float y) :
		Gun("res/guns/bfg.png", x, y, 33, 14, game, 5, 1, bfgMagSize, bfgFireRate, 0, bfgReloadLength) {
	init();
}

void BFG::init() {
	this->shotSound = game->getWAV("res/sounds/bfg_launch.wav");
	this->fileWidth = 50;
	this->fileHeight = 22;
}

Projectile* BFG::createProjectile(float x, float y, float aim) {
	return new BFGProjectile(x, y, game, 12 * cos(aim), 12 * -sin(aim), bfgDamage, bfgHeadshotDamage, holder);
}

string BFG::getName() {
	return "BFG";
}

int BFG::getNumber() {
	return 7;
}

string BFG::getAmmoString() {
	return lastShot > 0 ? "Recargando" : "Listo";
}