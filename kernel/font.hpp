#pragma once

#include "graphics.hpp"
#include <cstdint>

void WriteAscii(PixelWriter &writer, int x, int y, char c,
                const PixelColor &color);

void WriteString(PixelWriter &writer, int x, int y, const char *c,
                 const PixelColor &color);
