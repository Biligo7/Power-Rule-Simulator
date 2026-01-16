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
	// Toggle fullscreen on F11 (debounced until key release)
	static bool f11Latch = false;
	bool f11Pressed = graphics::getKeyState(graphics::SCANCODE_F11);
	if (f11Pressed && !f11Latch){
		f11Latch = true;
		bool fs = !g_state.isFullscreen();
		g_state.setFullscreen(fs);
		graphics::setFullScreen(fs);
		// Re-apply canvas mapping after toggling fullscreen
		graphics::setCanvasSize(cfg::canvas_w, cfg::canvas_h);
		graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
	} else if (!f11Pressed && f11Latch){
		// key released
		f11Latch = false;
	}
	// exit on ESC
	if (graphics::getKeyState(graphics::SCANCODE_ESCAPE)){
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

