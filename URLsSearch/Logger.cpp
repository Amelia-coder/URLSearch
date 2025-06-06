#include "pch.h"
#include "Logger.h"
#include <sstream>
#include <iomanip>

std::wofstream Logger::logFile;

void Logger::initialize() {
    logFile.open(L"url_search.log", std::ios::out | std::ios::app);
}

void Logger::cleanup() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

std::wstring Logger::levelToString(LogLevel level) {
    switch (level) {
        case LogLevel::Info:
            return L"INFO";
        case LogLevel::Error:
            return L"ERROR";
        default:
            return L"UNKNOWN";
    }
}

std::wstring Logger::getTime() {
    auto now = std::time(nullptr);
    struct tm timeinfo;
    localtime_s(&timeinfo, &now);
    std::wstringstream wss;
    wss << std::put_time(&timeinfo, L"%Y-%m-%d %H:%M:%S");
    return wss.str();
}

void Logger::log(LogLevel level, const std::wstring& message) {
    if (!logFile.is_open()) {
        initialize();
    }
    
    logFile << getTime() << L" [" << levelToString(level) << L"] " << message << std::endl;
    logFile.flush();
} 