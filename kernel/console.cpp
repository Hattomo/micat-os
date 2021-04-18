#include "console.hpp"
#include "font.hpp"
#include "layer.hpp"
#include <cstring>

Console::Console(const PixelColor &fg_color, const PixelColor &bg_color)
    : writer_{nullptr}, fg_color_{fg_color}, bg_color_{bg_color}, buffer_{},
      cursor_row_{0}, cursor_column_{0}, margin_row_{28}, margin_column_{8} {}

void Console::PutString(const char *s) {
    while (*s) {
        if (*s == '\n') {
            Newline();
        } else if (cursor_column_ < kColums - 1) {
            WriteAscii(*writer_, (8 * cursor_column_) + margin_column_,
                       (16 * cursor_row_) + margin_row_, *s, fg_color_);
            buffer_[cursor_row_][cursor_column_] = *s;
            ++cursor_column_;
        }
        ++s;
    }
    if (layer_manager) {
        layer_manager->Draw();
    }
}

void Console::SetWriter(PixelWriter *writer) {
    if (writer == writer_) {
        return;
    }
    writer_ = writer;
    Refresh();
}

void Console::Newline() {
    cursor_column_ = 0;
    if (cursor_row_ < kRows - 1) {
        ++cursor_row_;
    } else {
        for (int y = 0; y < 16 * kRows; ++y) {
            for (int x = 0; x < 8 * kColums; ++x) {
                writer_->Write(x + margin_column_, y + margin_row_, bg_color_);
            }
        }
        for (int row = 0; row < kRows - 1; ++row) {
            memcpy(buffer_[row], buffer_[row + 1], kColums + 1);
            WriteString(*writer_, margin_column_, (16 * row) + margin_row_,
                        buffer_[row], fg_color_);
        }
        memset(buffer_[kRows - 1], 0, kColums + 1);
    }
}

void Console::Refresh() {
    for (int row = 0; row < kRows; ++row) {
        WriteString(*writer_, margin_column_, (16 * row) + margin_row_,
                    buffer_[row], fg_color_);
    }
}