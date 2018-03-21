cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(euler
    LANGUAGES CXX
    DESCRIPTION "Project euler problems"
)

find_package(Boost 1.65.1 COMPONENTS program_options REQUIRED)

add_executable(euler
    # src/
        src/Main.cpp
        # 1-100
            src/1-100/Problem01.cpp
            src/1-100/Problem01-Lazy.cpp
            src/1-100/Problem02.cpp
            src/1-100/Problem02-Lazy.cpp
            src/1-100/Problem03.cpp
            src/1-100/Problem04.cpp
            src/1-100/Problem05.cpp
            src/1-100/Problem06.cpp
            src/1-100/Problem07.cpp
            src/1-100/Problem08.cpp
            src/1-100/Problem09.cpp
            src/1-100/Problem10.cpp
            src/1-100/Problem11.cpp
            src/1-100/Problem12.cpp
            src/1-100/Problem13.cpp
            src/1-100/Problem14.cpp
            src/1-100/Problem15.cpp
            src/1-100/Problem16.cpp
            src/1-100/Problem17.cpp
)

set_target_properties(euler
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        RUNTIME_OUTPUT_DIRECTORY bin
)

target_compile_features(euler
    PUBLIC
        cxx_std_17
)

target_include_directories(euler
    PUBLIC
        include
        ${Boost_INCLUDE_DIR}
)

target_compile_options(euler
    PUBLIC
        -Wall
        -Wextra
        -O2
)

target_link_libraries(euler
    PUBLIC
        ${Boost_LIBRARIES}
)
