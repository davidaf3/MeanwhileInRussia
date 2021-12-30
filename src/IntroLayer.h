#pragma once
#include "MenuLayer.h"
class IntroLayer :
    public MenuLayer
{
public:
    static IntroLayer* instance(Game* game);
    void onContinue() override;
private:
    static IntroLayer* _instance;
    IntroLayer(Game* game);
};

