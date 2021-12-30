#include "PlayerState.h"
#include "JumpingPlayerState.h"
#include "PlayerStateDead.h"
#include "Player.h"

void PlayerState::update(Player* player) {}

void PlayerState::jump(Player* player) {
	player->vy = -12;
	player->changeState(JumpingPlayerState::instance(player->game));
}

void PlayerState::crouch(Player* player, Space* space) {}

void PlayerState::getUp(Player* player, Space* space) {}

void PlayerState::moveX(Player* player, int orientation) {
	player->vx = 3 * orientation;
}

void PlayerState::moveY(Player* player, int orientation) {
	player->vy = 3 * orientation;
}

void PlayerState::draw(Player* player, float scrollX, float scrollY) {
	animation->draw(player->x - scrollX, player->y - scrollY, !player->isLookingRight());
}

bool PlayerState::isHeadshot(Player* player, Projectile* projectile) {
	return player->Character::isHeadshot(projectile);
}

void PlayerState::selectGun(Player* player, int n) {
	if (player->gunsInventory[n] != NULL && n != player->gun->getNumber()) {
		player->gun->holster();
		player->gun = player->gunsInventory[n];
		player->weaponSwitchSound->play();
		for (auto const& observer : player->observers)
			observer->onCharacterAmmoChange(player);
	}
}

void PlayerState::selectNextGun(Player* player) {
	for (int i = player->gun->getNumber() + 1; i < 8; i++) {
		if (player->gunsInventory[i] != NULL) {
			selectGun(player, i);
			return;
		}
	}
}

void PlayerState::selectPreviousGun(Player* player) {
	for (int i = player->gun->getNumber() - 1; i >= 0; i--) {
		if (player->gunsInventory[i] != NULL) {
			selectGun(player, i);
			return;
		}
	}
}

void PlayerState::reload(Player* player) {
	int ammoForGun = player->getAmmoForCurrentGun();
	int freeMagSlots = player->gun->magSize - player->gun->ammo;
	if (ammoForGun > 0 && freeMagSlots > 0) {
		int ammoToReload = ammoForGun > freeMagSlots ? freeMagSlots : ammoForGun;
		player->gun->reload(ammoToReload);
		player->ammoInventory[player->gun->getName()] = ammoForGun - ammoToReload;
		for (auto const& observer : player->observers)
			observer->onCharacterAmmoChange(player);
	}
}

void PlayerState::startFocus(Player* player) {
	if (player->focusLeft > 0) {
		player->focus = true;
		player->game->frameRate = 15;
	}
}

void PlayerState::onDead(Player* player) {
	if (player->isLookingRight() && player->hitLeft || !player->isLookingRight() && player->hitRight)
		player->deadAnimation = player->shotBehindAnimation;
	if (player->focus) player->stopFocus();
	player->changeState(PlayerStateDead::instance());
}

void PlayerState::beforeStateChange(Player* player) {}

void PlayerState::afterStateChange(Player* player) {}