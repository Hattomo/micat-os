#include "font.hpp"
#include "frame_buffer_config.hpp"
#include "graphics.hpp"
#include <cstddef>
#include <cstdint>

char pixel_writer_buf[sizeof(RGBResv8BitPerColorPixelWriter)];
PixelWriter *pixel_writer;

void *operator new(size_t size, void *buf) { return buf; }
void operator delete(void *obj) noexcept {}

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

    for (int x = 0; x < frame_buffer_config.horizontal_resolution; ++x) {
        for (int y = 0; y < frame_buffer_config.vertical_resolution; ++y) {
            pixel_writer->Write(x, y,
                                {(uint8_t)(y * x % 255), (uint8_t)(y * x % 255),
                                 (uint8_t)(y * x % 255)});
        }
    }
    for (int x = 0; x < 200; ++x) {
        for (int y = 0; y < 100; ++y) {
            pixel_writer->Write(x, y, {0, 255, 0});
        }
    }
    // Write A
    WriteAscii(*pixel_writer, 50, 50, 'A', {0, 0, 0});
    WriteAscii(*pixel_writer, 58, 50, 'A', {0, 0, 0});

    while (1) {
        __asm__("hlt");
    }
}
// #@@range_end(call_write_pixel)
