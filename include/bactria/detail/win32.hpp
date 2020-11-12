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

#ifndef BACTRIA_DETAIL_WIN32_HPP
#define BACTRIA_DETAIL_WIN32_HPP

#ifdef _WIN32

#include <bactria/detail/plugin_interface.hpp>

#include <windows.h>

#include <string>
#include <system_error>

namespace bactria::plugin::detail
{
    using plugin_handle_t = HMODULE;

    auto make_last_error_string() noexcept(false) -> std::string
    {
        const auto code = std::error_code{GetLastError(), std::system_category()};
        return code.message();
    }

    auto open_plugin(const char* path) noexcept(false) -> plugin_handle_t
    {
        if(auto handle = LoadLibrary(path); handle != nullptr)
            return handle;

        throw std::runtime_error{make_last_error_string()};
    }

    template <typename Sig>
    auto load_func(plugin_handle_t handle, Sig& ptr, const char* name) noexcept(false) -> void
    {
        if(ptr == nullptr)
        {
            if(ptr = reinterpret_cast<Sig>(GetProcAddress(handle, name)); ptr == nullptr)
                throw std::runtime_error{make_last_error_string()};
        }
    }

    auto close_plugin(plugin_handle_t handle) noexcept -> void
    {
        if(auto err = FreeLibrary(handle); err == 0)
        {
            // Technically this is not noexcept-safe. But if we do throw here we have more serious problems anyway.
            std::cerr << "WARNING: Error while closing plugin library: " << make_last_error_string() << '\n';
        }
    }
}

#endif // _WIN32

#endif
