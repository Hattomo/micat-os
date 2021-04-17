#pragma once

enum LogLevel {
    kError = 10,
    kWarn = 20,
    kInfo = 30,
    kDebug = 40,
};

void SetLogLevel(LogLevel level);

int Log(LogLevel level, const char *format, ...);