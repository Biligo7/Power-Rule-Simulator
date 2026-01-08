#pragma once

#include "scene.h"
#include "graphics.h"
#include "config.h"
#include "ui/button.h"
#include <vector>

class MenuScene : public Scene {
    std::vector<Button*> buttons;
public:
    ~MenuScene() override {
        for (auto* b : buttons) delete b;
    }

    void init(GlobalState& gs) override;
    void update(GlobalState& gs) override;
    void draw(GlobalState& gs) override;
};
