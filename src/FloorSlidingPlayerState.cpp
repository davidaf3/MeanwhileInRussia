#include "FloorSlidingPlayerState.h"
#include "IdlePlayerState.h"
#include "GameLayer.h"
#include "Player.h"

FloorSlidingPlayerState::FloorSlidingPlayerState(Game* game) {
	this->space = NULL;
	this->animation = new Animation("res/player_floor_sliding.png", Player::floorSlidingWidth,
		Player::floorSlidingHeight, Player::floorSlidingWidth * 4, Player::floorSlidingHeight, 4, 4, true, game);
}

FloorSlidingPlayerState* FloorSlidingPlayerState::_instance = NULL;

FloorSlidingPlayerState* FloorSlidingPlayerState::instance(Game* game) {
	if (_instance == NULL)
		_instance = new FloorSlidingPlayerState(game);
	return _instance;
}

void FloorSlidingPlayerState::update(Player* player) {
	animation->update();

	if (--reduceSpeedTime == 0 && !slideEnded) {
		player->vx += player->vx > 0 ? -1 : 1;
		reduceSpeedTime = reduceSpeedInterval;
	}

	if (abs(player->vx) <= abs(endSpeed)) {
		slideEnded = true;
		// Comprobamos si tiene espacio encima para levantarse
		float yToCheck = player-> y - (player->standingHeight - player->floorSlidingHeight) / 2;
		if (!space->isRectFree(player->x, yToCheck, player->standingWidht, player->standingHeight)) {
			// Si no tiene espacio se sigue deslizando hasta que lo encuentre
			player->vx = endSpeed * (player->vx > 0 ? 1 : -1);
			return;
		}

		player->changeState(IdlePlayerState::instance(player->game));
	}
}

void FloorSlidingPlayerState::afterStateChange(Player* player) {
	space = GameLayer::instance(player->game)->space;
	slideEnded = false;
	reduceSpeedTime = reduceSpeedInterval;
	player->vx = initialSpeed * orientation;
	player->height = player->floorSlidingHeight;
	player->width = player->floorSlidingWidth;
	player->y += (player->standingHeight - player->floorSlidingHeight) / 2;
	player->x += (player->floorSlidingWidth - player->standingWidht) / 2 * orientation;
}

void FloorSlidingPlayerState::beforeStateChange(Player* player) {
	animation->reset();
	player->vx = 0;
	player->height = player->standingHeight;
	player->width = player->standingWidht;
	player->y -= (player->standingHeight - player->floorSlidingHeight) / 2;
}

void FloorSlidingPlayerState::jump(Player* player) {
	// Comprobamos si tiene espacio encima para levantarse
	float yToCheck = player->y - (player->standingHeight - player->floorSlidingHeight) / 2;
	if (space->isRectFree(player->x, yToCheck, player->standingWidht, player->standingHeight)) {
		PlayerState::jump(player);
	}
}

void FloorSlidingPlayerState::moveX(Player* player, int orientation) {}

void FloorSlidingPlayerState::moveY(Player* player, int orientation) {}

void FloorSlidingPlayerState::draw(Player* player, float scrollX, float scrollY) {
	animation->draw(player->x - scrollX, player->y - scrollY, player->vx < 0);
}

bool FloorSlidingPlayerState::isHeadshot(Player* player, Projectile* projectile) {
	if (player->vx < 0) return projectile->getTipX() >= player->x + (player->width / 2 - player->headHeight);
	return projectile->getTipX() <= player->x - (player->width / 2 - player->headHeight);
}