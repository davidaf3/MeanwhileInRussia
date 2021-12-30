#include "PlayerStateDead.h"
#include "Player.h"

PlayerStateDead::PlayerStateDead() {}

PlayerStateDead* PlayerStateDead::_instance = new PlayerStateDead();

PlayerStateDead* PlayerStateDead::instance() {
	return _instance;
}

void PlayerStateDead::update(Player* player) {
	if (player->deadAnimation->update()) player->isDead = true;
}

void PlayerStateDead::moveX(Player* player, int orientation) {}

void PlayerStateDead::moveY(Player* player, int orientation) {}

void PlayerStateDead::jump(Player* player) {}

void PlayerStateDead::selectGun(Player* player, int n) {}

void PlayerStateDead::selectNextGun(Player* player) {}

void PlayerStateDead::selectPreviousGun(Player* player) {}

void PlayerStateDead::reload(Player* player) {}

void PlayerStateDead::startFocus(Player* player) {}

void PlayerStateDead::draw(Player* player, float scrollX, float scrollY) {
	player->deadAnimation->draw(player->x - scrollX, player->y - scrollY, !player->isLookingRight());
}