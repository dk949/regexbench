#ifndef BOOST_REGEX_HPP
#define BOOST_REGEX_HPP
#include <string>
#include <vector>
#include <chrono>
#include <boost/regex.hpp>
#include <spdlog/spdlog.h>

    const auto start = std::chrono::high_resolution_clock::now();

    const auto end = std::chrono::high_resolution_clock::now();
    const auto time = (end - start);

namespace boost_regex {

int measure(const std::vector<std::string> &chat, const std::string &pattern, bool caseSensitive) {
    const auto compStart = std::chrono::high_resolution_clock::now();
    const boost::regex re {pattern,
        caseSensitive ? static_cast<unsigned int>(boost::regex::basic) :
                        static_cast<unsigned int>(boost::regex::basic | boost::regex::icase)};
    const auto compEnd = std::chrono::high_resolution_clock::now();
    const auto timeToCompile = (compEnd - compStart);

    const auto matchStart = std::chrono::high_resolution_clock::now();
    int count = 0;
    for (const auto &line : chat) {
        if (boost::regex_match(line, re)) {
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

#endif  // BOOST_REGEX_HPP
