#pragma once

#include "scene.h"

class GlobalState {
    Scene* activeScene { nullptr };
    Scene* pendingScene { nullptr };
    float canvasW { 1024.0f };
    float canvasH { 768.0f };
    bool exitRequested { false };
    bool fullscreen { false };

public:
    GlobalState() = default;
    ~GlobalState();

    void setCanvasSize(float w, float h) { canvasW = w; canvasH = h; }
    float getCanvasW() const { return canvasW; }
    float getCanvasH() const { return canvasH; }

    void setScene(Scene* s);
    void queueScene(Scene* s);
    Scene* getScene() const { return activeScene; }

    void requestExit() { exitRequested = true; }
    bool shouldExit() const { return exitRequested; }

    void setFullscreen(bool fs) { fullscreen = fs; }
    bool isFullscreen() const { return fullscreen; }

    void init();
    void update();
    void draw();
};
