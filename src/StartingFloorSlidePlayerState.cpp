#include "StartingFloorSlidePlayerState.h"
#include "FloorSlidingPlayerState.h"
#include "IdlePlayerState.h"
#include "Player.h"

StartingFloorSlidePlayerState::StartingFloorSlidePlayerState(Game* game) {
	this->space = NULL;
	this->animation = new Animation("res/player_start_slide.png", 24, 48, 48, 48, 3, 2, false, game);
}

StartingFloorSlidePlayerState* StartingFloorSlidePlayerState::_instance = NULL;

StartingFloorSlidePlayerState* StartingFloorSlidePlayerState::instance(Game* game, Space* space) {
	if (_instance == NULL)
		_instance = new StartingFloorSlidePlayerState(game);
	_instance->space = space;
	return _instance;
}

void StartingFloorSlidePlayerState::update(Player* player) {
	if (player->vx == 0) {
		animation->reset();
		player->changeState(IdlePlayerState::instance(player->game));
	}

	if (animation->update()) {
		animation->reset();

		// Comprueba si hay espacio en frente del jugador para deslizarse
		// Para ello calcula el rectángulo que ocupará el jugador a la derecha
		// o a la izquierda y comprueba si hay algún actor estático con el que se solape
		float widthDelta = player->floorSlidingWidth - player->standingWidht;
		float xDelta = (widthDelta / 2 + player->standingWidht / 2) * (player->vx > 0 ? 1 : -1);
		float xToCheck = player->x + xDelta;
		float yDelta = player->standingHeight / 2 - player->floorSlidingHeight / 2;
		float yToCheck = player->y + yDelta;

		if (!space->isRectFree(xToCheck, yToCheck, widthDelta, player->floorSlidingHeight)) {
			player->vx = 0;
			player->changeState(IdlePlayerState::instance(player->game));
			return;
		}
		
		FloorSlidingPlayerState* slidingState = FloorSlidingPlayerState::instance(player->game);
		slidingState->orientation = player->vx > 0 ? 1 : -1;
		player->changeState(slidingState);
	}
}

void StartingFloorSlidePlayerState::jump(Player* player) {}

void StartingFloorSlidePlayerState::moveX(Player* player, int orientation) {}

void StartingFloorSlidePlayerState::moveY(Player* player, int orientation) {}

void StartingFloorSlidePlayerState::draw(Player* player, float scrollX, float scrollY) {
	animation->draw(player->x - scrollX, player->y - scrollY, player->vx < 0);
}