find_package(stduuid REQUIRED)

add_library(utils)
target_sources(utils
PUBLIC
    FILE_SET cxx_modules_public TYPE CXX_MODULES
    FILES src/uuid_utils.cppm
)

target_link_libraries(utils PRIVATE
    stduuid::stduuid
)

add_subdirectory(test)