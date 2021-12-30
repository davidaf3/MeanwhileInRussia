#include "ShotgunShell.h"
#include "Character.h"
#include "Layer.h"
#include "Space.h"

ShotgunShell::ShotgunShell(float x, float y, Game* game, float vx, float vy, int damage, int headshotDamage, Character* owner) :
		Projectile("res/projectiles/pellet.png", x, y, 4, 4, game, vx, vy, damage, headshotDamage, owner) {
	for (int i = 0; i < 10; i++) {
		int pelletVx = vx + (rand() % 4 - 2);
		int pelletVy = vy + (rand() % 4 - 2);
		this->pellets[i] = new Pellet(x, y, game, pelletVx, pelletVy, damage, headshotDamage, owner);
	}
}

void ShotgunShell::update() {
	int highestTTL = 0;
	for (int i = 0; i < 10; i++) {
		Pellet* pellet = pellets[i];
		if (pellet != NULL) {
			pellet->update();
			if (pellet->timeToLive > highestTTL) highestTTL = pellet->timeToLive;
			if (pellet->timeToLive == 0) {
				game->layer->space->removeDynamicActor(pellets[i]);
				delete pellets[i];
				pellets[i] = NULL;
			}
		}
	}
	timeToLive = highestTTL;
}

bool ShotgunShell::isOverlap(Actor* actor) {
	for (int i = 0; i < 10; i++) {
		if (pellets[i] != NULL && pellets[i]->isOverlap(actor)) return true;
	}
	return false;
}

void ShotgunShell::draw(float scrollX, float scrollY) {
	for (int i = 0; i < 10; i++) {
		if (pellets[i] != NULL) pellets[i]->draw(scrollX, scrollY);
	}
}

void ShotgunShell::hit(Character* character) {
	for (int i = 0; i < 10; i++) {
		if (pellets[i] != NULL && pellets[i]->isOverlap(character)) {
			pellets[i]->hit(character);
		}
	}
}

void ShotgunShell::addToSpace(Space* space) {
	for (int i = 0; i < 10; i++) {
		if (pellets[i] != NULL) space->addDynamicActor(pellets[i]);
	}
}

void ShotgunShell::move(float deltaX, float deltaY) {
	for (int i = 0; i < 10; i++) {
		if (pellets[i] != NULL) pellets[i]->move(deltaX, deltaY);
	}
}