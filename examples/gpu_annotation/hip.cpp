/* Copyright (c) 2014, NVIDIA CORPORATION. All rights reserved.
 * Copyright (c) 2021, Jan Stephan
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of NVIDIA CORPORATION nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <bactria/bactria.hpp>

#include <hip/hip_runtime.h>

#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

__global__ void init_data_kernel(std::size_t n, double* x)
{
    auto i = hipBlockIdx_x * hipBlockDim_x + hipThreadIdx_x;
    if(i < n)
    {
        x[i] = n - i;
    }
}

__global__ void daxpy_kernel(std::size_t n, double a, double* x, double* y)
{
    auto i = hipBlockIdx_x * hipBlockDim_x + hipThreadIdx_x;
    if(i < n)
    {
        y[i] = a * x[i] + y[i];
    }
}

__global__ void check_results_kernel(std::size_t n, double correctvalue, double* x)
{
    auto i = hipBlockIdx_x * hipBlockDim_x + hipThreadIdx_x;
    if(i < n)
    {
        if(x[i] != correctvalue)
        {
            printf("ERROR at index = %lu, expected = %f, actual: %f\n", i, correctvalue, x[i]);
        }
    }
}

auto init_host_data(std::size_t n, double* x)
{
    bactria::ranges::Range{"init_host_data", bactria::ranges::color::blue};
    for(auto i = std::size_t{0}; i < n; ++i)
    {
        x[i] = i;
    }
}

auto init_data(std::size_t n, double* x, double* x_d, double* y_d)
{
    bactria::ranges::Range{"init_host_data", bactria::ranges::color::yellow};
    hipStream_t copy_stream;
    hipStream_t compute_stream;
    hipStreamCreate(&copy_stream);
    hipStreamCreate(&compute_stream);

    hipMemcpyAsync(x_d, x, n * sizeof(double), hipMemcpyDefault, copy_stream);
    hipLaunchKernelGGL(
        init_data_kernel,
        dim3{static_cast<std::uint32_t>(std::ceil(n / 256.f))},
        dim3{256},
        0,
        compute_stream,
        n,
        y_d);

    hipStreamSynchronize(copy_stream);
    hipStreamSynchronize(compute_stream);

    hipStreamDestroy(compute_stream);
    hipStreamDestroy(copy_stream);
}

auto daxpy(std::size_t n, double a, double* x_d, double* y_d)
{
    bactria::ranges::Range{"daxpy", bactria::ranges::color::magenta};
    hipLaunchKernelGGL(
        daxpy_kernel,
        dim3{static_cast<std::uint32_t>(std::ceil(n / 256.f))},
        dim3{256},
        0,
        0,
        n,
        a,
        x_d,
        y_d);
    hipDeviceSynchronize();
}

auto check_results(std::size_t n, double correctvalue, double* x_d)
{
    bactria::ranges::Range{"check_results", bactria::ranges::color::cyan};
    hipLaunchKernelGGL(
        check_results_kernel,
        dim3{static_cast<std::uint32_t>(std::ceil(n / 256.f))},
        dim3{256},
        0,
        0,
        n,
        correctvalue,
        x_d);
}

auto run_test(std::size_t n)
{
    bactria::ranges::Range{"run_test", bactria::ranges::color::lime};
    double* x;
    double* x_d;
    double* y_d;
    hipSetDevice(0);
    hipHostMalloc((void**) &x, n * sizeof(double));
    hipMalloc((void**) &x_d, n * sizeof(double));
    hipMalloc((void**) &y_d, n * sizeof(double));

    init_host_data(n, x);

    init_data(n, x, x_d, y_d);

    daxpy(n, 1.0, x_d, y_d);

    check_results(n, n, y_d);

    hipFree(y_d);
    hipFree(x_d);
    hipHostFree(x);
    hipDeviceSynchronize();
}

auto main() -> int
{
    try
    {
        auto ctx = bactria::Context{};
        constexpr auto n = std::size_t{1} << 22;
        run_test(n);
    }
    catch(std::runtime_error const& err)
    {
        std::cerr << err.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}