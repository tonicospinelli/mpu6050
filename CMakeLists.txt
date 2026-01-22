cmake_minimum_required(VERSION 3.14)

project(mpu6050_driver)

set(CMAKE_CXX_STANDARD 17)

# Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# Arduino/I2C stubs - CREATE THIS FIRST
add_library(arduino_stubs
        tests/stubs/Arduino.cpp
        tests/stubs/I2Cdev.cpp
)
target_include_directories(arduino_stubs PUBLIC tests/stubs)

# Original MPU6050 library
add_library(mpu6050_lib
        src/MPU6050.cpp
)
target_compile_options(mpu6050_lib PRIVATE
        -include cmath
)

# Enable coverage for mpu6050_lib and test
if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "Debug-Coverage" OR NOT CMAKE_BUILD_TYPE)
    target_compile_options(mpu6050_lib PUBLIC --coverage -O0)
    target_link_libraries(mpu6050_lib PUBLIC --coverage)
endif()

target_link_libraries(mpu6050_lib PUBLIC arduino_stubs)
target_include_directories(mpu6050_lib PUBLIC
        tests/stubs      # Our Arduino/I2Cdev stubs (MUST be first)
        src             # MPU6050 headers
)

# Test executable
add_executable(mpu6050_test
        tests/mpu6050_test.cpp
        tests/quaternion_test.cpp
        tests/vector_test.cpp
)

# Link test executable with GoogleTest and your library
target_link_libraries(mpu6050_test
        GTest::gtest_main
        mpu6050_lib
)
#target_include_directories(mpu6050_test PRIVATE src test)

include(GoogleTest)
gtest_discover_tests(mpu6050_test)
