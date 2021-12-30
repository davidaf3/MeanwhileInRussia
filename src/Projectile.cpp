#include "Projectile.h"
#include "Space.h"
#include "Character.h"
#include "WAVAudio.h"

Projectile::Projectile(string filename, float x, float y, int width, int height, Game* game, float vx, float vy,
	int damage, int headshotDamage, Character* owner) :
	Actor(filename, x, y, width, height, game) {
	this->timeToLive = 60;
	this->vx = vx;
	this->vy = vy;
	this->initialHeight = height;
	this->initialWidth = width;
	this->damage = damage;
	this->headshotDamage = headshotDamage;
	this->owner = owner;
}

Projectile::~Projectile() {}

void Projectile::update() {
	if (timeToLive > 0) timeToLive--;

	// Transforma la anchura y altura de acuerdo al ángulo de la bala
	float angle = atan2f(-vy, vx);
	width = initialHeight + (initialWidth - initialHeight) * abs(cos(angle));
	height = initialHeight + (initialWidth - initialHeight) * abs(sin(angle));

	if (collisionDown || collisionTop || collisionLeft || collisionRight) onCollision();
}

void Projectile::onCollision() {
	timeToLive = 0;
}

void Projectile::hit(Character* character) {
	if (character != owner) {
		character->hitLeft = false;
		character->hitRight = false;
		if (x < character->x) character->hitLeft = true;
		else character->hitRight = true;
		character->takeHit(character->isHeadshot(this) ? headshotDamage : damage);
		timeToLive = 0;
	}
}

void Projectile::addToSpace(Space* space) {
	space->addDynamicActor(this);
}

void Projectile::removeFromSpace(Space* space) {
	space->removeDynamicActor(this);
}

void Projectile::move(float deltaX, float deltaY) {
	x += deltaX;
	y += deltaY;
}

float Projectile::getTipY() {
	if (vy == 0) return y;
	return y + (vy > 0 ? height / 2 : -height / 2);
}

float Projectile::getTipX() {
	if (vx == 0) return x;
	return x + (vx > 0 ? width / 2 : -width / 2);
}

void Projectile::draw(float scrollX, float scrollY) {
	// Recorte en el fichero de la imagen
	SDL_Rect source;
	source.x = 0;
	source.y = 0;
	source.w = fileWidth; // texture.width;
	source.h = fileHeight; // texture.height;

	// Donde se va a pegar en el renderizador
	SDL_Rect destination;
	destination.x = x - initialWidth / 2 - scrollX;
	destination.y = y - initialHeight / 2 - scrollY;
	destination.w = initialWidth;
	destination.h = initialHeight;
	// Modificar para que la referencia sea el punto central

	float angle = atan2f(-vy, vx) * 180 / M_PI;
	SDL_RendererFlip flip = vx > 0 ? SDL_FLIP_NONE : SDL_FLIP_VERTICAL;

	SDL_RenderCopyEx(game->renderer,
		texture, &source, &destination, -angle, NULL, flip);
}

bool Projectile::gravity() {
	return false;
}