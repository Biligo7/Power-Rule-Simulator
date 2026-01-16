#include "forest_fire_scene.h"
#include "global_state.h"
#include "config.h"
#include "graphics.h"
#include "utils/random.h"
#include "menu_scene.h"

ForestFireScene::ForestFireScene()
    : grid(cfg::grid_w, cfg::grid_h), p_grow(cfg::default_p_grow),
      p_lightning(cfg::default_p_lightning), tickMs(cfg::default_tick_ms) {}

ForestFireScene::~ForestFireScene() {
    for (auto* s : sliders) delete s;
    sliders.clear();
    if (backBtn) { delete backBtn; backBtn = nullptr; }
}

void ForestFireScene::init(GlobalState& gs) {
    float cw = gs.getCanvasW();
    float ch = gs.getCanvasH();
    // Compute cell size to fit a square area on the left
    float areaW = cw * 0.65f;
    float areaH = ch * 0.8f;
    cellW = areaW / grid.width();
    cellH = areaH / grid.height();

    // Sliders on the right
    float sx = cw * 0.85f;
    float baseY = ch * 0.35f;
    float dy = 90.0f;
    sliders.push_back(new Slider(sx, baseY + 0*dy, 240.0f, 20.0f, 0.0f, 0.01f, p_grow, "Tree growth p_grow"));
    sliders.push_back(new Slider(sx, baseY + 1*dy, 240.0f, 20.0f, 0.0f, 0.1f, p_lightning, "Lightning p_lightning"));
    sliders.push_back(new Slider(sx, baseY + 2*dy, 240.0f, 20.0f, 0.0f, 100.0f, tickMs, "Tick interval (ms)"));

    // Back button top-left
    backBtn = new Button(cw * 0.09f, ch * 0.08f, 120.0f, 36.0f, "< Back", [&gs]() {
        gs.queueScene(new MenuScene());
    });
}

void ForestFireScene::tick(GlobalState& gs) {
    // 1) Growth
    for (int y = 0; y < grid.height(); ++y) {
        for (int x = 0; x < grid.width(); ++x) {
            if (grid.empty(x,y)) {
                if (Random::uniform01() < p_grow) {
                    grid.set(x,y, new Tree());
                }
            }
        }
    }

    // 2) Lightning: allow only if no ongoing fire and no queued propagation
    if (!anyTreeBurning() && ignitionQueue.empty() && Random::uniform01() < p_lightning) {
        Cell c;
         if (grid.randomOccupiedCell(c)) {
            igniteClusterFrom(gs, c.x, c.y);
        }
    }

    // 3) Delete expired
    float nowMs = graphics::getGlobalTime();
    for (int y = 0; y < grid.height(); ++y) {
        for (int x = 0; x < grid.width(); ++x) {
            Tree* t = grid.get(x,y);
            if (t && t->shouldDelete(nowMs, cfg::burning_lifetime_ms)) {
                delete t; grid.clear(x,y);
            }
        }
    }
}

bool ForestFireScene::anyTreeBurning() const {
    for (int y = 0; y < grid.height(); ++y) {
        for (int x = 0; x < grid.width(); ++x) {
            Tree* t = grid.get(x,y);
            if (t && t->state == Tree::Burning) return true;
        }
    }
    return false;
}

void ForestFireScene::igniteClusterFrom(GlobalState& gs, int sx, int sy) {
    // Schedule staged ignition with small delays to create a visual chain effect
    float startMs = graphics::getGlobalTime();
    std::queue<std::pair<Cell,int>> q; // cell + BFS depth
    std::vector<char> visited(grid.width() * grid.height(), 0);
    auto markVisited = [&](int x, int y){ visited[grid.index(x,y)] = 1; };
    auto isVisited = [&](int x, int y){ return visited[grid.index(x,y)] != 0; };

    q.push({Cell{sx, sy}, 0});
    markVisited(sx, sy);
    while (!q.empty()) {
        auto cur = q.front(); q.pop();
        Cell c = cur.first; int depth = cur.second;
        Tree* t = grid.get(c.x, c.y);
        if (t != nullptr) {
            float scheduleTime = startMs + depth * chainDelayMs;
            ignitionQueue.push_back({c.x, c.y, scheduleTime});
            for (auto n : grid.neighbors4(c.x, c.y)) {
                if (!isVisited(n.x, n.y)) {
                    Tree* tn = grid.get(n.x, n.y);
                    if (tn != nullptr) {
                        markVisited(n.x, n.y);
                        q.push({n, depth + 1});
                    }
                }
            }
        }
    }
}

