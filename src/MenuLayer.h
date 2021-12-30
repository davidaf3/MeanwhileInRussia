#pragma once
#include "Layer.h"
#include "InputController.h"

class MenuLayer :
    public Layer
{
public:
    MenuLayer(string backgroundFilename, Game* game);
    void init() override;
    virtual void processControls() override;
    virtual void update() override;
    void draw() override;
    virtual void doInit();
    virtual void doDraw();
    virtual void onContinue();
    bool unpause = false;
    Actor* background;
    InputController* inputController;
};
