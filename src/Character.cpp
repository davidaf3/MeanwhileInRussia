#include "Character.h"
#include "Pistol.h"
#include "Space.h"
#include "WAVAudio.h"

Character::Character(string filename, float x, float y, int width, int height, int health, Game* game, int headHeight) :
	Actor(filename, x, y, width, height, game) {
	this->hitSound = game->getWAV("res/sounds/hit.wav");
	this->maxHealth = health;
	this->health = health;
	this->aim = 0;
	this->lastVy = 0;
	this->gun = NULL;
	this->headHeight = headHeight;
}

Character::~Character() {
	if (gun != NULL) delete gun;
}

void Character::update() {
	doUpdate();

	// Daño por caída
	if (collisionDown && lastVy > 15) {
		takeHit((lastVy - 15) * 5);
	}

	lastVy = vy;
	if (gun != NULL) gun->update();
}

void Character::doUpdate() {}

void Character::draw(float scrollX, float scrollY) {
	doDraw(scrollX, scrollY);
	if(gun != NULL) gun->draw(scrollX, scrollY);
}

void Character::doDraw(float scrollX, float scrollY) {
	Actor::draw(scrollX, scrollY);
}

void Character::shoot() {
	if (gun != NULL && gun->canShoot())  {
		Projectile* projectile = gun->shoot(aim);
		for (auto const& observer : observers) {
			observer->onCharacterFire(projectile);
			observer->onCharacterAmmoChange(this);
		}
	}
}

void Character::reload() {
	if (gun != NULL) {
		int freeMagSlots = gun->magSize - gun->ammo;
		if (freeMagSlots > 0) gun->reload(freeMagSlots);
	}
}

void Character::setHealth(int health) {
	if (health < 0) this->health = 0;
	else if (health > maxHealth) this->health = maxHealth;
	else this->health = health;

	for (auto const& observer : observers)
		observer->onCharacterHealthChange(this);
}

void Character::takeHit(int damage) {
	hitSound->play();
	if (health > 0) {
		setHealth(health - damage);
		if (health <= 0) onDead();
	}
}

bool Character::isHeadshot(Projectile* projectile) {
	return projectile->getTipY() < y - (height / 2 - headHeight);
}

void Character::onDead() {
	doOnDead();

	GunCollectable* droppedGun = gun->drop();
	gun = NULL;

	for (auto const& observer : observers) {
		observer->onCharacterDead(this, droppedGun);
	}
}

void Character::doOnDead() {}

bool Character::isLookingRight() {
	return aim > -M_PI / 2 && aim < M_PI / 2;
}

void Character::aimAt(int x, int y) {
	aim = atan2(this->y - y, x - this->x);
}

string Character::getAmmoString() {
	if (gun == NULL) return "";
	return gun->getAmmoString();
}

string Character::getHealthString() {
	return to_string((int) ((float) health / maxHealth * 100));
}

string Character::getFocusString() {
	return "0";
}