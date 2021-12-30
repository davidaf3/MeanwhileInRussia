#include "Pellet.h"

Pellet::Pellet(float x, float y, Game* game, float vx, float vy, int damage, int headshotDamage, Character* owner) :
	Projectile("res/projectiles/pellet.png", x, y, 4, 4, game, vx, vy, damage, headshotDamage, owner) {
}