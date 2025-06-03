find_package(GTest REQUIRED)

add_executable(test_csvreader test_csvreader.cpp)

target_link_libraries(test_csvreader
    PRIVATE
    GTest::gtest_main
    storage
)

add_test(NAME test_csvreader COMMAND test_csvreader
    WORKING_DIRECTORY $<TARGET_FILE_DIR:test_csvreader>
)

add_custom_command(
    TARGET test_csvreader
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
    ${CMAKE_SOURCE_DIR}/test-data
    $<TARGET_FILE_DIR:test_csvreader>/test-data
    COMMENT "test_csvreader: Copy test data to binary directory"
)
