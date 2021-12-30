#include "Bullet.h"

Bullet::Bullet(float x, float y, Game* game, float vx, float vy, int damage, int headshotDamage, Character* owner) :
	Projectile("res/projectiles/pistol_bullet.png", x, y, 12, 3, game, vx, vy, damage, headshotDamage, owner) {
}