#include "graphics.h"
#include "global_state.h"
#include "config.h"
#include <cstdlib>

static GlobalState g_state;

static void draw() {
	g_state.draw();
}

static void update(float ms) {
	(void)ms;
	// Handle global hotkeys first
	// Toggle fullscreen on F11
	if (graphics::getKeyState(graphics::SCANCODE_F11)) {
		bool fs = !g_state.isFullscreen();
		g_state.setFullscreen(fs);
		graphics::setFullScreen(fs);
		// Re-apply canvas mapping after toggling fullscreen
		graphics::setCanvasSize(cfg::canvas_w, cfg::canvas_h);
		graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
	}
	// exit on ESC
	if (graphics::getKeyState(graphics::SCANCODE_ESCAPE)) {
		graphics::stopMessageLoop();
	}
	// Then run scene update
	g_state.update();
}

int main() {
	graphics::createWindow((int)cfg::canvas_w, (int)cfg::canvas_h, "Power-Law Simulator");
	graphics::setCanvasSize(cfg::canvas_w, cfg::canvas_h);
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
	graphics::setFont("assets/Nostard-Medium.ttf");
	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);

	g_state.init();

	graphics::startMessageLoop();
	graphics::destroyWindow();
	return 0;
}

