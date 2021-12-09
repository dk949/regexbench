#include "boost_regex.hpp"
#include "ctre_regex.hpp"
#include "pcre_regex.hpp"
#include "re2_regex.hpp"
#include "std_regex.hpp"

#include <fstream>
#include <iostream>
#include <vector>

#define RUN(NAMESPACE, FUNC)                                       \
    if (NAMESPACE::FUNC) {                                         \
        std::cerr << "test failed for " #NAMESPACE ", aborting\n"; \
        return -1;                                                 \
    }

#define RUN_TEST(NAMESPACE)                              \
    std::cout << #NAMESPACE << '\n';                     \
    RUN(NAMESPACE, measure(chat, ".*pog.*", true))       \
    RUN(NAMESPACE, measure(chat, ".*pog.*", false))      \
    RUN(NAMESPACE, measure(chat, R"(.*poo*g.*)", true))  \
    RUN(NAMESPACE, measure(chat, R"(.*poo*g.*)", false)) \
    RUN(NAMESPACE, measure(chat, R"([0-9]*,[^ ]*,[^ ]* subscribed at Tier [123]\..*$)", true))

#define RUN_TEST_CTRE(NAMESPACE)                            \
    std::cout << #NAMESPACE << '\n';                        \
    RUN(NAMESPACE, measure<".*pog.*">(chat, "", true))      \
    std::cout << "N/A\n";                                   \
    RUN(NAMESPACE, measure<R"(.*poo*g.*)">(chat, "", true)) \
    std::cout << "N/A\n";                                   \
    RUN(NAMESPACE, measure<R"([0-9]*,[^ ]*,[^ ]* subscribed at Tier [123]\..*$)">(chat, "", true))

int main(int argc, const char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: benchmark [FILE]\n";
        return 1;
    }


    spdlog::set_pattern("%^[%l]%$: %v");

    std::ifstream chat_data(argv[1]);

    std::vector<std::string> chat;

    std::string temp_line;
    if (!chat_data.good()) {
        std::cerr << "could not open file " << argv[1] << '\n';
    }

    while (getline(chat_data, temp_line)) {
        chat.push_back(temp_line);
    }
    if (chat.empty()) {
        std::cerr << "no \n";
        return -1;
    }

    RUN_TEST(boost_regex);
    RUN_TEST(std_regex);
    RUN_TEST(pcre_regex);
    RUN_TEST(re2_regex);
    RUN_TEST_CTRE(ctre_regex);


    return 0;
}
