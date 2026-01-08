#pragma once

#include "scene.h"
#include "domain/grid.h"
#include "ui/button.h"
#include "ui/slider.h"
#include <vector>

class ForestFireScene : public Scene {
    Grid grid;
    float cellW { 0.0f }, cellH { 0.0f };
    float accumMs { 0.0f };

    // Parameters controlled by sliders
    float p_grow;
    float p_lightning;
    float tickMs;

    // UI
    std::vector<Slider*> sliders;
    Button* backBtn { nullptr };

    void tick(GlobalState& gs);
    void igniteClusterFrom(GlobalState& gs, int sx, int sy);

public:
    ForestFireScene();
    ~ForestFireScene() override;

    void init(GlobalState& gs) override;
    void update(GlobalState& gs) override;
    void draw(GlobalState& gs) override;
};
