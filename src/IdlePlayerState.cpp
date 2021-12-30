#include "IdlePlayerState.h"
#include "RunningPlayerState.h"
#include "OnAirPlayerState.h"
#include "CrouchedPlayerState.h"
#include "Player.h"

IdlePlayerState::IdlePlayerState(Game* game) {
	this->animation = new Animation("res/player_idle.png", 18, 48, 36, 48, 10, 2, true, game);
}

IdlePlayerState* IdlePlayerState::_instance = NULL;
 
IdlePlayerState* IdlePlayerState::instance(Game* game) {
	if (_instance == NULL)
		_instance = new IdlePlayerState(game);
	return _instance;
}

void IdlePlayerState::update(Player* player) {
	if (player->vx != 0 && player->collisionDown) {
		player->changeState(RunningPlayerState::instance(player->game));
		return;
	}

	if (!player->collisionDown) {
		player->changeState(OnAirPlayerState::instance(player->game));
		return;
	}
	
	animation->update();
}

void IdlePlayerState::crouch(Player* player, Space* space) {
	player->changeState(CrouchedPlayerState::instance(player->game));
}