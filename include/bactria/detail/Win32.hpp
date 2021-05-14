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

#ifdef _WIN32

#   include <windows.h>

#   include <cstdio>
#   include <string>
#   include <system_error>

namespace bactria
{
    namespace plugin
    {
        namespace detail
        {
            // HMODULE <- HINSTANCE <- HANDLE <- PVOID <- void*
            using plugin_handle_t = HMODULE;

            [[nodiscard]] auto make_last_error_string() -> std::string
            {
                const auto code = std::error_code{GetLastError(), std::system_category()};
                return code.message();
            }

            [[nodiscard]] auto open_plugin(const char* path) -> plugin_handle_t
            {
                auto handle = LoadLibrary(path);
                if(handle != nullptr)
                    return handle;

                throw std::runtime_error{make_last_error_string()};
            }

            template <typename Sig>
            auto load_func(plugin_handle_t handle, Sig& ptr, const char* name) -> void
            {
                if(ptr == nullptr)
                {
                    ptr = reinterpret_cast<Sig>(GetProcAddress(handle, name));
                    if(ptr == nullptr)
                        throw std::runtime_error{make_last_error_string()};
                }
            }

            auto close_plugin(plugin_handle_t handle) noexcept -> void
            {
                if(handle == nullptr)
                    return;

                auto err = FreeLibrary(handle);
                if(err == 0)
                {
                    auto errstr = make_last_error_string();
                    if(!errstr.empty())
                        std::fprintf(stderr, "WARNING: Error while closing plugin library: %s\n", errstr.c_str());
                    else
                        std::fprintf(stderr, "WARNING: Unknown error while closing plugin library.\n");
                }
            }
        }
    }
}

#endif // _WIN32

