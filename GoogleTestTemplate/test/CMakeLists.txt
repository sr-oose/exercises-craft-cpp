set(TEST_NAME runTests)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(${TEST_NAME} testsuite.cpp)
target_link_libraries(${TEST_NAME} src ${GTEST_LIBRARIES} pthread)

add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
