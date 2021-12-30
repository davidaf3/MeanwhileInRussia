#include "MenuLayer.h"

MenuLayer::MenuLayer(string backgroundFilename, Game* game) : Layer(game) {
	this->background = new Actor(backgroundFilename, WIDTH * 0.5, HEIGHT * 0.5, WIDTH, HEIGHT, game);
	this->inputController = new InputController(game);
}

void MenuLayer::init() {
	inputController->init();
	doInit();
}

void MenuLayer::processControls() {
	inputController->processControls();
	unpause = inputController->controlContinue;
}

void MenuLayer::update() {
	if (unpause) onContinue();
}

void MenuLayer::draw() {
	background->draw();
	doDraw();
	SDL_RenderPresent(game->renderer);
}

void MenuLayer::doInit() {}

void MenuLayer::doDraw() {}

void MenuLayer::onContinue() {}