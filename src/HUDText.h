#pragma once
#include "CharacterObserver.h"
#include "Game.h"
#include <functional>

class HUDText : 
    public CharacterObserver
{
public:
    HUDText(string iconFilename, int iconFileWidth, int iconFileHeight, int iconWidth,  int iconHeight, bool iconLeft, 
        bool anchorLeft, float x, float y, string initialContent, Game* game);
    void draw();
    TTF_Font* font;
    TTF_Font* fontOutline;
    SDL_Texture* iconTexture;
    int iconFileWidth;
    int iconFileHeight;
    int iconWidth;
    int iconHeight;
    bool iconLeft;
    bool anchorLeft;
    float x; // La x hace referencia al extremo en el que se encuentra el icono
    float y;
    Game* game;
    string content;

    static const int textIconSeparation = 10;

    void onCharacterDead(Character* character, GunCollectable* droppedGun) override;
    void onEnemyKilled() override;
    void onCharacterFire(Projectile* projectile) override;
    void onCharacterAmmoChange(Character* character) override;
    void onCharacterHealthChange(Character* character) override;
    void onCharacterFocusChange(Character* character) override;

    function<void(HUDText*, Character*, GunCollectable*)> onCharacterDeadLambda = [](HUDText*, Character*, GunCollectable*) -> void {};
    function<void(HUDText*)> onEnemyKilledLambda = [](HUDText*) -> void {};
    function<void(HUDText*, Projectile*)> onCharacterFireLambda = [](HUDText*, Projectile*) -> void {};
    function<void(HUDText*, Character*)> onCharacterAmmoChangeLambda = [](HUDText*, Character*) -> void {};
    function<void(HUDText*, Character*)> onCharacterHealthChangeLambda = [](HUDText*, Character*) -> void {};
    function<void(HUDText*, Character*)> onCharacterFocusChangeLambda = [](HUDText*, Character*) -> void {};
};
