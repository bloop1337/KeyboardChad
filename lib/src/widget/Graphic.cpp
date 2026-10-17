#include "Window.hpp"
#include <algorithm>
#include "Graphic.hpp"

namespace tui {
    void Graphic::render(Window& w, int& x, int& y) {
        int height = w.getHeight()-1;
        int width = params.size();
        
        for (int row = 0; row < width; row++) {
            int value = std::min(params.at(row), height);
            int _y = height;
            for (int _ = 0; _ < value; _++) {
                w.pixelAt(row, _y).style.mode = Pixel_Graphic_Mode::INVERSE;
                _y--;
            }
        }

    }

    int Graphic::getWidth() { return 0; }
    int Graphic::getHeight() { return 0; }
}
