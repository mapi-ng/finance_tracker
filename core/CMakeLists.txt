find_package(spdlog REQUIRED)

add_library(core)
target_sources(core PUBLIC
    FILE_SET CXX_MODULES
    FILES src/Transaction.ixx
)

target_link_libraries(core PRIVATE 
    spdlog::spdlog
)

add_executable(finance_tracker src/main.cpp)

target_link_libraries(finance_tracker PRIVATE
    core
    spdlog::spdlog
)

add_subdirectory(test)