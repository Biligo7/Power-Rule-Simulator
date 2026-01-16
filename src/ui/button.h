#pragma once

#include <functional>
#include <string>
#include "ui/widget.h"
#include "utils/collision.h"
#include "graphics.h"

class Button : public Widget {
    std::string label;
    std::function<void()> onClick;
    bool pressedLast { false };
public:
    Button(float cx_, float cy_, float w_, float h_, std::string text, std::function<void()> cb)
    : Widget(cx_, cy_, w_, h_), label(std::move(text)), onClick(std::move(cb)) {}

    void update(GlobalState& gs) override {
        graphics::MouseState ms;
        graphics::getMouseState(ms);
        float mx = graphics::windowToCanvasX((float)ms.cur_pos_x);
        float my = graphics::windowToCanvasY((float)ms.cur_pos_y);
        bool inside = collision::pointInRect(cx, cy, w, h, mx, my);
        bool pressed = ms.button_left_down;
        if (inside && pressed && !pressedLast && onClick){
            onClick();
        }
        pressedLast = pressed;
    }

    void draw(GlobalState& gs) override {
        graphics::Brush br;
        br.fill_color[0] = 0.0f; br.fill_color[1] = 0.0f; br.fill_color[2] = 0.0f;
        graphics::drawRect(cx, cy, w, h, br);
        br.fill_color[0] = 76.0f/255.0f; br.fill_color[1] = 161.0f/255.0f; br.fill_color[2] = 175.0f/255.0f;
        graphics::drawRect(cx, cy, w-6.0f, h-6.0f, br);
        br.fill_color[0] = 1.0f; br.fill_color[1] = 1.0f; br.fill_color[2] = 1.0f;
        graphics::drawText(cx - w*0.4f, cy + h*0.12f, 16.0f, label, br);
    }
};
