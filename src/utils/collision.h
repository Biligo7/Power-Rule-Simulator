#pragma once

namespace collision {
    inline bool pointInRect(float cx, float cy, float w, float h, float x, float y) {
        return (cx - w * 0.5f <= x && x <= cx + w * 0.5f) &&
               (cy - h * 0.5f <= y && y <= cy + h * 0.5f);
    }
}
