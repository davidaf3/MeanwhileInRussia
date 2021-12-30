#pragma once
#include "MenuLayer.h"
class EndLayer :
    public MenuLayer
{
public:
    static EndLayer* instance(Game* game);
    void onContinue() override;
private:
    static EndLayer* _instance;
    EndLayer(Game* game);
};
