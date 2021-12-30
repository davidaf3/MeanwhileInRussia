#include "Collectable.h"

Collectable::Collectable(string filename, float x, float y, int width, int height, Game* game) :
	Actor(filename, x, y, width, height, game) {}

Collectable::~Collectable() {}

void Collectable::update() {}

void Collectable::collect(Player* player) {}