#include "Player.h"
#include "IdlePlayerState.h"
#include "Pistol.h"
#include "WAVAudio.h"
#include "GunFactory.h"
#include <sstream>

Player::Player(float x, float y, set<int> gunsInventory, map<string, int> ammoInventory, int nGun, Game* game) :
		Character("res/player_idle.png", x, y, standingWidht, standingHeight, maxHealth, game, headHeight) {
	for (int i = 0; i < 8; i++) {
		this->gunsInventory[i] = gunsInventory.find(i) != gunsInventory.end() ? GunFactory::forNumber(i, this, game) : NULL;
	}
	this->gun = this->gunsInventory[nGun];
	this->ammoInventory = ammoInventory;

	this->state = IdlePlayerState::instance(game);

	this->focusLeft = maxFocus;

	this->shotFrontAnimation = new Animation("res/player_shot_front.png", 48, 48, 144, 48, 10, 3, false, game);
	this->shotBehindAnimation = new Animation("res/player_shot_behind.png", 48, 48, 144, 48, 10, 3, false, game);

	// Animación de muerte por defecto
	this->deadAnimation = shotFrontAnimation;

	this->weaponSwitchSound = game->getWAV("res/sounds/weapon_switch.wav");
	this->drinkAudio = game->getWAV("res/sounds/bottle.wav");
	this->healAudio = game->getWAV("res/sounds/medkit.wav");
	this->pickupAudio = game->getWAV("res/sounds/ammo_pickup.wav");
}

Player::~Player() {
	delete shotFrontAnimation;
	delete shotBehindAnimation;

	if (gun != NULL) {
		int gunNumber = gun->getNumber();
		delete gun;
		gun = NULL;
		gunsInventory[gunNumber] = NULL;
	}

	for (int i = 0; i < 8; i++) {
		if (gunsInventory[i] != NULL) {
			delete gunsInventory[i];
			gunsInventory[i] = NULL;
		}
	}
}

void Player::doUpdate() {
	if (focus) {
		setFocusLeft(focusLeft - 1);
		if (focusLeft == 0) stopFocus();
	}
	else if (focusLeft < maxFocus && ++lastFocusReload == focusReloadStep) {
		setFocusLeft(focusLeft + 1);
		lastFocusReload = 0;
	}

	state->update(this);
}

void Player::doDraw(float scrollX, float scrollY) {
	state->draw(this, scrollX, scrollY);
}
 
void Player::doOnDead() {
	// Quita el arma del iventario, se le va a caer al morir
	gunsInventory[gun->getNumber()] = NULL;

	state->onDead(this);
}

bool Player::isHeadshot(Projectile* projectile) {
	return state->isHeadshot(this, projectile);
}

void Player::jump() {
	state->jump(this);
}

void Player::crouch(Space* space) {
	state->crouch(this, space);
}

void Player::getUp(Space* space) {
	state->getUp(this, space);
}

void Player::moveX(int orientation) {
	state->moveX(this, orientation);
}

void Player::moveY(int orientation) {
	state->moveY(this, orientation);
}

void Player::changeState(PlayerState* newState) {
	state->beforeStateChange(this);
	state = newState;
	newState->afterStateChange(this);
}

void Player::selectGun(int n) {
	state->selectGun(this, n);
}

void Player::selectNextGun() {
	state->selectNextGun(this);
}

void Player::selectPreviousGun() {
	state->selectPreviousGun(this);
}

void Player::reload() {
	state->reload(this);
}

int Player::getAmmoForCurrentGun() {
	if (gun == NULL || ammoInventory.find(gun->getName()) == ammoInventory.end())
		return 0;
	return ammoInventory[gun->getName()];
}

void Player::startFocus() {
	state->startFocus(this);
}

void Player::stopFocus() {
	focus = false;
	game->frameRate = 30;
}

void Player::setFocusLeft(int focusLeft) {
	if (focusLeft < 0) this->focusLeft = 0;
	if (focusLeft > maxFocus) this->focusLeft = maxFocus;
	else this->focusLeft = focusLeft;

	for (auto const& observer : observers)
		observer->onCharacterFocusChange(this);
}

string Player::getAmmoString() {
	if (gun == NULL) return "";
	if (ammoInventory[gun->getName()] == NULL) return gun->getAmmoString();

	stringstream ammoString;
	ammoString << gun->getAmmoString() << " | " << ammoInventory[gun->getName()];
	return ammoString.str();
}

string Player::getFocusString() {
	return to_string(focusLeft);
}