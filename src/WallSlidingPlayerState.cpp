#include "WallSlidingPlayerState.h"
#include "Player.h"
#include "IdlePlayerState.h"
#include "OnAirPlayerState.h"
#include "JumpingPlayerState.h"
#include "WallJumpingPlayerState.h"

WallSlidingPlayerState::WallSlidingPlayerState(Game* game) {
	this->animation = new Animation("res/player_sliding_against.png", 18, 48, 18, 48, 30, 1, true, game);
	this->inverseAnimation = new Animation("res/player_sliding_towards.png", 20, 48, 20, 48, 30, 1, true, game);
}

WallSlidingPlayerState* WallSlidingPlayerState::_instance = NULL;

WallSlidingPlayerState* WallSlidingPlayerState::instance(Game* game) {
	if (_instance == NULL)
		_instance = new WallSlidingPlayerState(game);
	return _instance;
}

void WallSlidingPlayerState::update(Player* player) {
	player->vy = 1;

	if (player->collisionDown) {
		player->changeState(IdlePlayerState::instance(player->game));
		return;
	}

	if (!player->collisionLeft && !player->collisionRight) {
		player->changeState(OnAirPlayerState::instance(player->game));
		return;
	}
}

void WallSlidingPlayerState::jump(Player* player) {
	PlayerState::jump(player);
	int jumpSpeed = WallJumpingPlayerState::totalJumpFrames;
	player->vx = player->collisionLeft ? jumpSpeed : -jumpSpeed;
	player->changeState(WallJumpingPlayerState::instance(player->game));
}

void WallSlidingPlayerState::draw(Player* player, float scrollX, float scrollY) {
	if (player->collisionLeft && player->isLookingRight())
		animation->draw(player->x - scrollX, player->y - scrollY, false);
	else if (player->collisionLeft && !player->isLookingRight())
		inverseAnimation->draw(player->x - scrollX, player->y - scrollY, true);
	else if (player->collisionRight && player->isLookingRight())
		inverseAnimation->draw(player->x - scrollX, player->y - scrollY, false);
	else if (player->collisionRight && !player->isLookingRight())
		animation->draw(player->x - scrollX, player->y - scrollY, true);
}