#pragma once

#include "graphics.hpp"

class Console {
  public:
    static const int kRows = 35, kColums = 90;

    Console(const PixelColor &writer, const PixelColor &fg_color);
    void PutString(const char *s);
    void SetWriter(PixelWriter *writer);

  private:
    void Newline();
    void Refresh();

    PixelWriter *writer_;
    const PixelColor fg_color_, bg_color_;
    char buffer_[kRows][kColums + 1];
    int cursor_row_, cursor_column_;
    int margin_row_, margin_column_;
};
