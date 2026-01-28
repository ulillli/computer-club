cmake_minimum_required(VERSION 3.10)
project(computer_club)

set(CMAKE_CXX_STANDARD 11)  # Google Test требует C++11 или выше
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Основная программа
add_executable(computer_club samples/main.cpp)
target_include_directories(computer_club PRIVATE include)

# 2. Google Test (сначала)
add_subdirectory(gtest)

# 3. Тесты
add_executable(run_tests
    test/test_main.cpp
    test/test_cases.cpp
)
target_include_directories(run_tests 
    PRIVATE 
    include
    ${CMAKE_CURRENT_SOURCE_DIR}/gtest
)
target_link_libraries(run_tests gtest)



# 5. Информация
message(STATUS "======================================")
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Targets:")
message(STATUS "  computer_club - main program")
message(STATUS "  run_tests - Google Test runner")
message(STATUS "======================================")