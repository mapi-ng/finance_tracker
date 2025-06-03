find_package(GTest REQUIRED)

add_executable(test_storage test_storage.cpp)

target_link_libraries(test_storage
    PRIVATE
    GTest::gtest_main
    storage
)

add_test(NAME test_storage COMMAND test_storage)