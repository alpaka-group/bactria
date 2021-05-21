cmake_minimum_required(VERSION 3.18)

project("bactria" VERSION 0.0.1
                  DESCRIPTION "Broadly Applicable C++ Tracing and Instrumentation API"
                  LANGUAGES CXX)

include(GNUInstallDirs)

###############################################################################
# Options and variants
###############################################################################

option(bactria_BUILD_DOCUMENTATION "Generate the documentation" ON)
option(bactria_BUILD_EXAMPLES "Build examples" ON)

option(bactria_STDOUT_BACKENDS "Build the STDOUT backends" ON)
option(bactria_SYSTEM_FMT "Use your local installation of {fmt}" ON)
option(bactria_JSON_BACKENDS "Build the JSON backends" ON)
option(bactria_SYSTEM_JSON "Use your local installation of nlohmann-json" ON)
option(bactria_SCOREP_BACKEND "Build the Score-P metrics backend" OFF)

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
target_compile_features(bactria INTERFACE cxx_std_14)
target_compile_options(bactria INTERFACE $<$<CXX_COMPILER_ID:GNU>:-Wno-attributes>)
target_link_libraries(bactria INTERFACE $<$<NOT:$<PLATFORM_ID:Windows>>:${CMAKE_DL_LIBS}>)

if(bactria_BUILD_DOCUMENTATION)
    add_subdirectory("docs")
endif()

if(bactria_BUILD_EXAMPLES)
    add_subdirectory("examples")
endif()

include(FetchContent)

if(bactria_JSON_BACKENDS)
    if(bactria_SYSTEM_JSON)
        find_package(nlohmann_json REQUIRED)
    else()
        message(STATUS "Downloading dependency nlohmann_json.")
        FetchContent_Declare(json
            GIT_REPOSITORY https://github.com/nlohmann/json.git
            GIT_TAG v3.9.1)
        FetchContent_GetProperties(json)
        if(NOT json_POPULATED)
            FetchContent_Populate(json)
            set(JSON_BuildTests OFF CACHE INTERNAL "")
            add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
        endif()
    endif()
endif()

if(bactria_STDOUT_BACKENDS)
    if(bactria_SYSTEM_FMT)
        find_package(fmt REQUIRED)
    else()
        message(STATUS "Downloading dependency {fmt}.")
        FetchContent_Declare(fmtlib
            GIT_REPOSITORY https://github.com/fmtlib/fmt.git
            GIT_TAG 7.1.3)
        FetchContent_GetProperties(fmtlib)
        if(NOT fmtlib_POPULATED)
            FetchContent_Populate(fmtlib)
            add_subdirectory(${fmtlib_SOURCE_DIR} ${fmtlib_BINARY_DIR} EXCLUDE_FROM_ALL)
        endif()
    endif()
endif()

add_subdirectory("external")
add_subdirectory("src")

