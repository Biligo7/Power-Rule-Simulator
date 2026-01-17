#pragma once

#include <functional>
#include <string>
#include "ui/widget.h"
#include "config.h"
#include "utils/collision.h"
#include "graphics.h"

class Button : public Widget {
    std::string label;
    std::function<void()> onClick;
    bool pressedLast { false };
    std::string texturePath;
public:
    Button(float cx_, float cy_, float w_, float h_, std::string text, std::function<void()> cb)
    : Widget(cx_, cy_, w_, h_), label(std::move(text)), onClick(std::move(cb)) {}

    void setTexture(const std::string& path){ texturePath = path; }

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
        if (!texturePath.empty()){
            // Draw textured button with low opacity and border
            br.texture = texturePath;
            br.fill_color[0] = 1.0f; br.fill_color[1] = 1.0f; br.fill_color[2] = 1.0f;
            br.fill_opacity = 0.6f; // lower opacity for the image
            br.outline_color[0] = cfg::accent_blue_r/255.0f;
            br.outline_color[1] = cfg::accent_blue_g/255.0f;
            br.outline_color[2] = cfg::accent_blue_b/255.0f;
            br.outline_opacity = 1.0f;
            br.outline_width = 4.0f;
            graphics::drawRect(cx, cy, w, h, br);
            // Overlay label text centered-ish on the image
            if (!label.empty()){
                graphics::Brush tbr;
                tbr.fill_color[0] = cfg::accent_blue_r/255.0f;
                tbr.fill_color[1] = cfg::accent_blue_g/255.0f;
                tbr.fill_color[2] = cfg::accent_blue_b/255.0f;
                float textSize = h * 0.18f;
                float textX = cx - w * 0.35f;
                float textY = cy + textSize * 0.4f;
                graphics::drawText(textX, textY, textSize, label, tbr);
            }
        } else {
            // Fallback styled button
            br.fill_color[0] = 0.0f; br.fill_color[1] = 0.0f; br.fill_color[2] = 0.0f;
            graphics::drawRect(cx, cy, w, h, br);
            br.fill_color[0] = 76.0f/255.0f; br.fill_color[1] = 161.0f/255.0f; br.fill_color[2] = 175.0f/255.0f;
            graphics::drawRect(cx, cy, w-6.0f, h-6.0f, br);
            br.fill_color[0] = 1.0f; br.fill_color[1] = 1.0f; br.fill_color[2] = 1.0f;
            graphics::drawText(cx - w*0.4f, cy + h*0.12f, 16.0f, label, br);
        }
    }
};
