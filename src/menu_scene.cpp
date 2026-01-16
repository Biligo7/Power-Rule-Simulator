#include "menu_scene.h"
#include "global_state.h"
#include "forest_fire_scene.h"

void MenuScene::init(GlobalState& gs) {
    float cw = gs.getCanvasW();
    float ch = gs.getCanvasH();
    // Single card/button for Forest Fire
    buttons.push_back(new Button(cw*0.5f, ch*0.55f, 300.0f, 120.0f, "Forest Fire", [&gs]() {
        gs.queueScene(new ForestFireScene());
    }));
}

void MenuScene::update(GlobalState& gs) {
    for (Button* b : buttons) b->update(gs);
}

void MenuScene::draw(GlobalState& gs) {
    float cw = gs.getCanvasW();
    float ch = gs.getCanvasH();
    graphics::Brush br;
    br.fill_color[0] = cfg::bg_r/255.0f; br.fill_color[1] = cfg::bg_g/255.0f; br.fill_color[2] = cfg::bg_b/255.0f;
    graphics::drawRect(cw*0.5f, ch*0.5f, cw, ch, br);
    // Title
    br.fill_color[0] = cfg::accent_blue_r/255.0f; br.fill_color[1] = cfg::accent_blue_g/255.0f; br.fill_color[2] = cfg::accent_blue_b/255.0f;
    graphics::drawText(cw*0.25f, ch*0.15f, 60.0f, "Power-Law Simulator", br);
    // Horizontal black bar
    br.fill_color[0] = cfg::black_r; br.fill_color[1] = cfg::black_g; br.fill_color[2] = cfg::black_b;
    graphics::drawRect(cw*0.5f, ch*0.22f, cw*0.8f, 6.0f, br);
    // Buttons/cards
    for (Button* b : buttons) b->draw(gs);
}
