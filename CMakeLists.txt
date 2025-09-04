cmake_minimum_required(VERSION 3.22)

project(cdroid)

set(SOURCES
    src/main.c
    src/state.c)

set(HEADERS)

add_library(cdroid
            SHARED
            ${SOURCES}
            ${HEADERS})

target_include_directories(cdroid
                           PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_library(log-lib log)
target_link_libraries(cdroid
                      ${log-lib})