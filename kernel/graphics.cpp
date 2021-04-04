#include "graphics.hpp"

// writer
void RGBResv8BitPerColorPixelWriter::Write(int x, int y, const PixelColor &c) {
    auto p = PixelAt(x, y);
    p[0] = c.r;
    p[1] = c.g;
    p[2] = c.b;
}

void BGRResv8BitPerColorPixelWriter::Write(int x, int y, const PixelColor &c) {
    auto p = PixelAt(x, y);
    p[0] = c.b;
    p[1] = c.g;
    p[2] = c.r;
}

// reactangle
void FillReactangle(PixelWriter &writer, const Vector2D<int> &pos,
                    const Vector2D<int> &size, const PixelColor &c) {
    for (int dy = 0; dy < size.y; ++dy) {
        for (int dx = 0; dx < size.x; ++dx) {
            writer.Write(pos.x + dx, pos.y + dy, c);
        }
    }
}

// reactangle(line only)
void DrawReactangle(PixelWriter &writer, const Vector2D<int> &pos,
                    const Vector2D<int> &size, const PixelColor &c) {
    for (int dx = 0; dx < size.x; ++dx) {
        writer.Write(pos.x + dx, pos.y, c);
        writer.Write(pos.x + dx, pos.y + size.y - 1, c);
    }
    for (int dy = 1; dy < size.y - 1; ++dy) {
        writer.Write(pos.x, pos.y + dy, c);
        writer.Write(pos.x + size.x - 1, pos.y + dy, c);
    }
}

// Draw Circle
void DrawCircle(PixelWriter &writer, const Vector2D<int> &pos,
                const int &size, const PixelColor &c){
    for (int dy = -size; dy < 2*size;++dy){
        for (int dx = -size; dx < 2*size; ++dx){
            if (((dx * dx) + (dy * dy)) < size * size) {
                writer.Write(pos.x + dx, pos.y + dy,c);
            }
        }
    }
}