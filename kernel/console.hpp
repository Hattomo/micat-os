#pragma once

#include "graphics.hpp"

class Console {
  public:
    static const int kRows = 36, kColums = 90;

    Console(PixelWriter &writer, const PixelColor &fg_color,
            const PixelColor &bg_color);
    void PutString(const char *s);

  private:
    void Newline();

    PixelWriter &writer_;
    const PixelColor fg_color_, bg_color_;
    char buffer_[kRows][kColums + 1];
    int cursor_row_, cursor_column_;
    int margin_row_, margin_column_;
};