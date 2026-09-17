
cmake_minimum_required(VERSION 3.5)

project( stateengine )

set (CMAKE_C_STANDARD 11 )
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY bin/ )
set (CMAKE_BUILD_TYPE Debug )

include_directories( tests.out PRIVATE Unity )
include_directories( tests.out PRIVATE Unity/src )
include_directories( tests.out PRIVATE src )

add_executable( tests.out
                src/event_heap.c
                src/fifo_base.c
                src/state.c
                src/state_history.c
                src/emitter_base.c
                src/event_observer.c
                src/pq_base.c
                src/base64.c
                tests/base64_tests.c
                tests/pq_tests.c
                tests/fifo_tests.c
                tests/state_tests.c
                tests/heap_tests.c
                tests/tests.c
                tests/emitter_tests.c
                tests/scenario_tests.c
                tests/event_observer_tests.c
                tests/util_tests.c
                tests/tests_bp.c
                Unity/src/unity.c
                Unity/src/unity.h
                Unity/src/unity_internals.h ) 


target_compile_options( tests.out
                        PUBLIC
                        -Wfatal-errors
                        #-Wall
                        #-Wextra
                        -Werror
                        #-Wpedantic
                        #-Wpointer-arith
                        -g
                        -DUNIT_TESTS
                        -DUNITY_OUTPUT_COLOR )
