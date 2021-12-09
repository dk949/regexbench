#ifndef CTRE_REGEX_HPP
#define CTRE_REGEX_HPP

#include <string>
#include <vector>
#include <chrono>
#include <ctre.hpp>
#include <spdlog/spdlog.h>


namespace ctre_regex {


template<ctll::fixed_string pattern>
int measure(const std::vector<std::string> &chat, const std::string &, bool ) {
    const auto compStart = std::chrono::high_resolution_clock::now();
    auto matcher = ctre::match<pattern>;
    const auto compEnd = std::chrono::high_resolution_clock::now();
    const auto timeToCompile = (compEnd - compStart);

    const auto matchStart = std::chrono::high_resolution_clock::now();
    int count = 0;
    for (const auto &line : chat) {
        if (matcher(line)) {
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


};  // namespace boost_regex

#endif // CTRE_REGEX_HPP

