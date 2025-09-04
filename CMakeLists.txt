cmake_minimum_required (VERSION 3.22)

project (cdroid)

set (CMAKE_C_STANDARD 90)

set (SOURCES
     src/activity.c
     src/linearlayout.c
     src/main.c
     src/ptr.c
     src/pub.c
     src/state.c
     src/textview.c
     src/view.c
     src/viewhelper.c)

set( HEADERS)

add_library (cdroid
             SHARED
             ${SOURCES}
             ${HEADERS})

target_include_directories (cdroid
                            PUBLIC
                            ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_library (log-lib log)
target_link_libraries (cdroid
                       ${log-lib})