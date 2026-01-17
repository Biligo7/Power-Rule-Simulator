#pragma once

#include "scene.h"
#include "domain/grid.h"
#include "ui/button.h"
#include "ui/slider.h"
#include "ui/log_log_plot.h"
#include <vector>
#include <deque>
#include <utility>

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
    LogLogPlot* plotWidget { nullptr };

    struct ScheduledIgnition { int x; int y; float time; };
    std::deque<ScheduledIgnition> ignitionQueue;

    // Power-law data collection for graph
    bool eventActive { false };
    int currentEventBurnCount { 0 };
    std::vector<int> fireSizes;

    void tick(GlobalState& gs);
    void igniteClusterFrom(GlobalState& gs, int sx, int sy);
    bool anyTreeBurning() const;
    int countBurningTrees() const;
    void updateEventLifecycle(bool burningNow);
    

public:
    ForestFireScene();
    ~ForestFireScene() override;

    void init(GlobalState& gs) override;
    void update(GlobalState& gs) override;
    void draw(GlobalState& gs) override;
};
