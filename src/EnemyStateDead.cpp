#include "EnemyStateDead.h"
#include "Enemy.h"

void EnemyStateDead::draw(Enemy* enemy, float scrollX, float scrollY) {
	enemy->deadAnimation->draw(enemy->x - scrollX, enemy->y - scrollY, !enemy->isLookingRight());
}

void EnemyStateDead::update(Enemy* enemy) {
	if (enemy->deadAnimation->update()) enemy->isDead = true;
}

void EnemyStateDead::onDead(Enemy* enemy) {}

EnemyStateDead::EnemyStateDead() {}

EnemyStateDead* EnemyStateDead::_instance = new EnemyStateDead();

EnemyStateDead* EnemyStateDead::instance() {
	return _instance;
}