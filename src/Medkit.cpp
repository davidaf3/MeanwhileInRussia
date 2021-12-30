#include "Medkit.h"
#include "WAVAudio.h"

Medkit::Medkit(float x, float y, Game* game) : Collectable("res/medkit.png", x, y, 17, 13, game) {}

void Medkit::collect(Player* player) {
	player->healAudio->play();
	player->setHealth(player->health + healthRecovered);
}