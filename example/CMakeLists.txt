cmake_minimum_required(VERSION 3.22)

project(cdroid_example)

set(SOURCES
    src/main.c)

set (CMAKE_C_STANDARD 90)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wno-unused-function -pedantic")

set(HEADERS)

add_subdirectory(../ ${CMAKE_CURRENT_BINARY_DIR}/cdroid_build)

# we should use cdroid_main target name
# for the API start correctly
add_library(cdroid_main
            SHARED
            ${SOURCES}
            ${HEADERS})

target_include_directories(cdroid_main
                           PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(cdroid_main
                           PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}/../include)

target_link_libraries(cdroid_main
                      cdroid)