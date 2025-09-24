cmake_minimum_required (VERSION 3.22)

project (cdroid)

set (CMAKE_C_STANDARD 90)
set (CMAKE_CXX_STANDARD 98)

set (SOURCES
     src/Main.cpp
     src/legacy/activity.c
     src/legacy/linearlayout.c
     src/legacy/main.c
     src/legacy/ptr.c
     src/legacy/pub.c
     src/legacy/state.c
     src/legacy/textview.c
     src/legacy/toast.c
     src/legacy/view.c
     src/legacy/viewhelper.c)

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