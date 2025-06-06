#include "pch.h"
#include "URLSearcher.h"
#include "Logger.h"
#include <fstream>
#include <sstream>

std::map<std::wstring, std::vector<URLOccurrence>> URLSearcher::searchURLs(const std::vector<std::wstring>& files) {
    std::map<std::wstring, std::vector<URLOccurrence>> results;
    
    for (const auto& file : files) {
        try {
            auto fileResults = searchInFile(file);
            for (const auto& occurrence : fileResults) {
                std::wstring url(occurrence.match);
                results[url].push_back(occurrence);
            }
            Logger::log(LogLevel::Info, L"Successfully processed file: " + file);
        }
        catch (const std::exception& e) {
            std::wstringstream ss;
            ss << L"Error processing file " << file << L": " << e.what();
            Logger::log(LogLevel::Error, ss.str());
        }
    }
    
    return results;
}

std::vector<URLOccurrence> URLSearcher::searchInFile(const std::wstring& filePath) {
    std::vector<URLOccurrence> occurrences;
    std::wifstream file(filePath);
    
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file");
    }
    
    std::wstring line;
    int lineNumber = 0;
    
    while (std::getline(file, line)) {
        lineNumber++;
        
        std::wsregex_iterator it(line.begin(), line.end(), urlPattern);
        std::wsregex_iterator end;
        
        while (it != end) {
            URLOccurrence occurrence;
            occurrence.filePath = filePath;
            occurrence.line = lineNumber;
            occurrence.column = static_cast<int>(it->position() + 1);
            occurrence.match = it->str();
            occurrences.push_back(occurrence);
            ++it;
        }
    }
    
    return occurrences;
} 