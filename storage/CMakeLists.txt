find_package(spdlog REQUIRED)
find_package(stduuid REQUIRED)

add_library(storage)
target_sources(storage
    PUBLIC
    FILE_SET cxx_modules_public TYPE CXX_MODULES
    FILES
    src/CSVReader.cpp

    PRIVATE
    src/CSVReader_impl.cpp
)

target_link_libraries(storage PRIVATE
    spdlog::spdlog
    stduuid::stduuid
    utils
)

add_subdirectory(test)