/* Copyright 2021 Jan Stephan
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

#pragma once

#ifndef _WIN32

#   include <dlfcn.h>

#   include <cstdio>
#   include <cstdlib>
#   include <stdexcept>
#   include <string>

namespace bactria
{
    namespace plugin
    {
        namespace detail
        {
            using plugin_handle_t = void*;

            [[nodiscard, gnu::always_inline]] inline auto open_plugin(const char* path)
            {
                auto handle = dlopen(path, RTLD_NOW | RTLD_GLOBAL);
                if(handle != nullptr)
                    return handle;

                throw std::runtime_error{dlerror()};
            }

            template <typename Sig>
            [[gnu::always_inline]] inline auto load_func(plugin_handle_t handle, Sig& ptr, const char* name)
            {
                if(ptr == nullptr)
                {
                    ptr = reinterpret_cast<Sig>(dlsym(handle, name));
                    if(ptr == nullptr)
                        throw std::runtime_error{dlerror()};
                }
            }

            [[gnu::always_inline]] inline auto close_plugin(plugin_handle_t handle) noexcept
            {
                if(handle == nullptr)
                    return;

                auto err = dlclose(handle);
                if(err != 0)
                {
                    auto errstr = dlerror();
                    if(errstr != nullptr)
                        std::fprintf(stderr, "WARNING: Error while closing plugin library: %s\n", errstr);
                    else
                        std::fprintf(stderr, "WARNING: Unknown error while closing plugin library.\n");
                }
            }
        }
    }
}

#endif // _WIN32

