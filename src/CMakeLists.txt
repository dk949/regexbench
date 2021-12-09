# Generate compile_commands.json to make it easier to work with clang based tools
link_compile_commands()

set(EXE_NAME benchmark)

file(
    GLOB
    SOURCE_FILES
    "${CMAKE_SOURCE_DIR}/src"
    "*.cpp"
)

file(
    GLOB
    HEADER_FILES
    "${CMAKE_SOURCE_DIR}/src"
    "*.hpp"
)

add_executable(${EXE_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(
    ${EXE_NAME} SYSTEM
    PRIVATE ${CONAN_INCLUDE_DIRS_SPDLOG}
            ${CONAN_INCLUDE_DIRS_BOOST}
            ${CONAN_INCLUDE_DIRS_PCRE2}
            ${CONAN_INCLUDE_DIRS_RE2}
            ${CONAN_INCLUDE_DIRS_CTRE}
)
target_link_libraries(
    ${EXE_NAME}
    PRIVATE project_options
            project_warnings
            CONAN_PKG::spdlog
            CONAN_PKG::boost
            CONAN_PKG::pcre2
            CONAN_PKG::re2
            CONAN_PKG::ctre
)
