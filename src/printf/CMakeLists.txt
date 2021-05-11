if(bactria_STDOUT_BACKENDS)
    add_library(bactria_printf MODULE BodyInstrumentation.cpp
                                      FunctionInstrumentation.cpp
                                      GenericInstrumentation.cpp
                                      Instrumentation.cpp
                                      LoopInstrumentation.cpp
                                      Markers.cpp
                                      PhaseInstrumentation.cpp)
    target_link_libraries(bactria_printf PRIVATE bactria fmt::fmt)
endif()

