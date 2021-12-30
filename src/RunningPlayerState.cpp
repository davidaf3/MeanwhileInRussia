#include "RunningPlayerState.h"
#include "IdlePlayerState.h"
#include "OnAirPlayerState.h"
#include "StartingFloorSlidePlayerState.h"
#include "Player.h"
#include "WAVAudio.h"
#include "Game.h"

RunningPlayerState::RunningPlayerState(Game* game) {
	this->animation = new Animation("res/player_running.png", 18, 48, 108, 48, 3, 6, true, game);
	this->stepsSound = game->getWAV("res/sounds/steps.wav", true);
}

RunningPlayerState* RunningPlayerState::_instance = NULL;

RunningPlayerState* RunningPlayerState::instance(Game* game) {
	if (_instance == NULL)
		_instance = new RunningPlayerState(game);
	return _instance;
}

void RunningPlayerState::update(Player* player) {
	if (player->vx == 0 && player->collisionDown) {
		animation->reset();
		player->changeState(IdlePlayerState::instance(player->game));
		return;
	}

	if (!player->collisionDown) {
		player->changeState(OnAirPlayerState::instance(player->game));
		return;
	}
	
	animation->update();
}

void RunningPlayerState::crouch(Player* player, Space* space) {
	player->changeState(StartingFloorSlidePlayerState::instance(player->game, space));
}

void RunningPlayerState::afterStateChange(Player* player) {
	stepsSound->play();
}

void RunningPlayerState::beforeStateChange(Player* player) {
	stepsSound->pause();
}