#include "EnemyState.h"
#include "EnemyStateDead.h"
#include "Enemy.h"
#include "Layer.h"
#include "Space.h"
#include "Gun.h"

void EnemyState::draw(Enemy* enemy, float scrollX, float scrollY) {
	enemy->aliveAnimation->draw(enemy->x - scrollX, enemy->y - scrollY, !enemy->isLookingRight());
}

void EnemyState::update(Enemy* enemy) {
	enemy->aliveAnimation->update();

	if (enemy->gun->ammo < 1) {
		enemy->reload();
		return;
	}

	// Comprueba si debe atacar al objetivo
	// Se considera que debe atacar al objetivo si lo est� viendo (est� mirando hacia �l y est�n
	// a una distancia menor del ancho de la pantalla menos 50) o si est�n a menos de 150 p�xeles, y adem�s
	// no hay ninguna tile que bloquee la visi�n
	Character* objective = enemy->objective;
	float distance = sqrt(pow(enemy->x - objective->x, 2) + pow(enemy->y - objective->y, 2));
	bool lookingAtObjective = enemy->x >= enemy->objective->x == !enemy->isLookingRight();

	if (objective->health > 0 && (distance < 150 || (lookingAtObjective && distance < enemy->gun->getLineOfSight())) &&
			enemy->game->layer->space->isSegmentFree(enemy->x, enemy->y, enemy->objective->x, enemy->objective->y)) {
		enemy->aimAt(objective->x, objective->y);
		enemy->shoot();
	}
}

void EnemyState::onDead(Enemy* enemy) {
	// Cambia la animaci�n de muerte por defecto si le han disparado por la espalda
	if (enemy->isLookingRight() && enemy->hitLeft || !enemy->isLookingRight() && enemy->hitRight)
		enemy->deadAnimation = enemy->shotBehindAnimation;

	for (auto const& observer : enemy->observers)
		observer->onEnemyKilled();

	enemy->changeState(EnemyStateDead::instance());
}