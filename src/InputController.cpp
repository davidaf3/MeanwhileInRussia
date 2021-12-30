#include "InputController.h"
#include "Game.h"

InputController::InputController(Game* game) {
	this->game = game;
}

void InputController::init() {
	controlContinue = false;
	controlCrouch = false;
	controlGetUp = false;
	controlJump = false;
	controlReload = false;
	controlSelectGun = false;
	controlNextGun = false;
	controlPreviousGun = false;
	toggleFocus = false;

	SDL_GetMouseState(&controlAimX, &controlAimY);
	controlMoveX = 0;
}

void InputController::processControls() {
	controlContinue = false;
	controlCrouch = false;
	controlGetUp = false;
	controlJump = false;
	controlReload = false;
	controlSelectGun = false;
	controlNextGun = false;
	controlPreviousGun = false;
	toggleFocus = false;

	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event))
		inputToControls(event);
}

void InputController::inputToControls(SDL_Event event) {
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
		controlShoot = true;
		return;
	}

	if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
		controlShoot = false;
		return;
	}

	if (event.type == SDL_MOUSEWHEEL) {
		if (event.wheel.y < 0) controlNextGun = true;
		if (event.wheel.y > 0) controlPreviousGun = true;
	}

	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
			case SDLK_ESCAPE:
				game->loopActive = false;
				break;
			case SDLK_d: // derecha
				controlMoveX = 1;
				break;
			case SDLK_a: // izquierda
				controlMoveX = -1;
				break;
			case SDLK_w: // arriba
				controlJump = true;
				break;
			case SDLK_s: // abajo
				controlCrouch = true;
				break;
			case SDLK_r:
				controlReload = true;
				break;
			case SDLK_SPACE:
				controlContinue = true;
				break;
			case SDLK_LSHIFT:
				toggleFocus = !toggleFocus;
			default:
				if (code > SDLK_0 && code < SDLK_9) { // Cambio de arma
					controlSelectGun = true;
					selectedGun = code - 49;
				}
			}
	}

	if (event.type == SDL_KEYUP) {
		int code = event.key.keysym.sym;
		// Levantada
		switch (code) {
			case SDLK_d: // derecha
				if (controlMoveX == 1) {
					controlMoveX = 0;
				}
				break;
			case SDLK_a: // izquierda
				if (controlMoveX == -1) {
					controlMoveX = 0;
				}
				break;
			case SDLK_s: // abajo
				controlGetUp = true;
				break;
		}
	}

	if (event.type == SDL_MOUSEMOTION) {
		controlAimX = event.motion.x + halfCursorSide;
		controlAimY = event.motion.y + halfCursorSide;
	}
}