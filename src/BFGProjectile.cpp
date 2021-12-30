#include "BFGProjectile.h"
#include "Character.h"
#include "WAVAudio.h"

BFGProjectile::BFGProjectile(float x, float y, Game* game, float vx, float vy, int damage, int headshotDamage, Character* owner) :
		Projectile("res/projectiles/bfg_ball.png", x, y, 12, 12, game, vx, vy, damage, headshotDamage, owner) {
	this->explosion = new Animation("res/projectiles/bfg_explosion.png", 200, 200, 1200, 200, 5, 6, false, game);
	this->explosionSound = game->getWAV("res/sounds/explosion.wav");
}

void BFGProjectile::update() {
	if (explosionTimer > 0) {
		explosionTimer--;
		if (collisionDown || collisionTop || collisionLeft || collisionRight) onCollision();
		return;
	}

	if (explosionTimer == 0 && !exploded) {
		explode();
		return;
	}

	if (explosion->update()) {
		timeToLive = 0;
		return;
	}

	width = explosion->currentFrame * 40;
	height = explosion->currentFrame * 40;
}

void BFGProjectile::onCollision() {
	if (explosionTimer > 0) explosionTimer = 0;
}

void BFGProjectile::explode() {
	explosionSound->play();
	exploded = true;
	vx = 0;
	vy = 0;
}

void BFGProjectile::hit(Character* character) {
	if (character == owner) return;

	if (explosionTimer > 0) {
		explosionTimer = 0;
		return;
	}

	character->takeHit(damage);
}

void BFGProjectile::draw(float scrollX, float scrollY) {
	if (explosionTimer > 0) {
		Projectile::draw(scrollX, scrollY);
		return;
	}

	explosion->draw(x - scrollX, y - scrollY, false);
}