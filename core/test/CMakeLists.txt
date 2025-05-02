find_package(GTest REQUIRED)

add_executable(test_transaction test_transaction.cpp)

target_link_libraries(test_transaction
    PRIVATE
    GTest::gtest_main
    core
)

add_test(NAME test_transaction COMMAND test_transaction)