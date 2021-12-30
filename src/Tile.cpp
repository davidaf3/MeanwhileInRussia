#include "Tile.h"
#include "GameLayer.h"

Tile::Tile(string filename, int tileNum, float x, float y, int tilesetWidth, int tilesetHeight, Game* game, Level* level)
	: Actor(filename, x, y, tilesetWidth, tilesetHeight, game) {

	this->level = level;
	this->tileNum = tileNum;
	this->width = 32;
	this->height = 32;
}

void Tile::draw(float scrollX, float scrollY) {
	// Recorte en el fichero de la imagen
	// Posición del Tile que queremos seleccionar de toda la hoja
	int xOfTileInFile = (tileNum - 1) % level->tilesetColumns;
	int yOfTileInFile = (tileNum - 1) / level->tilesetColumns;

	// Recortar en la foto
	SDL_Rect source;
	source.x = xOfTileInFile * (32 + level->tilesetSpacing) + level->tilesetMargin;
	source.y = yOfTileInFile * (32 + level->tilesetSpacing) + level->tilesetMargin;
	source.w = 32;
	source.h = 32;

	// Donde se va a pegar en el renderizador
	SDL_Rect destination;
	destination.x = x - 32 / 2 - scrollX;
	destination.y = y - 32 / 2 - scrollY;
	destination.w = 32;
	destination.h = 32;
	// Modificar para que la referencia sea el punto central

	SDL_RenderCopyEx(game->renderer,
		texture, &source, &destination, 0, NULL, SDL_FLIP_NONE);
}