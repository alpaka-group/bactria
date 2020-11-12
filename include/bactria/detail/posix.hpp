/* Copyright 2020 Jan Stephan
 *
 * Licensed under the EUPL, Version 1.2 or - as soon they will be approved by
 * the European Commission - subsequent versions of the EUPL (the “Licence”).
 * You may not use this work except in compliance with the Licence.
 * You may obtain a copy of the Licence at:
 *
 *     http://ec.europa.eu/idabc/eupl.html
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the Licence is distributed on an “AS IS” basis, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 *  Licence permissions and limitations under the Licence.
 */

#ifndef BACTRIA_DETAIL_POSIX_HPP
#define BACTRIA_DETAIL_POSIX_HPP

#ifndef _WIN32

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

#include <dlfcn.h>

#include <bactria/detail/plugin_interface.hpp>

namespace bactria::plugin::detail
{
    using plugin_handle_t = void*;

    [[gnu::always_inline]]
    auto open_plugin(const char* path) noexcept(false)
    {
        if(auto handle = dlopen(path, RTLD_NOW | RTLD_GLOBAL); handle != nullptr)
            return handle;

        throw std::runtime_error{dlerror()};
    }

    template <typename Sig>
    [[gnu::always_inline]]
    auto load_func(plugin_handle_t handle, Sig& ptr, const char* name) noexcept(false)
    {
        if(ptr == nullptr)
        {
            if(ptr = reinterpret_cast<Sig>(dlsym(handle, name)); ptr == nullptr)
                throw std::runtime_error{dlerror()};
        }
    }

    [[gnu::always_inline]]
    auto close_plugin(plugin_handle_t handle) noexcept
    {
        if(auto err = dlclose(handle); err != 0)
        {
            // Technically this is not noexcept-safe. But if we do throw here we have more serious problems anyway.
            std::cerr << "WARNING: Error while closing plugin library: " << dlerror() << '\n';
        }
    }
}

#endif // _WIN32

#endif

