#include "AliveEnemyState.h"

AliveEnemyState::AliveEnemyState() {}

AliveEnemyState* AliveEnemyState::_instance = new AliveEnemyState();

AliveEnemyState* AliveEnemyState::instance() {
	return _instance;
}