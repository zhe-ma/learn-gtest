file(GLOB SRCS
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

set(TARGET_NAME main)

set(LIBS
    base
    "${CMAKE_THREAD_LIBS_INIT}"
    )

add_executable(${TARGET_NAME} ${SRCS})
target_link_libraries(${TARGET_NAME} ${LIBS})
