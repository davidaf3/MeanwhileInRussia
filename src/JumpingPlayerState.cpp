#include "JumpingPlayerState.h"
#include "Player.h"

JumpingPlayerState::JumpingPlayerState(Game* game) : OnAirPlayerState(game) {
	this->animation = new Animation("res/player_jump.png", 20, 48, 40, 48, 4, 2, false, game);
}

JumpingPlayerState* JumpingPlayerState::_instance = NULL;

JumpingPlayerState* JumpingPlayerState::instance(Game* game) {
	if (_instance == NULL)
		_instance = new JumpingPlayerState(game);
	return _instance;
}

void JumpingPlayerState::doUpdate(Player* player) {
	if (animation->update()) {
		player->changeState(OnAirPlayerState::instance(player->game));
	}
}

void JumpingPlayerState::beforeStateChange(Player* player) {
	OnAirPlayerState::beforeStateChange(player);
	animation->reset();
}

void JumpingPlayerState::draw(Player* player, float scrollX, float scrollY) {
	animation->draw(player->x - scrollX, player->y - scrollY, !player->isLookingRight());
}