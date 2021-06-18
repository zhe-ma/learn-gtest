# Unit test

set(UT_TARGET_NAME unittest)

file(GLOB UT_SRCS
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    )


# Common libraries to link.
set(UT_LIBS
    gtest
    gmock
    base
    system1
    system2
    )

# if(UNIX)
#     # Add `-ldl` for Linux to avoid "undefined reference to `dlopen'".
#     set(UT_LIBS ${UT_LIBS} ${CMAKE_DL_LIBS})
# endif()

add_executable(${UT_TARGET_NAME} ${UT_SRCS})
target_link_libraries(${UT_TARGET_NAME} ${UT_LIBS})
set_target_properties(${UT_TARGET_NAME} PROPERTIES FOLDER "Tests")

add_test(${UT_TARGET_NAME} ${UT_TARGET_NAME})
