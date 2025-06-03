find_package(spdlog REQUIRED)
find_package(stduuid REQUIRED)

add_library(storage)
target_sources(storage
    PUBLIC
    FILE_SET cxx_modules_public TYPE CXX_MODULES
    FILES
    src/Importer.cpp
    src/CSVImporter.cpp

    PRIVATE
    src/CSVImporter_impl.cpp
)

target_link_libraries(storage PRIVATE
    spdlog::spdlog
    stduuid::stduuid
    utils
    core
)

add_subdirectory(test)