void ForestFireScene::update(GlobalState& gs) {
    // Update UI
    for (auto* s : sliders) s->update(gs);
    if (backBtn) backBtn->update(gs);

    // Read parameters
    p_grow = sliders[0]->getValue();
    p_lightning = sliders[1]->getValue();
    tickMs = sliders[2]->getValue();

    // Timing
    float dt = graphics::getDeltaTime();
    accumMs += dt;
    if (accumMs >= tickMs) {
        tick(gs);
        // Keep remainder to prevent drift
        accumMs = 0.0f;
    }

    // Process staged ignitions
    float nowMs = graphics::getGlobalTime();
    while (!ignitionQueue.empty() && ignitionQueue.front().time <= nowMs) {
        auto ev = ignitionQueue.front(); ignitionQueue.pop_front();
        if (grid.inBounds(ev.x, ev.y)) {
            Tree* t = grid.get(ev.x, ev.y);
            if (t && t->state == Tree::Alive) {
                t->ignite(ev.time);
            }
        }
    }
}

void ForestFireScene::draw(GlobalState& gs) {
    float cw = gs.getCanvasW();
    float ch = gs.getCanvasH();
    // Background
    graphics::Brush br;
    br.fill_color[0] = cfg::bg_r/255.0f; br.fill_color[1] = cfg::bg_g/255.0f; br.fill_color[2] = cfg::bg_b/255.0f;
    graphics::drawRect(cw*0.5f, ch*0.5f, cw, ch, br);

    // Draw grid area bounds
    float areaW = cw * 0.65f;
    float areaH = ch * 0.8f;
    float areaCx = cw * 0.375f;
    float areaCy = ch * 0.55f;
    br.fill_color[0] = 0.0f; br.fill_color[1] = 0.0f; br.fill_color[2] = 0.0f;
    graphics::drawRect(areaCx, areaCy, areaW + 4.0f, areaH + 4.0f, br);

    // Draw cells
    // Disable outlines to avoid visible lines between adjacent cells
    br.outline_opacity = 0.0f;
    for (int y = 0; y < grid.height(); ++y) {
        for (int x = 0; x < grid.width(); ++x) {
            float cxCell = areaCx - areaW*0.5f + (x + 0.5f) * cellW;
            float cyCell = areaCy - areaH*0.5f + (y + 0.5f) * cellH;
            Tree* t = grid.get(x,y);
            if (!t) {
                // empty: draw subtle dark
                br.fill_color[0] = 0.12f; br.fill_color[1] = 0.12f; br.fill_color[2] = 0.12f;
            } else if (t->state == Tree::Alive) {
                br.fill_color[0] = cfg::tree_alive_r/255.0f; br.fill_color[1] = cfg::tree_alive_g/255.0f; br.fill_color[2] = cfg::tree_alive_b/255.0f;
            } else {
                br.fill_color[0] = cfg::tree_burning_r/255.0f; br.fill_color[1] = cfg::tree_burning_g/255.0f; br.fill_color[2] = cfg::tree_burning_b/255.0f;
            }
            graphics::drawRect(cxCell, cyCell, cellW, cellH, br);
        }
    }

    // Title and back button
    br.fill_color[0] = cfg::accent_blue_r/255.0f; br.fill_color[1] = cfg::accent_blue_g/255.0f; br.fill_color[2] = cfg::accent_blue_b/255.0f;
    graphics::drawText(cw*0.30f, ch*0.12f, 30.0f, "Forest Fire Simulator", br);
    if (backBtn) backBtn->draw(gs);
    // Sliders
    for (auto* s : sliders) s->draw(gs);
}
