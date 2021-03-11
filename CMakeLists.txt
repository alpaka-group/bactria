cmake_minimum_required(VERSION 3.18)

project("bactria" VERSION 0.0.1
                  DESCRIPTION "Broadly Applicable C++ Tracing and Instrumentation API"
                  LANGUAGES CXX)

###############################################################################
# Options and variants
###############################################################################

option(bactria_BUILD_DOCUMENTATION "Generate the documentation" ON)
option(bactria_BUILD_EXAMPLES "Build examples" ON)

###############################################################################
# Internal variables
###############################################################################

# This file's directory
set(_BACTRIA_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})
# Normalize the path (Remove ../)
get_filename_component(_BACTRIA_ROOT_DIR ${_BACTRIA_ROOT_DIR} ABSOLUTE)

# Add module search path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${_BACTRIA_ROOT_DIR}/cmake/modules)

add_library(bactria INTERFACE)
target_include_directories(bactria INTERFACE include)
target_compile_features(bactria INTERFACE cxx_std_17)
target_compile_options(bactria INTERFACE $<$<CXX_COMPILER_ID:GNU>:-Wno-attributes>)
target_link_libraries(bactria INTERFACE $<$<NOT:$<PLATFORM_ID:Windows>>:${CMAKE_DL_LIBS}>)

add_subdirectory("src")

if(bactria_BUILD_DOCUMENTATION)
    add_subdirectory("docs")
endif()

if(bactria_BUILD_EXAMPLES)
    add_subdirectory("examples")
endif()
