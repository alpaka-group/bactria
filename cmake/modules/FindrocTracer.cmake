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

# This will define:
# rocTracer_FOUND - System has rocTracer libraries
# 
# rocTracer::rocTracer - target for linking the rocTracer library
# ROCTRACER_INCLUDE_DIR - include directory for the rocTracer library
# ROCTRACER_LIBRARY - the rocTracer library
#
# rocTracer::rocTX - target for linking the rocTX library
# ROCTX_INCLUDE_DIR - include directory for the rocTX library
# ROCTX_LIBRARY - the rocTX library

include(FindPackageHandleStandardArgs)

# rocTracer library 
find_path(ROCTRACER_INCLUDE_DIR
          NAMES roctracer.h
          PATHS /opt/rocm/roctracer/include)
find_library(ROCTRACER_LIBRARY
             NAMES roctracer64
             PATHS /opt/rocm/lib)
if(ROCTRACER_INCLUDE_DIR AND ROCTRACER_LIBRARY)
    add_library(rocTracer::rocTracer SHARED IMPORTED)
    set_target_properties(rocTracer::rocTracer PROPERTIES
                          IMPORTED_LOCATION ${ROCTRACER_LIBRARY}
                          INTERFACE_INCLUDE_DIRECTORIES ${ROCTRACER_INCLUDE_DIR})
    set(_rocTracer_FOUND TRUE)
else()
    set(_rocTracer_FOUND FALSE)
endif()

# rocTX library
find_path(ROCTX_INCLUDE_DIR
          NAMES roctx.h
          PATHS /opt/rocm/roctracer/include)
find_library(ROCTX_LIBRARY
             NAMES roctx64
             PATHS /opt/rocm/lib)
if(ROCTX_INCLUDE_DIR AND ROCTX_LIBRARY)
    add_library(rocTracer::rocTX SHARED IMPORTED)
    set_target_properties(rocTracer::rocTX PROPERTIES
                          IMPORTED_LOCATION ${ROCTX_LIBRARY}
                          INTERFACE_INCLUDE_DIRECTORIES ${ROCTX_INCLUDE_DIR})
    set(_rocTX_FOUND TRUE)
else()
    set(_rocTX_FOUND FALSE)
endif()

if(_rocTracer_FOUND AND _rocTX_FOUND)
    set(rocTracer_FOUND TRUE)

    find_package_handle_standard_args(
        rocTracer DEFAULT_MSG
        ROCTRACER_INCLUDE_DIR ROCTRACER_LIBRARY
        ROCTX_INCLUDE_DIR ROCTX_LIBRARY
    )

    mark_as_advanced(ROCTRACER_INCLUDE_DIR ROCTRACER_LIBRARY ROCTX_INCLUDE_DIR ROCTX_LIBRARY)
endif()