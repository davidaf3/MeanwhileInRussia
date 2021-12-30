#include "EndLayer.h"
#include "IntroLayer.h"

EndLayer* EndLayer::_instance = NULL;

EndLayer* EndLayer::instance(Game* game) {
	if (_instance == NULL)
		_instance = new EndLayer(game);
	return _instance;
}

EndLayer::EndLayer(Game* game) : MenuLayer("res/end.png", game) {}

void EndLayer::onContinue() {
	game->changeLayer(IntroLayer::instance(game));
}