if(bactria_CUDA_PLUGINS)
    enable_language(CUDA)
    add_executable(cuda_annotation cuda.cu)
    target_compile_features(cuda_annotation INTERFACE cuda_std_14)
    target_link_libraries(cuda_annotation PRIVATE bactria)
endif()

if(bactria_ROCM_PLUGINS)
    set(GPU_TARGETS "gfx906" CACHE STRING "ROCm GPU targets to compile for")
    find_package(hip REQUIRED)
    add_executable(hip_annotation hip.cpp)
    target_compile_options(hip_annotation PRIVATE "-std=c++14") # hip-clang doesn't obey target_compile_features
    target_link_libraries(hip_annotation PRIVATE bactria hip::device)
endif()