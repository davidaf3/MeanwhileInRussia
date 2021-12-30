#include "OnAirPlayerState.h"
#include "IdlePlayerState.h"
#include "WallSlidingPlayerState.h"
#include "Player.h"
#include "WAVAudio.h"

OnAirPlayerState::OnAirPlayerState(Game* game) {
	this->animation = new Animation("res/player_on_air.png", 20, 48, 60, 48, 4, 3, false, game);
	this->fallAudio = game->getWAV("res/sounds/fall.wav");
}

OnAirPlayerState* OnAirPlayerState::_instance = NULL;

OnAirPlayerState* OnAirPlayerState::instance(Game* game) {
	if (_instance == NULL)
		_instance = new OnAirPlayerState(game);
	return _instance;
}

void OnAirPlayerState::update(Player* player) {
	if (player->collisionDown) {
		fallAudio->play();
		player->changeState(IdlePlayerState::instance(player->game));
		return;
	}

	if (player->vy > 0 && (player->collisionLeft || player->collisionRight)) {
		player->changeState(WallSlidingPlayerState::instance(player->game));
		return;
	}

	doUpdate(player);
}

void OnAirPlayerState::doUpdate(Player* player) {
	animation->update();
}

void OnAirPlayerState::jump(Player* player) {}

void OnAirPlayerState::beforeStateChange(Player* player) {
	animation->reset();
}