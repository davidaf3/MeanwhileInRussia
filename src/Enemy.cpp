#include "Enemy.h"
#include "AliveEnemyState.h"
#include "GunFactory.h"

Enemy::Enemy(float x, float y, Game* game, int nGun, Character* objective, string kind, int health, float aim) :
		Character("res/enemy_" + kind + "_idle.png", x, y, 18, 48, health, game, 14) {
	this->aliveAnimation = new Animation("res/enemy_" + kind + "_idle.png", 18, 48, 36, 48, 10, 2, true, game);
	this->shotFrontAnimation = new Animation("res/enemy_" + kind + "_shot_front.png", 48, 48, 144, 48, 10, 3, false, game);
	this->shotBehindAnimation = new Animation("res/enemy_" + kind + "_shot_behind.png", 48, 48, 144, 48, 10, 3, false, game);
	this->objective = objective;
	this->aim = aim;
	this->gun = GunFactory::forNumber(nGun, this, game);
	this->state = AliveEnemyState::instance();

	// Animación de muerte por defecto
	this->deadAnimation = shotFrontAnimation;
}

Enemy::~Enemy() {
	delete aliveAnimation;
	delete shotFrontAnimation;
	delete shotBehindAnimation;
}

void Enemy::doDraw(float scrollX, float scrollY) {
	state->draw(this, scrollX, scrollY);
}

void Enemy::doUpdate() {
	state->update(this);
}

void Enemy::doOnDead() {
	state->onDead(this);
}

void Enemy::changeState(EnemyState* newState) {
	state = newState;
}