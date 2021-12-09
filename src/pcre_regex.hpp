#ifndef PCRE_REGEX_HPP
#define PCRE_REGEX_HPP

#define PCRE2_CODE_UNIT_WIDTH 8
#include <chrono>
#include <pcre2.h>
#include <spdlog/spdlog.h>
#include <string>
#include <vector>
namespace pcre_regex {

int measure(const std::vector<std::string> &chat, const std::string &pat, bool caseSensitive) {
    const auto compStart = std::chrono::high_resolution_clock::now();
    int errornumber;
    PCRE2_SIZE erroroffset;

    PCRE2_SPTR pattern = reinterpret_cast<PCRE2_SPTR>(pat.c_str());
    PCRE2_SPTR subject;

    pcre2_code *re = pcre2_compile(pattern, /* the pattern */
        PCRE2_ZERO_TERMINATED,              /* indicates pattern is zero-terminated */
        caseSensitive ? 0 : PCRE2_CASELESS, /* default options */
        &errornumber,                       /* for error number */
        &erroroffset,                       /* for error offset */
        NULL);                              /* use default compile context */
    if (re == nullptr) {
        PCRE2_UCHAR buffer[256];
        pcre2_get_error_message(errornumber, buffer, sizeof(buffer));
        printf("PCRE2 compilation failed at offset %d: %s\n", static_cast<int>(erroroffset), buffer);
        return -1;
    }

    const auto compEnd = std::chrono::high_resolution_clock::now();
    const auto timeToCompile = (compEnd - compStart);

    const auto matchStart = std::chrono::high_resolution_clock::now();
    int count = 0;
    pcre2_match_data *match_data = pcre2_match_data_create_from_pattern(re, NULL);  // only one needed, so I put it here
    for (const auto &line : chat) {
        subject = reinterpret_cast<PCRE2_SPTR>(line.c_str());
        const auto subject_length = line.size();
        const auto res = pcre2_match(re, /* the compiled pattern */
            subject,                     /* the subject string */
            subject_length,              /* the length of the subject */
            0,                           /* start at offset 0 in the subject */
            0,                           /* default options */
            match_data,                  /* block for storing the result */
            NULL);                       /* use default match context */
        if (res > 0) {
            count++;
        }
    }
    pcre2_match_data_free(match_data); /* Release memory used for the match */
    pcre2_code_free(re);               /* data and the compiled pattern. */

    const auto matchEnd = std::chrono::high_resolution_clock::now();
    const auto timeToMatch = (matchEnd - matchStart);

    spdlog::info("total time = {}ms. time to compile regex = {}us. time to permorm all matches = {}ms. count = {}",
        std::chrono::duration_cast<std::chrono::milliseconds>(timeToMatch + timeToCompile).count(),
        std::chrono::duration_cast<std::chrono::microseconds>(timeToCompile).count(),
        std::chrono::duration_cast<std::chrono::milliseconds>(timeToMatch).count(),
        count);
    return 0;
}



}  // namespace pcre_regex

#endif  // PCRE_REGEX_HPP
