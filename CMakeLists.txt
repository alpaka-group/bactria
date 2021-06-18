# Copyright 2021 Jan Stephan
#
# Licensed under the EUPL, Version 1.2 or - as soon they will be approved by
# the European Commission - subsequent versions of the EUPL (the “Licence”).
# You may not use this work except in compliance with the Licence.
# You may obtain a copy of the Licence at:
#
#     http://ec.europa.eu/idabc/eupl.html
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the Licence is distributed on an “AS IS” basis, WITHOUT
#  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
#  Licence permissions and limitations under the Licence.

cmake_minimum_required(VERSION 3.18)

project("bactria" VERSION       0.0.1
                  DESCRIPTION   "The bactria library is a header-only C++14 library for profiling and tracing."
                  HOMEPAGE_URL  "https://www.github.com/alpaka-group/bactria"
                  LANGUAGES     CXX)

include(CMakeDependentOption)
include(FetchContent)
include(GNUInstallDirs)

###############################################################################
# Options and variants
###############################################################################

option(bactria_BUILD_DOCUMENTATION "Generate the Doxygen documentation" OFF)
option(bactria_BUILD_EXAMPLES "Build examples" ON)

option(bactria_ENABLE_PLUGINS "Build bactria's plugins" ON)
cmake_dependent_option(bactria_CUDA_PLUGINS "Build the CUDA toolkit plugins" OFF bactria_ENABLE_PLUGINS OFF)
cmake_dependent_option(bactria_STDOUT_PLUGINS "Build the STDOUT plugins" ON bactria_ENABLE_PLUGINS OFF)
cmake_dependent_option(bactria_SYSTEM_FMT "Use your local installation of {fmt}" ON bactria_STDOUT_PLUGINS OFF)
cmake_dependent_option(bactria_SYSTEM_TOML11 "Use your local installation of toml11" ON bactria_ENABLE_PLUGINS OFF)
cmake_dependent_option(bactria_JSON_PLUGINS "Build the JSON plugins" ON bactria_ENABLE_PLUGINS OFF)
cmake_dependent_option(bactria_SYSTEM_JSON "Use your local installation of nlohmann-json" ON bactria_JSON_PLUGINS OFF)
cmake_dependent_option(bactria_ROCM_PLUGINS "Build the ROCm plugins" OFF bactria_ENABLE_PLUGINS OFF)
cmake_dependent_option(bactria_SCOREP_PLUGINS "Build the Score-P plugins" OFF bactria_ENABLE_PLUGINS OFF)
cmake_dependent_option(bactria_STDOUT_PLUGINS "Build the STDOUT plugins" ON bactria_ENABLE_PLUGINS OFF)


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

if(bactria_ENABLE_PLUGINS)
    if(bactria_SYSTEM_TOML11)
    find_package(toml11 REQUIRED)
    else()
    message(STATUS "Downloading dependency toml11.")
    FetchContent_Declare(toml_eleven
        GIT_REPOSITORY https://github.com/ToruNiina/toml11.git
        GIT_TAG v3.6.1)
    FetchContent_MakeAvailable(toml_eleven)
    endif()

    if(bactria_CUDA_PLUGINS)
    find_package(CUDAToolkit REQUIRED)
    endif()

    if(bactria_JSON_PLUGINS)
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

    if(bactria_ROCM_PLUGINS)
        find_package(rocTracer REQUIRED)
    endif()

    if(bactria_STDOUT_PLUGINS)
        if(bactria_SYSTEM_FMT)
            find_package(fmt REQUIRED)
        else()
            message(STATUS "Downloading dependency {fmt}.")
            FetchContent_Declare(fmtlib
                GIT_REPOSITORY https://github.com/fmtlib/fmt.git
                GIT_TAG 7.1.3)
            FetchContent_MakeAvailable(fmtlib)
        endif()
    endif()

    add_subdirectory("src")
endif()


