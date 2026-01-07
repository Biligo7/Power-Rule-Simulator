#pragma once

class GlobalState;

class Widget {
protected:
    float cx { 0.0f }, cy { 0.0f }, w { 0.0f }, h { 0.0f };
public:
    Widget(float cx_, float cy_, float w_, float h_) : cx(cx_), cy(cy_), w(w_), h(h_) {}
    virtual ~Widget() = default;
    virtual void update(GlobalState& gs) = 0;
    virtual void draw(GlobalState& gs) = 0;

    float centerX() const { return cx; }
    float centerY() const { return cy; }
    float width() const { return w; }
    float height() const { return h; }
};
