#pragma once

namespace cfg {
    // Canvas and window sizes
    constexpr float canvas_w = 1024.0f;
    constexpr float canvas_h = 768.0f;

    // Colors (r,g,b)
    constexpr float bg_r = 40.0f, bg_g = 40.0f, bg_b = 50.0f;
    constexpr float accent_green_r = 60.0f, accent_green_g = 196.0f, accent_green_b = 124.0f;
    constexpr float accent_blue_r = 76.0f, accent_blue_g = 161.0f, accent_blue_b = 175.0f;
    constexpr float black_r = 0.0f, black_g = 0.0f, black_b = 0.0f;

    // Forest fire defaults
    constexpr int grid_w = 64;
    constexpr int grid_h = 64;
    constexpr float tree_alive_r = accent_green_r;
    constexpr float tree_alive_g = accent_green_g;
    constexpr float tree_alive_b = accent_green_b;
    constexpr float tree_burning_r = 220.0f;
    constexpr float tree_burning_g = 20.0f;
    constexpr float tree_burning_b = 60.0f;
    // Sliders defaults
    constexpr float default_p_grow = 0.01f;
    constexpr float default_p_lightning = 0.001f;
    constexpr float default_tick_ms = 100.0f;

    // Burning lifetime
    constexpr float burning_lifetime_ms = 500.0f; // 0.5 seconds
}
