#include "WallJumpingPlayerState.h"
#include "Player.h"

WallJumpingPlayerState::WallJumpingPlayerState(Game* game) :
	OnAirPlayerState(game) {}

WallJumpingPlayerState* WallJumpingPlayerState::_instance = NULL;

WallJumpingPlayerState* WallJumpingPlayerState::instance(Game* game) {
	if (_instance == NULL)
		_instance = new WallJumpingPlayerState(game);
	return _instance;
}

void WallJumpingPlayerState::doUpdate(Player* player) {
	if (jumpFrames++ == totalJumpFrames) {
		player->changeState(OnAirPlayerState::instance(player->game));
		return;
	}

	player->vx += player->vx > 0 ? -1 : 1;
}

void WallJumpingPlayerState::beforeStateChange(Player* player) {
	jumpFrames = 0;
}

void WallJumpingPlayerState::moveX(Player* player, int orientation) {}

void WallJumpingPlayerState::moveY(Player* player, int orientation) {}