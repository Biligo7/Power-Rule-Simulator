#include "global_state.h"
#include "scene.h"
#include "config.h"
#include "menu_scene.h"
#include "graphics.h"

GlobalState::~GlobalState(){
    if (activeScene){
        delete activeScene;
        activeScene = nullptr;
    }
}

void GlobalState::setScene(Scene* s){
    if (activeScene){
        delete activeScene;
    }
    activeScene = s;
    if (activeScene){
        activeScene->init(*this);
    }
}

void GlobalState::queueScene(Scene* s) {
    // Defer switching to avoid deleting current scene during its update
    pendingScene = s;
}

void GlobalState::init(){
    setCanvasSize(cfg::canvas_w, cfg::canvas_h);
    setScene(new MenuScene());
}

void GlobalState::update(){
    if (activeScene){
        activeScene->update(*this);
    }
    if (pendingScene){
        setScene(pendingScene);
        pendingScene = nullptr;
    }
}

void GlobalState::draw(){
    if (activeScene){
        activeScene->draw(*this);
    }
}
