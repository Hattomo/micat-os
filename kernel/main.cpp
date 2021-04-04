#include "console.hpp"
#include "font.hpp"
#include "frame_buffer_config.hpp"
#include "graphics.hpp"
#include "newlib_support.c"
#include "pci.hpp"
#include <cstddef>
#include <cstdint>
#include <cstdio>

// pixel writer
char pixel_writer_buf[sizeof(RGBResv8BitPerColorPixelWriter)];
PixelWriter *pixel_writer;

// void *operator new(size_t size, void *buf) { return buf; }
void operator delete(void *obj) noexcept {}

// console
char console_buf[sizeof(Console)];
Console *console;

int printk(const char *format, ...) {
    va_list ap;
    int result;
    char s[1024];

    va_start(ap, format);
    result = vsprintf(s, format, ap);
    va_end(ap);

    console->PutString(s);
    return result;
}

// mouse cursor
const int kMouseCursorWidth = 15;
const int kMouseCursorHeight = 24;
const char mouse_cursor_sahpe[kMouseCursorHeight][kMouseCursorWidth + 1] = {
    ".              ", "..             ", ".@.            ", ".@@.           ",
    ".@@@.          ", ".@@@@.         ", ".@@@@@.        ", ".@@@@@@.       ",
    ".@@@@@@@.      ", ".@@@@@@@@.     ", ".@@@@@@@@@.    ", ".@@@@@@@@@@.   ",
    ".@@@@@@@@@@@.  ", ".@@@@@@@@@@@@. ", ".@@@@@@........", ".@@@@@@.       ",
    ".@@@@..@.      ", ".@@@. .@.      ", ".@@.   .@.     ", ".@.    .@.     ",
    "..      .@.    ", ".       .@.    ", "         .@.   ", "         ...   ",
};

// #@@range_begin(call_write_pixel)
extern "C" void KernelMain(const FrameBufferConfig &frame_buffer_config) {
    switch (frame_buffer_config.pixel_format) {
    case kPixelRGBResv8BitPerColor:
        pixel_writer = new (pixel_writer_buf)
            RGBResv8BitPerColorPixelWriter{frame_buffer_config};
        break;
    case kPixelBGRResv8BitPerColor:
        pixel_writer = new (pixel_writer_buf)
            BGRResv8BitPerColorPixelWriter{frame_buffer_config};
        break;
    default:
        break;
    }
    // black screen
    FillReactangle(*pixel_writer, {0, 0},
                   {(int)frame_buffer_config.horizontal_resolution,
                    (int)frame_buffer_config.vertical_resolution},
                   {0, 0, 0});
    console = new (console_buf)
        Console(*pixel_writer, {255, 255, 255}, {45, 118, 237});
    FillReactangle(*pixel_writer, {0, 0},
                   {(int)frame_buffer_config.horizontal_resolution,
                    (int)frame_buffer_config.vertical_resolution},
                   {45, 118, 237});
    FillReactangle(*pixel_writer, {0, 0},
                   {(int)frame_buffer_config.horizontal_resolution, 20},
                   {119, 197, 255});
    // Write A
    int i = 0;
    for (char c = '!'; c <= '~'; ++c, ++i) {
        WriteAscii(*pixel_writer, 8 * i, 50, c, {0, 0, 0});
    }
    WriteString(*pixel_writer, 0, 66, "Hello world!!", {0, 0, 255});
    for (int i = 0; i < 40; ++i) {
        printk("printk%d\n", i);
    }

    for (int dy = 0; dy < kMouseCursorHeight; ++dy) {
        for (int dx = 0; dx < kMouseCursorWidth; ++dx) {
            if (mouse_cursor_sahpe[dy][dx] == '@') {
                pixel_writer->Write(200 + dx, 100 + dy, {0, 0, 0});
            } else if (mouse_cursor_sahpe[dy][dx] == '.') {
                pixel_writer->Write(200 + dx, 100 + dy, {255, 255, 255});
            }
        }
    }

    FillReactangle(*pixel_writer, {50, 50}, {10, 10}, {255, 0, 255});
    DrawReactangle(*pixel_writer, {150, 150}, {150, 150}, {255, 0, 255});
    DrawCircle(*pixel_writer, {250, 250}, 100, {34, 0, 255});

    auto err = pci::ScanAllBus();
    printk("ScanAllBus: %s\n", err.Name());

    for (int i = 0; i < pci::num_device; ++i) {
        const auto &dev = pci::devices[i];
        auto vender_id = pci::ReadVenderId(dev.bus, dev.device, dev.function);
        auto class_code = pci::ReadClassCode(dev.bus, dev.device, dev.function);
        printk("%d.%d.%d: vend %04x, class %08x, head %02x\n", dev.bus,
               dev.device, dev.function, vender_id, class_code,
               dev.header_type);
    }
    while (1) {
        __asm__("hlt");
    }
}
// #@@range_end(call_write_pixel)
