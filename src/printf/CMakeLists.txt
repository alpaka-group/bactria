find_package(fmt)

if(NOT fmt_FOUND)
    message(WARNING "Could not find {fmt}. Disabling printf backend.")
else()
    add_library(bactria_printf MODULE BodyInstrumentation.cpp
                                      FunctionInstrumentation.cpp
                                      GenericInstrumentation.cpp
                                      Instrumentation.cpp
                                      LoopInstrumentation.cpp
                                      Markers.cpp
                                      PhaseInstrumentation.cpp)
    target_link_libraries(bactria_printf PRIVATE bactria fmt::fmt)
endif()

