#include "Gun.h"
#include "Character.h"
#include "WAVAudio.h"
#include "GunCollectable.h"

Gun::Gun(string filename, int width, int height, Game* game, Character* holder, int cannonHeight, 
	int ammo, int magSize, int fireRate, int ammoPerShot, int reloadLength) :
	Gun(filename, holder->x, holder->y, width, height, game, cannonHeight, ammo, magSize, fireRate, ammoPerShot, reloadLength) {
	this->holder = holder;
	this->tilt = holder->aim;
}

Gun::Gun(string filename, float x, float y, int width, int height, Game* game, int cannonHeight,
	int ammo, int magSize, int fireRate, int ammoPerShot, int reloadLength) :
	Actor(filename, x, y, width, height, game) {
	this->holder = NULL;
	this->tilt = 0;
	this->centerToCannon = sqrtf(powf(width / 2, 2) + powf(height / 2 - cannonHeight / 2, 2));
	this->centerToCannonAngle = atan2f(height / 2 - cannonHeight / 2, width / 2);
	this->cannonHeight = cannonHeight;
	this->ammo = ammo > magSize ? magSize : ammo;
	this->magSize = magSize;
	this->fireRate = fireRate;
	this->lastShot = 0;
	this->ammoPerShot = ammoPerShot;
	this->reloadTime = 0;
	this->reloadLength = reloadLength;
	this->outOfAmmoSound = game->getWAV("res/sounds/out_of_ammo.wav");
}

Gun::~Gun() {}

void Gun::update() {
	if (holder != NULL) {
		x = calculateX();
		y = calculateY();
		tilt = holder->aim;
	}

	if (lastShot > 0) {
		if (--lastShot == 0) notifyHolderObservers();
	}

	if (reloadTime > 0) {
		if (--reloadTime == 0) {
			// Cuando termina la recarga se añaden las balas al cargador
			ammo = nextReloadAmmo;
			nextReloadAmmo = 0;
			notifyHolderObservers();
		}
	}
}

void Gun::reload(int ammo) {
	if (reloadTime == 0) {
		playReloadSound();
		this->reloadTime = reloadLength;
		int newAmmo = this->ammo + ammo;
		this->nextReloadAmmo = (newAmmo > magSize ? magSize : newAmmo);
	}
}

void Gun::unload(int ammo) {
	int newAmmo = this->ammo - ammo;
	this->ammo = (newAmmo < 0 ? 0 : newAmmo);
}

bool Gun::canShoot() {
	if (ammo == 0 && reloadTime == 0 && lastShot == 0) {
		// No tiene munición, no está recargando y ha pasado suficiente tiempo
		// desde la última vez que apretó el gatillo
		lastShot = fireRate;
		outOfAmmoSound->play();
		return false;
	}
	return ammo > 0 && lastShot == 0 && reloadTime == 0;
}

Projectile* Gun::createProjectile(float x, float y, float aim) {
	return NULL;
}

Projectile* Gun::shoot(float aim) {
	playShotSound();
	unload(ammoPerShot);
	lastShot = fireRate;
	Projectile* projectile = createProjectile(x, y, aim);
	// Mueve el proyectil a la punta del cañón
	float aimPlusCenterToCannon = aim + (holder->isLookingRight() ? centerToCannonAngle : -centerToCannonAngle);
	projectile->move(centerToCannon * cos(aimPlusCenterToCannon) + projectile->width / 2 * cos(aim),
		centerToCannon * -sin(aimPlusCenterToCannon) + projectile->width / 2 * -sin(aim));
	return projectile;
}

void Gun::draw(float scrollX, float scrollY) {
	// Recorte en el fichero de la imagen
	SDL_Rect source;
	source.x = 0;
	source.y = 0;
	source.w = fileWidth; // texture.width;
	source.h = fileHeight; // texture.height;

	// Donde se va a pegar en el renderizador
	SDL_Rect destination;
	destination.x = x - width / 2 - scrollX;
	destination.y = y - height / 2 - scrollY;
	destination.w = width;
	destination.h = height;
	// Modificar para que la referencia sea el punto central

	float angle = tilt * 180 / M_PI;
	SDL_RendererFlip flip = tilt > -M_PI / 2 && tilt < M_PI / 2 ? SDL_FLIP_NONE : SDL_FLIP_VERTICAL;

	SDL_RenderCopyEx(game->renderer,
		texture, &source, &destination, -angle, NULL, flip);
}

void Gun::cancelReload() {
	reloadTime = 0;
	nextReloadAmmo = 0;
	reloadSound->pause();
}

void Gun::holster() {
	if (reloadTime > 0) cancelReload();
}

GunCollectable* Gun::drop() {
	if (reloadTime > 0) cancelReload();
	holder = NULL;
	return new GunCollectable(this);
}

int Gun::getLineOfSight() {
	return WIDTH / 2 - 50;
}

void Gun::notifyHolderObservers() {
	if (holder != NULL) {
		for (auto const& observer : holder->observers)
			observer->onCharacterAmmoChange(holder);
	}
}

string Gun::getName() {
	return "baseGun";
}

int Gun::getNumber() {
	return 0;
}

float Gun::calculateX() {
	return holder->x + 15 * cos(holder->aim);
}

float Gun::calculateY() {
	return holder->y + 10 * -sin(holder->aim) + height / 2 - cannonHeight / 2;
}

string Gun::getAmmoString() {
	return to_string(ammo);
}

void Gun::playShotSound() {
	if (shotSound != NULL) shotSound->play();
}

void Gun::playReloadSound() {
	if (reloadSound != NULL) reloadSound->play();
}