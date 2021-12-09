#ifndef STD_REGEX_HPP
#define STD_REGEX_HPP
#include <chrono>
#include <regex>
#include <spdlog/spdlog.h>
#include <string>
#include <vector>


namespace std_regex {

int measure(const std::vector<std::string> &chat, const std::string &pattern, bool caseSensitive) {
    const auto compStart = std::chrono::high_resolution_clock::now();
    const std::regex re {pattern,
        static_cast<std::regex_constants::syntax_option_type>(
            caseSensitive ? static_cast<unsigned int>(std::regex_constants::basic) :
                            static_cast<unsigned int>(std::regex_constants::basic | std::regex_constants::icase))};
    const auto compEnd = std::chrono::high_resolution_clock::now();
    const auto timeToCompile = (compEnd - compStart);

    const auto matchStart = std::chrono::high_resolution_clock::now();
    int count = 0;
    for (const auto &line : chat) {
        if (std::regex_match(line, re)) {
            count++;
        }
    }
    const auto matchEnd = std::chrono::high_resolution_clock::now();
    const auto timeToMatch = (matchEnd - matchStart);

    spdlog::info("total time = {}ms. time to compile regex = {}us. time to permorm all matches = {}ms. count = {}",
        std::chrono::duration_cast<std::chrono::milliseconds>(timeToMatch + timeToCompile).count(),
        std::chrono::duration_cast<std::chrono::microseconds>(timeToCompile).count(),
        std::chrono::duration_cast<std::chrono::milliseconds>(timeToMatch).count(),
        count);
    return 0;
}


};  // namespace std_regex

#endif  // STD_REGEX_HPP
