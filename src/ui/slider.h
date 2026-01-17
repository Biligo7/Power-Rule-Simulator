#pragma once

#include "ui/widget.h"
#include "utils/collision.h"
#include "graphics.h"
#include <string>

class Slider : public Widget {
    float minV, maxV;
    float value;
    bool dragging { false };
    std::string label;
public:
    Slider(float cx_, float cy_, float w_, float h_, float minV_, float maxV_, float initV_, std::string label_)
    : Widget(cx_, cy_, w_, h_), minV(minV_), maxV(maxV_), value(initV_), label(std::move(label_)) {}

    float getValue() const { return value; }
    void setValue(float v) { value = (v < minV ? minV : (v > maxV ? maxV : v)); }

    void update(GlobalState& gs) override {
        graphics::MouseState ms; graphics::getMouseState(ms);
        float mx = graphics::windowToCanvasX((float)ms.cur_pos_x);
        float my = graphics::windowToCanvasY((float)ms.cur_pos_y);
        float knobX = cx - w*0.5f + (value - minV)/(maxV - minV) * w;
        bool overKnob = collision::pointInRect(knobX, cy, h, h, mx, my);
        if (ms.button_left_down && (overKnob || dragging)){
            dragging = true;
            float rel = (mx - (cx - w*0.5f));
            if (rel < 0){ rel = 0; } if (rel > w){ rel = w; }
            value = minV + (rel / w) * (maxV - minV);
        } else {
            dragging = false;
        }
    }

    void draw(GlobalState& gs) override {
        // Track
        graphics::Brush br;
        br.fill_color[0] = 0.0f; br.fill_color[1] = 0.0f; br.fill_color[2] = 0.0f;
        graphics::drawRect(cx, cy, w, h, br);
        br.fill_color[0] = 76.0f/255.0f; br.fill_color[1] = 161.0f/255.0f; br.fill_color[2] = 175.0f/255.0f;
        graphics::drawRect(cx, cy, w-6.0f, h-6.0f, br);
        // Knob
        float knobX = cx - w*0.5f + (value - minV)/(maxV - minV) * w;
        br.fill_color[0] = 60.0f/255.0f; br.fill_color[1] = 196.0f/255.0f; br.fill_color[2] = 124.0f/255.0f;
        graphics::drawRect(knobX, cy, h, h, br);
        // Label & value
        br.fill_color[0] = 1.0f; br.fill_color[1] = 1.0f; br.fill_color[2] = 1.0f;
        graphics::drawText(cx - w*0.5f, cy - h*0.8f, 14.0f, label, br);
        char buf[64];
        snprintf(buf, sizeof(buf), "%.4f", value);
        graphics::drawText(cx + w*0.3f, cy - h*0.8f, 14.0f, buf, br);
    }
};
