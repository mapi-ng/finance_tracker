add_executable(finance_tracker src/main.cpp)

find_package(spdlog REQUIRED)

target_link_libraries(finance_tracker PRIVATE 
    spdlog::spdlog
)
target_include_directories(finance_tracker PRIVATE include)

add_subdirectory(test)