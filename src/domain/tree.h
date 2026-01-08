#pragma once

struct Tree {
    enum State { Alive, Burning } state { Alive };
    float ignitionMs { 0.0f };

    void ignite(float nowMs) {
        state = Burning;
        ignitionMs = nowMs;
    }

    bool shouldDelete(float nowMs, float lifetimeMs) const {
        return state == Burning && (nowMs - ignitionMs) >= lifetimeMs;
    }
};
