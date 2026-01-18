#include "ui/log_log_plot.h"
#include "global_state.h"
#include "config.h"
#include "graphics.h"
#include <cmath>

void LogLogPlot::update(GlobalState& /*gs*/){
    // Static plot: nothing to update for now
}

void LogLogPlot::draw(GlobalState& gs){
    float plotCx = centerX();
    float plotCy = centerY();
    float plotW = width();
    float plotH = height();

    graphics::Brush br;
    br.outline_opacity = 0.0f;
    // Frame
    br.fill_color[0] = 0.05f; br.fill_color[1] = 0.05f; br.fill_color[2] = 0.05f;
    graphics::drawRect(plotCx, plotCy, plotW + 6.0f, plotH + 6.0f, br);
    br.fill_color[0] = 0.12f; br.fill_color[1] = 0.12f; br.fill_color[2] = 0.12f;
    graphics::drawRect(plotCx, plotCy, plotW, plotH, br);

    // Axes lines
    br.outline_opacity = 0.0f;
    br.fill_color[0] = 0.8f; br.fill_color[1] = 0.8f; br.fill_color[2] = 0.8f;
    float left = plotCx - plotW*0.5f;
    float right = plotCx + plotW*0.5f;
    float bottom = plotCy + plotH*0.5f;
    float top = plotCy - plotH*0.5f;
    graphics::drawLine(left, bottom, right, bottom, br); // X axis
    graphics::drawLine(left, bottom, left, top, br);     // Y axis

    // Title
    graphics::drawText(plotCx - plotW*0.48f, top - 30.0f, 15.0f, "Log Log Plot of Fire Size Distribution", br);
    graphics::drawText(plotCx - plotW*0.48f, top - 10.0f, 15.0f, "X: Fire size (log2 bins) / Y: Frequency (log10)", br);

    if (data.empty()){
        graphics::drawText(plotCx - plotW*0.2f, plotCy, 12.0f, "No data yet", br);
        return;
    }

    // Build log2 bins and normalized frequencies
    int total = (int)data.size();
    int maxBin = 0;
    std::vector<int> binCounts;
    binCounts.reserve(32);
    for (int s : data){
        if (s < 1) continue;
        int b = (int)std::floor(std::log2((double)s));
        if (b > maxBin) maxBin = b;
        if (b >= (int)binCounts.size()){
            binCounts.resize(b+1, 0);
        }
        binCounts[b] += 1;
    }
    if (binCounts.empty()){
        graphics::drawText(plotCx - plotW*0.2f, plotCy, 12.0f, "Insufficient data", br);
        return;
    }

    std::vector<float> normCounts(binCounts.size(), 0.0f);
    float maxNorm = 0.0f;
    for (int b = 0; b < (int)binCounts.size(); ++b){
        int sMin = (int)std::pow(2, b);
        int sMax = (int)std::pow(2, b+1) - 1;
        int binWidth = sMax - sMin + 1;
        float val = 0.0f;
        if (total > 0 && binWidth > 0){
            val = (float)binCounts[b] / (float)total / (float)binWidth;
        }
        normCounts[b] = val;
        if (val > maxNorm) maxNorm = val;
    }
    if (maxNorm <= 0.0f){
        graphics::drawText(plotCx - plotW*0.2f, plotCy, 12.0f, "No positive frequencies", br);
        return;
    }

    // Plot points: X uses bin index (approx log2 center), Y uses log10(normalized)
    graphics::Brush pt;
    pt.fill_color[0] = 0.2f; pt.fill_color[1] = 0.8f; pt.fill_color[2] = 0.3f;
    pt.outline_opacity = 0.0f;

    // Determine Y scaling from log10 range
    float maxLogY = -INFINITY;
    float minLogY = INFINITY;
    for (float v : normCounts){
        if (v > 0.0f){
            float lv = std::log10(v);
            if (lv > maxLogY) maxLogY = lv;
            if (lv < minLogY) minLogY = lv;
        }
    }
    if (!std::isfinite(maxLogY) || !std::isfinite(minLogY)){
        graphics::drawText(plotCx - plotW*0.2f, plotCy, 12.0f, "No plottable points", br);
        return;
    }

    auto xForBin = [&](int b){
        float t = (float)(b + 0.5f) / (float)(maxBin + 1); // normalized 0..1
        return left + t * (right - left);
    };
    auto yForVal = [&](float v){
        float lv = std::log10(v);
        float t = (lv - minLogY) / (maxLogY - minLogY);
        return bottom - t * (bottom - top);
    };

    // Draw the points and a thin line through them
    float prevX = NAN, prevY = NAN;
    for (int b = 0; b <= maxBin; ++b){
        float v = (b < (int)normCounts.size() ? normCounts[b] : 0.0f);
        if (v <= 0.0f) continue;
        float px = xForBin(b);
        float py = yForVal(v);
        graphics::drawDisk(px, py, 2.5f, pt);
        if (std::isfinite(prevX)){
            graphics::drawLine(prevX, prevY, px, py, pt);
        }
        prevX = px; prevY = py;
    }
}
