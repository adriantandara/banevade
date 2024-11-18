#include "GetLastLine.h"
#include <filesystem>
#include <fstream>
#include <regex>
#include <deque>
#include <thread>
#include <chrono>
#include <sstream>

#include "tools/common/Notify.h"
#include "tools/common/Webhook.h"

namespace fs = std::filesystem;

string cleanLine(const string& line) {
    regex timestampRegex("^\\[[0-9]{2}:[0-9]{2}:[0-9]{2}\\]");
    regex nameRegex("<(.*?)>");

    // Înlătură timestamp-ul și numele, apoi curăță spațiile
    string cleanedLine = regex_replace(line, timestampRegex, "");
    cleanedLine = regex_replace(cleanedLine, nameRegex, "$1");
    cleanedLine = regex_replace(cleanedLine, regex("^\\s+"), "");
    cleanedLine = regex_replace(cleanedLine, regex("\\s+$"), "");

    return cleanedLine;
}

string getLastLine(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) return "";

    string line;
    deque<string> lines;

    while (getline(file, line)) {
        lines.push_back(line);
        if (lines.size() > 1) {
            lines.pop_front();
        }
    }

    file.close();
    return lines.empty() ? "" : cleanLine(lines.back());
}

void monitorLogFile(CChat* playerChat) {
    if (playerChat == nullptr) return;

    fs::path logFilePath(playerChat->m_szLogPath);

    if (!fs::exists(logFilePath) || !fs::is_regular_file(logFilePath)) return;

    auto lastWriteTime = fs::last_write_time(logFilePath);

    regex pmFromRegex("PM FROM", regex_constants::icase);

    while (playerChat != nullptr) {
        auto currentWriteTime = fs::last_write_time(logFilePath);

        if (currentWriteTime != lastWriteTime) {
            lastWriteTime = currentWriteTime;

            auto logContent = getLastLine(playerChat->m_szLogPath);

            std::smatch match;
            auto begin = logContent.cbegin();
            while (std::regex_search(begin, logContent.cend(), match, pmFromRegex)) {
                playerChat->AddMessage(0x008080FF, "Ban Evade: {f9f9f9}Detected");
                SendDiscord("1307472949959462962", "XDavvQQPdO3-nFX2dsvZpPJd28qio2bxXL6Mfb-cKRaZrC8xVldDyj4aMVumyz8TS6R8", "Ban Evade", logContent);
                begin = match.suffix().first;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}
