#include "FokusnoffBottle.h"
#include "WAVAudio.h"

FokusnoffBottle::FokusnoffBottle(float x, float y, Game* game) : Collectable("res/icons/focus_icon.png", x, y, 6, 20, game) {
	this->fileWidth = 50;
	this->fileHeight = 184;
}

void FokusnoffBottle::collect(Player* player) {
	player->drinkAudio->play();
	player->setFocusLeft(player->focusLeft + focusRecovered);
}