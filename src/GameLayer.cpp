#include "GameLayer.h"
#include "TMXLoader.h"
#include "InputController.h"
#include "GunCollectable.h"
#include "MP3Audio.h"
#include "LevelCompleteLayer.h"
#include "Pistol.h"
#include <set>

GameLayer* GameLayer::_instance = NULL;

GameLayer* GameLayer::instance(Game* game) {
	if (_instance == NULL)
		_instance = new GameLayer(game);
	return _instance;
}

GameLayer::GameLayer(Game* game)
		: Layer(game) {
	this->pause = false;
	this->inputController = new InputController(game);
	this->background = new Background("res/fondo.png", WIDTH * 0.5, HEIGHT * 0.5, 0, game);

	this->ammoText = new HUDText("res/icons/ammo_icon.png", 40, 51, 20, 25, true, true, WIDTH * 0.03, HEIGHT * 0.06, "", game);
	this->healthText = new HUDText("res/icons/heart_icon.png", 18, 18, 18, 18, true, true, WIDTH * 0.03, HEIGHT * 0.94, "", game);
	this->focusText = new HUDText("res/icons/focus_icon.png", 50, 184, 7, 25, false, false, WIDTH * 0.97, HEIGHT * 0.94, "", game);
	this->texts.push_back(ammoText);
	this->texts.push_back(healthText);
	this->texts.push_back(focusText);
}

void GameLayer::setToFirstLevel() {
	currentLevel.number = 0;
	currentLevel.initialGun = 0;
	currentLevel.initialGunsInventory.insert(0);
	currentLevel.initialAmmoInventory["Pistola"] = 5 * Pistol::pistolMagSize;
	deletePlayer();
}

void GameLayer::deletePlayer() {
	if (player != NULL) {
		// Finaliza el estado actual del jugador
		player->state->beforeStateChange(player);

		characters.remove(player);
		delete player;
		player = NULL;
	}
}

void GameLayer::init() {
	inputController->init();
	space = new Space(1);
	enemiesKilled = 0;
	startTimeMillis = 
		chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());

	for (auto const& tile : tiles) {
		delete tile;
	}
	tiles.clear();

	for (auto const& character : characters) {
		if (character != player) delete character;
	}
	characters.clear();

	for (auto const& projectile : projectiles) {
		delete projectile;
	}
	projectiles.clear();

	for (auto const& collectable : collectables) {
		delete collectable;
	}
	collectables.clear();

	backgroundMusic = new MP3Audio("res/sounds/background_music.mp3");
	backgroundMusic->play();

	TMXLoader::loadMapTMX(levels[currentLevel.number], this, &currentLevel);
	characters.push_back(player);

	ammoText->content = player->getAmmoString();
	ammoText->onCharacterAmmoChangeLambda = [](HUDText* text, Character* character) -> void {
		text->content = character->getAmmoString();
	};

	healthText->content = player->getHealthString();
	healthText->onCharacterHealthChangeLambda = [](HUDText* text, Character* character) -> void {
		text->content = character->getHealthString();
	};

	focusText->content = player->getFocusString();
	focusText->onCharacterFocusChangeLambda = [](HUDText* text, Character* character) -> void {
		text->content = character->getFocusString();
	};

	scrollX = 0;
	scrollY = currentLevel.mapHeight - HEIGHT;
}

void GameLayer::processControls() {
	inputController->processControls();
	
	if (inputController->controlContinue) pause = false;

	// Armas
	if (inputController->controlReload) player->reload();
	if (inputController->controlSelectGun) player->selectGun(inputController->selectedGun);
	if (inputController->controlNextGun) player->selectNextGun();
	if (inputController->controlPreviousGun) player->selectPreviousGun();

	// Concentración
	if (inputController->toggleFocus) {
		if (!player->focus) player->startFocus();
		else player->stopFocus();
	}

	// Eje X
	if (inputController->controlMoveX != 0) {
		player->moveX(inputController->controlMoveX > 0 ? 1 : -1);
	} else player->moveX(0);

	// Eje Y
	if (inputController->controlJump) player->jump();
	if (inputController->controlCrouch) player->crouch(space);
	if (inputController->controlGetUp) player->getUp(space);
}

