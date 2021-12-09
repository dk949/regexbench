#ifndef RE2_REGEX_HPP
#define RE2_REGEX_HPP

#include <string>
#include <vector>
#include <chrono>
#include <boost/regex.hpp>
#include <re2/re2.h>
#include <spdlog/spdlog.h>


namespace re2_regex {

int measure(const std::vector<std::string> &chat, const std::string &pattern, bool caseSensitive) {
    const auto compStart = std::chrono::high_resolution_clock::now();
    re2::RE2::Options opts;
    opts.set_case_sensitive(caseSensitive);
    RE2 re {pattern, opts};
    const auto compEnd = std::chrono::high_resolution_clock::now();
    const auto timeToCompile = (compEnd - compStart);

    const auto matchStart = std::chrono::high_resolution_clock::now();
    int count = 0;
    for (const auto &line : chat) {
        if (re2::RE2::FullMatch(line, re)) {
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
#endif // RE2_REGEX_HPP


