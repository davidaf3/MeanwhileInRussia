#include "RicochetBullet.h"

RicochetBullet::RicochetBullet(float x, float y, Game* game, float vx, float vy, int damage, int headshotDamage, Character* owner) :
		Projectile("res/projectiles/ricochet_bullet.png", x, y, 12, 3, game, vx, vy, damage, headshotDamage, owner) {
	timeToLive = 150;
	lastVx = vx;
	lastVy = vy;
}

void RicochetBullet::onCollision() {
	vx = lastVx * (collisionLeft || collisionRight ? -1 : 1);
	vy = lastVy * (collisionDown || collisionTop ? -1 : 1);
	lastVx = vx;
	lastVy = vy;
}