#include "GunCollectable.h"
#include "WAVAudio.h"

GunCollectable::GunCollectable(Gun* gun) : 
		Collectable("res/guns/desert_hawk.png", gun->x, gun->y, gun->width, gun->height, gun->game) {
	this->gun = gun;
}

GunCollectable::~GunCollectable() {
	if (gun != NULL) delete gun;
}

void GunCollectable::update() {
	gun->x = this->x;
	gun->y = this->y;
	gun->update();
}

void GunCollectable::draw(float scrollX, float scrollY) {
	gun->draw(scrollX, scrollY);
}

void GunCollectable::collect(Player* player) {
	player->pickupAudio->play();

	player->ammoInventory[gun->getName()] += gun->magSize;
	for (auto const& observer : player->observers)
		observer->onCharacterAmmoChange(player);

	if (player->gunsInventory[gun->getNumber()] != NULL) {
		delete gun;
		gun = NULL;
		return;
	}

	gun->ammo = gun->magSize;
	gun->holder = player;
	player->gunsInventory[gun->getNumber()] = gun;
	player->selectGun(gun->getNumber());
	gun = NULL;
}