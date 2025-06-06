#pragma once

#include <string>
#include <vector>
#include <regex>
#include <map>

struct URLOccurrence {
    std::wstring filePath;
    std::wstring match;
    int line;
    int column;
};

class URLSearcher {
public:
    std::map<std::wstring, std::vector<URLOccurrence>> searchURLs(const std::vector<std::wstring>& files);

private:
    const std::wregex urlPattern{ 
        L"(http|ftp|gopher|news|telnet|file)://[\\w\\-]+(\\.[\\w\\-]+)+([\\w\\-.,@?^=%&:/~+#]*[\\w\\-@?^=%&/~+#])?" 
    };

    std::vector<URLOccurrence> searchInFile(const std::wstring& filePath);
}; 