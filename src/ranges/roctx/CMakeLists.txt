if(bactria_ROCM_PLUGINS)
    add_library(bactria_ranges_roctx MODULE Ranges.cpp)
    target_link_libraries(bactria_ranges_roctx PRIVATE bactria rocTracer::rocTX)
endif()