find_package(spdlog REQUIRED)
find_package(stduuid REQUIRED)

add_library(core)
target_sources(core
    PUBLIC
    FILE_SET cxx_modules_public TYPE CXX_MODULES
    FILES src/Transaction.cpp src/TransactionBuilder.cpp
)

target_link_libraries(core PRIVATE
    spdlog::spdlog
    stduuid::stduuid
    storage
    utils
)

add_executable(finance_tracker src/main.cpp)

target_link_libraries(finance_tracker PRIVATE
    core
    spdlog::spdlog
)

add_subdirectory(test)