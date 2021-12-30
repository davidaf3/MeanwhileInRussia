#include "Actor.h"

Actor::Actor(string filename, float x, float y, int width, int height, Game* game) {
	this->game = game;
	texture = game->getTexture(filename);
	this->x = x;
	this->y = y;
	// lo que mide el fichero
	this->fileWidth = width;
	this->fileHeight = height;
	// lo que va a medir en el juego
	this->width = width;
	this->height = height;

	this->collisionDown = false;
	this->collisionLeft = false;
	this->collisionRight = false;
	this->collisionTop = false;
	this->outLeft = false;
	this->outRight = false;
	this->vx = 0;
	this->vy = 0;
}

Actor::~Actor() {}

void Actor::draw(float scrollX, float scrollY) {
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

	SDL_RenderCopyEx(game->renderer,
		texture, &source, &destination, 0, NULL, SDL_FLIP_NONE);
}

bool Actor::isOverlap(Actor* actor) {
	return isOverlap(actor->x, actor->y, actor->width, actor->height);
}

bool Actor::isOverlap(float x, float y, float width, float height) {
	return x - width / 2 < this->x + this->width / 2
		&& x + width / 2 > this->x - this->width / 2
		&& y + height / 2 > this->y - this->height / 2
		&& y - height / 2 < this->y + this->height / 2;
}

bool Actor::isInRender(float scrollX, float scrollY) {
	return (x - scrollX) - width / 2 <= WIDTH && x + width / 2 >= 0 &&
		(y - scrollY) - height / 2 <= HEIGHT && y + height / 2 >= 0;
}

bool Actor::containsPoint(int pointX, int pointY) {
	return pointY >= y - height / 2 &&
		pointY <= y + height / 2 &&
		pointX <= x + width / 2 &&
		pointX >= x - width / 2;
}

bool Actor::gravity() { 
	return true; 
}