void GameLayer::update() {
	if (pause) return;

	space->update();
	background->update();

	for (auto const& character : characters) {
		character->update();
	}
	
	// El jugador apunta y dispara después de moverse para
	// que los disparos sean más precisos
	player->aimAt(inputController->controlAimX + scrollX,
		inputController->controlAimY + scrollY);
	if (inputController->controlShoot) player->shoot();

	set<Projectile*> deletedProjectiles;

	for (auto const& projectile : projectiles) {
		projectile->update();

		for (auto const& character : characters) {
			if (!character->isDead && projectile->isOverlap(character)) 
				projectile->hit(character);
		}

		if (projectile->timeToLive == 0) 
			deletedProjectiles.insert(projectile);
	}

	for (auto const& projectile : deletedProjectiles) {
		projectiles.remove(projectile);
		space->removeDynamicActor(projectile);
		delete projectile;
	}

	list<Collectable*>::iterator collectablesIterator = collectables.begin();
	while (collectablesIterator != collectables.end()) {
		Collectable* collectable = *collectablesIterator;
		collectable->update();

		if (player->health > 0 && player->isOverlap(collectable)) {
			collectable->collect(player);
			collectablesIterator = collectables.erase(collectablesIterator);
			space->removeDynamicActor(collectable);
			delete collectable;
		}
		else collectablesIterator++;
	}

	// Jugador se sale por la derecha
	if (player->x < 0) {
		player->x = 0;
		player->vx = 0;
	}

	// Jugador muere o se cae
	if (player->isDead || player->y > currentLevel.mapHeight + 80) onGameOver();

	// Jugador llega al final del nivel
	if (player->x > currentLevel.endLevelX) onLevelComplete();
}

void GameLayer::calculateScroll() {
	if (player->x < currentLevel.mapWidth - WIDTH * 0.5 && player->x > WIDTH * 0.5) {
		scrollX = player->x - WIDTH * 0.5;
	}

	if (player->y < currentLevel.mapHeight - HEIGHT * 0.5 && player->y > HEIGHT * 0.5) {
		scrollY = player->y - HEIGHT * 0.5;
	}
}

void GameLayer::draw() {
	calculateScroll();

	background->draw();

	for (auto const& tile : tiles) {
		tile->draw(scrollX, scrollY);
	}

	for (auto const& character : characters) {
		character->draw(scrollX, scrollY);
	}

	for (auto const& collectable : collectables) {
		collectable->draw(scrollX, scrollY);
	}

	for (auto const& projectile : projectiles) {
		projectile->draw(scrollX, scrollY);
	}

	for (auto const& text : texts) {
		text->draw();
	}

	SDL_RenderPresent(game->renderer); // Renderiza
}

void GameLayer::onGameOver() {
	delete backgroundMusic;
	deletePlayer();
	init();
}

void GameLayer::onLevelComplete() {
	currentLevel.initialGunsInventory.clear();
	// Guarda las armas y munición que tenía el jugador al terminar el nivel
	for (int i = 0; i < 8; i++) {
		if (player->gunsInventory[i] != NULL) currentLevel.initialGunsInventory.insert(i);
	}
	currentLevel.initialAmmoInventory = map<string, int>(player->ammoInventory);
	currentLevel.initialGun = player->gun->getNumber();

	// Destruye el jugador para que su estado se reinicie en el siguiente nivel
	deletePlayer();

	game->changeLayer(LevelCompleteLayer::instance(this->game));
}

void GameLayer::onCharacterDead(Character* character, GunCollectable* droppedGun) {
	collectables.push_back(droppedGun);
	space->addDynamicActor(droppedGun);
}

void GameLayer::onEnemyKilled() {
	enemiesKilled++;
}

void GameLayer::onCharacterFire(Projectile* projectile) {
	// Comprobamos que haya espacio para el proyectil
	// Con comprobar el pixel central del proyectil es suficiente
	if (space->isRectFree(projectile->x, projectile->y, 1, 1)) {
		projectile->addToSpace(space);
		projectiles.push_back(projectile);
	}
}
