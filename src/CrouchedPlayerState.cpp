#include "CrouchedPlayerState.h"
#include "IdlePlayerState.h"
#include "Player.h"

CrouchedPlayerState::CrouchedPlayerState(Game* game) {
	this->animation = new Animation("res/player_crouch.png", 18, Player::crouchedHeight, 18, 
		Player::crouchedHeight, 30, 1, true, game);
}

CrouchedPlayerState* CrouchedPlayerState::_instance = NULL;

CrouchedPlayerState* CrouchedPlayerState::instance(Game* game) {
	if (_instance == NULL)
		_instance = new CrouchedPlayerState(game);
	return _instance;
}

void CrouchedPlayerState::getUp(Player* player, Space* space) {
	player->changeState(IdlePlayerState::instance(player->game));
}

void CrouchedPlayerState::afterStateChange(Player* player) {
	player->vx = 0;
	player->height = player->crouchedHeight;
	player->y += (player->standingHeight - player->crouchedHeight) / 2;
}

void CrouchedPlayerState::beforeStateChange(Player* player) {
	player->height = player->standingHeight;
	player->y -= (player->standingHeight - player->crouchedHeight) / 2;
}

void CrouchedPlayerState::jump(Player* player) {}

void CrouchedPlayerState::moveX(Player* player, int orientation) {}

void CrouchedPlayerState::moveY(Player* player, int orientation) {}