find_package(GTest REQUIRED)

add_executable(test_transaction test_transaction.cpp)

target_link_libraries(test_transaction
    PRIVATE
    GTest::gtest_main
    core
)

add_test(NAME test_transaction COMMAND test_transaction)

add_executable(test_transactionmapper test_transactionmapper.cpp)

target_link_libraries(test_transactionmapper
    PRIVATE
    GTest::gtest_main
    core
    storage
)

add_test(NAME test_transactionmapper COMMAND test_transactionmapper
    WORKING_DIRECTORY $<TARGET_FILE_DIR:test_transactionmapper>
)

add_custom_command(
    TARGET test_transactionmapper
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
    ${CMAKE_SOURCE_DIR}/test-data
    $<TARGET_FILE_DIR:test_transactionmapper>/test-data
    COMMENT "test_transactionmapper: Copy test data to binary directory"
)