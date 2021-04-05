#pragma once

enum LogLevel {
    kError = 3,
    kWarn = 2,
    kInfo = 1,
    kDebug = 0,
};

void SetLogLevel(LogLevel level);

int Log(LogLevel level, const char *format, ...);