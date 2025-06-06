#pragma once

#include <fstream>
#include <ctime>
#include <string>

enum class LogLevel {
    Info,
    Error
};

class Logger {
private:
    static std::wofstream logFile;
    static std::wstring levelToString(LogLevel level);
    static std::wstring getTime();

public:
    static void initialize();
    static void log(LogLevel level, const std::wstring& message);
    static void cleanup();
}; 