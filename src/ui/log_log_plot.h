#pragma once

#include "ui/widget.h"
#include <vector>

class GlobalState;

class LogLogPlot : public Widget {
    std::vector<int> data;
public:
    LogLogPlot(float cx, float cy, float w, float h) : Widget(cx, cy, w, h) {}
    void setData(const std::vector<int>& d){ data = d; }

    void update(GlobalState& gs) override;
    void draw(GlobalState& gs) override;
};
