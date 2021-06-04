if(bactria_STDOUT_PLUGINS)
    add_library(bactria_ranges_stdout MODULE Ranges.cpp)
    target_link_libraries(bactria_ranges_stdout PRIVATE bactria fmt::fmt)
endif()