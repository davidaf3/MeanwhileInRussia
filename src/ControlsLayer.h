#pragma once
#include "MenuLayer.h"

class ControlsLayer :
    public MenuLayer
{
public:
    static ControlsLayer* instance(Game* game);
    void onContinue() override;
private:
    static ControlsLayer* _instance;
    ControlsLayer(Game* game);
};
