find_package(GTest REQUIRED)

add_executable(test_importer test_importer.cpp)

target_link_libraries(test_importer
    PRIVATE
    GTest::gtest_main
    storage
)

add_test(NAME test_importer COMMAND test_importer
    WORKING_DIRECTORY $<TARGET_FILE_DIR:test_importer>
)

add_custom_command(
    TARGET test_importer
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/test-data
        $<TARGET_FILE_DIR:test_importer>/test-data
    COMMENT "Copy test data to binary directory"
)