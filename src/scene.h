#pragma once

class GlobalState;

class Scene {
public:
    virtual ~Scene() = default;
    virtual void init(GlobalState& gs) = 0;
    virtual void update(GlobalState& gs) = 0;
    virtual void draw(GlobalState& gs) = 0;
};
