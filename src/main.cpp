#include "graphics.h"
#include "global_state.h"
#include "config.h"

static GlobalState g_state;

static void draw() {
	g_state.draw();
}

static void update(float ms) {
	(void)ms;
	g_state.update();
	// Optional: exit on ESC
	if (graphics::getKeyState(graphics::SCANCODE_ESCAPE)) {
		graphics::stopMessageLoop();
	}
}

int main() {
	graphics::createWindow((int)cfg::canvas_w, (int)cfg::canvas_h, "Power-Law Simulator");
	graphics::setCanvasSize(cfg::canvas_w, cfg::canvas_h);
	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);

	g_state.init();

	graphics::startMessageLoop();
	graphics::destroyWindow();
	return 0;
}

