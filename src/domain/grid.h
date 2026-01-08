#pragma once

#include <vector>
#include <queue>
#include "utils/random.h"
#include "domain/tree.h"

struct Cell { int x; int y; };

class Grid {
    int w, h;
    std::vector<Tree*> cells; // size w*h
public:
    Grid(int width, int height) : w(width), h(height), cells(width*height, nullptr) {}
    ~Grid() {
        for (auto* t : cells) { delete t; }
    }

    int width() const { return w; }
    int height() const { return h; }
    int index(int x, int y) const { return y * w + x; }
    bool inBounds(int x, int y) const { return x >= 0 && y >= 0 && x < w && y < h; }

    Tree* get(int x, int y) const { return cells[index(x,y)]; }
    void set(int x, int y, Tree* t) { cells[index(x,y)] = t; }
    void clear(int x, int y) { cells[index(x,y)] = nullptr; }

    bool empty(int x, int y) const { return get(x,y) == nullptr; }
    bool occupied(int x, int y) const { return get(x,y) != nullptr; }

    std::vector<Cell> neighbors4(int x, int y) const {
        std::vector<Cell> n;
        if (inBounds(x+1, y)) n.push_back({x+1,y});
        if (inBounds(x-1, y)) n.push_back({x-1,y});
        if (inBounds(x, y+1)) n.push_back({x,y+1});
        if (inBounds(x, y-1)) n.push_back({x,y-1});
        return n;
    }

    bool randomOccupiedCell(Cell& out) const {
        // Collect occupied indices (simple approach)
        std::vector<int> occ;
        occ.reserve(w*h/4);
        for (int i = 0; i < (int)cells.size(); ++i) if (cells[i] != nullptr) occ.push_back(i);
        if (occ.empty()) return false;
        int idx = occ[Random::randInt(0, (int)occ.size()-1)];
        out = { idx % w, idx / w };
        return true;
    }
};
