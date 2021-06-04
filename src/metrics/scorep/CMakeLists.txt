if(bactria_SCOREP_PLUGINS)
    if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
        enable_language(C)
        
        find_program(SCOREP_CONFIG scorep-config PATHS /opt/scorep/bin)
        find_library(SCOREP_CONSTRUCTOR scorep_constructor PATHS /opt/scorep/lib)

        if(NOT SCOREP_CONFIG)
            message(FATAL_ERROR "Could not find scorep-config")
        elseif(NOT SCOREP_CONSTRUCTOR)
            message(FATAL_ERROR "Could not find scorep_constructor")
        else()
            message(STATUS "Found scorep-config: ${SCOREP_CONFIG}")
            message(STATUS "Found scorep_constructor: ${SCOREP_CONSTRUCTOR}")
            add_library(ScoreP INTERFACE)

            # Configure Score-P flags
            if(CMAKE_SIZEOF_VOID_P EQUAL 8)
                set(SCOREP_MEMORY_FLAG "--memory=libc,libc11,c++L64")
            else()
                set(SCOREP_MEMORY_FLAG "--memory=libc,libc11,c++L32")
            endif()

            set(SCOREP_FLAGS --nocompiler --user ${SCOREP_MEMORY_FLAG} --nopomp --kokkos --opencl:runtime --io=posix
                             --thread=pthread --mpp=none)
            
            # Compiler flags
            execute_process(COMMAND
                            ${SCOREP_CONFIG} ${SCOREP_FLAGS} --cxxflags
                            OUTPUT_VARIABLE SCOREP_CXXFLAGS)

            string(REPLACE " " ";" SCOREP_CXXFLAGS ${SCOREP_CXXFLAGS})
            foreach(flag ${SCOREP_CXXFLAGS})
                if(${flag} MATCHES "^-D")
                    string(REPLACE "-D" "" flag ${flag})
                    target_compile_definitions(ScoreP INTERFACE ${flag})
                elseif(${flag} MATCHES "^-I")
                    string(REPLACE "-I" "" flag ${flag})
                    target_include_directories(ScoreP INTERFACE ${flag})
                else()
                    target_compile_options(ScoreP INTERFACE ${flag})
                endif()
            endforeach()

            get_target_property(SCOREP_INCLUDE_DIRS ScoreP INTERFACE_INCLUDE_DIRECTORIES)
            message(STATUS "Found Score-P headers: ${SCOREP_INCLUDE_DIRS}")

            # Linker flags
            execute_process(COMMAND ${SCOREP_CONFIG} ${SCOREP_FLAGS} --ldflags
                            OUTPUT_VARIABLE SCOREP_LDFLAGS)
            string(REPLACE " " ";" SCOREP_LDFLAGS ${SCOREP_LDFLAGS})
            foreach(flag ${SCOREP_LDFLAGS})
                if(${flag} MATCHES "^-L")
                    string(REPLACE "-L" "" flag ${flag})
                    target_link_directories(ScoreP INTERFACE ${flag})
                else()
                    target_link_options(ScoreP INTERFACE ${flag})
                endif()
            endforeach()

            get_target_property(SCOREP_LIBRARY_DIRS ScoreP INTERFACE_LINK_DIRECTORIES)
            message(STATUS "Found Score-P library directories: ${SCOREP_LIBRARY_DIRS}")

            execute_process(COMMAND ${SCOREP_CONFIG} ${SCOREP_FLAGS} --libs
                            OUTPUT_VARIABLE SCOREP_LIBS)
            string(REPLACE " " ";" SCOREP_LIBS ${SCOREP_LIBS})
            foreach(lib ${SCOREP_LIBS})
                if(${lib} MATCHES "^-l")
                    string(REPLACE "-l" "" lib ${lib})
                    target_link_libraries(ScoreP INTERFACE ${lib})
                else()
                    message(WARNING "Unknown linker flag: ${lib}")
                endif()
            endforeach()

            get_target_property(SCOREP_LIBRARIES ScoreP INTERFACE_LINK_LIBRARIES)
            message(STATUS "Found Score-P libraries: ${SCOREP_LIBRARIES}")

            # Generate Score-P's special object file
            execute_process(COMMAND ${SCOREP_CONFIG} ${SCOREP_FLAGS} --adapter-init
                            OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/main.scorep_init.c)
            set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/main.scorep_init.c
                                        LANGUAGE C)

            add_library(bactria_metrics_scorep MODULE Configuration.cpp
                                                      Metrics.cpp
                                                      ${CMAKE_CURRENT_BINARY_DIR}/main.scorep_init.c)
            target_link_libraries(bactria_metrics_scorep PRIVATE bactria ScoreP ${SCOREP_CONSTRUCTOR} toml11::toml11)
        endif()
    else()
        message(FATAL_ERROR "Score-P plugin not supported for non-GNU compilers")
    endif()
endif()