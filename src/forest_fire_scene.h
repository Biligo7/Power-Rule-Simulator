#pragma once

#include "scene.h"
#include "domain/grid.h"
#include "ui/button.h"
#include "ui/slider.h"
#include <vector>
#include <deque>

class ForestFireScene : public Scene {
    Grid grid;
    float cellW { 0.0f }, cellH { 0.0f };
    float accumMs { 0.0f };

    // Parameters controlled by sliders
    float p_grow;
    float p_lightning;
    float tickMs;
    float chainDelayMs { 10.0f }; // delay between neighbor ignitions (ms)

    // UI
    std::vector<Slider*> sliders;
    Button* backBtn { nullptr };

    struct ScheduledIgnition { int x; int y; float time; };
    std::deque<ScheduledIgnition> ignitionQueue;

    void tick(GlobalState& gs);
    void igniteClusterFrom(GlobalState& gs, int sx, int sy);

public:
    ForestFireScene();
    ~ForestFireScene() override;

    void init(GlobalState& gs) override;
    void update(GlobalState& gs) override;
    void draw(GlobalState& gs) override;
};
