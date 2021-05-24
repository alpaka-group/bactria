if(bactria_CUDA_BACKENDS)
    add_library(bactria_ranges_nvtx MODULE Ranges.cpp)
    target_link_libraries(bactria_ranges_nvtx PRIVATE bactria CUDA::nvToolsExt)
endif()

