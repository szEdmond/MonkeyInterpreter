set(TEST_DIR "${CMAKE_SOURCE_DIR}/tests")

file(GLOB_RECURSE TEST_FILES
    "${TEST_DIR}/*.h"
    "${TEST_DIR}/*.hpp"
    "${TEST_DIR}/*.c"
    "${TEST_DIR}/*.cpp"
)

add_executable(Unit_Tests ${TEST_FILES})
target_link_libraries(Unit_Tests InterpreterLib)