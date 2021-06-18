cmake_minimum_required(VERSION 3.1.0)

if(POLICY CMP0074)
    # find_package() uses <PackageName>_ROOT variables.
    # This policy was introduced in CMake version 3.12.
    cmake_policy(SET CMP0074 NEW)
endif()

project(LearnGTest)

option(ENABLE_UT "Enable Unit Test" ON)
if(ENABLE_UT)
    add_definitions(-DENABLE_UT)
endif()


# C++ standard requirements.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# CMake 3.1.0+ required.
# See: https://stackoverflow.com/a/29871891
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

enable_testing()

set(THIRD_PARTY_DIR ${PROJECT_SOURCE_DIR}/third_party)

include_directories(
    ${PROJECT_SOURCE_DIR}/src
    # ${PROJECT_BINARY_DIR}/src
    include_directories(${THIRD_PARTY_DIR}/googletest)
    include_directories(${THIRD_PARTY_DIR}/googletest/include)
    include_directories(${THIRD_PARTY_DIR}/googlemock)
    include_directories(${THIRD_PARTY_DIR}/googlemock/include)
    )

add_subdirectory(${THIRD_PARTY_DIR}/googletest)
add_subdirectory(${THIRD_PARTY_DIR}/googlemock)

add_subdirectory(src/base)
add_subdirectory(src/app)
add_subdirectory(src/system1)
add_subdirectory(src/system2)
add_subdirectory(src/unittest)
