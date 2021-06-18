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

/**
 * \file Win32.hpp
 * \brief Windows-specific internals.
 *
 * The functionality described here is part of bactria's internals. It should not be included directly by the user.
 */

#ifdef _WIN32

#    include <windows.h>

#    include <cstdio>
#    include <string>
#    include <system_error>

namespace bactria
{
    namespace system
    {
        /**
         * \brief The Win32-specific handle type.
         * \ingroup bactria_core_internal
         *
         * Plugin handle type for Windows systems.
         */
        // HMODULE <- HINSTANCE <- HANDLE <- PVOID <- void*
        using plugin_handle_t = HMODULE;

        /**
         * \brief Convert a Win32 error code to a `std::string`.
         *
         * Converts a Win32 system error code (returned by `GetLastError()`) to a useful error message and stores
         * the latter in a `std::string`.
         *
         * \return A `std::string` containing the last error message.
         */
        [[nodiscard]] auto make_last_error_string() -> std::string
        {
            const auto code = std::error_code{GetLastError(), std::system_category()};
            return code.message();
        }

        /**
         * \brief The Win32-specific plugin loader.
         * \ingroup bactria_core_internal
         *
         * Opens the plugin specified by the user through the corresponding environment variable.
         *
         * \param[in] path The file path to the plugin library.
         * \return A Win32 plugin handle.
         * \throws std::runtime_error If loading of the plugin failed.
         * \sa close_plugin(), load_func()
         */
        [[nodiscard]] auto open_plugin(const char* path) -> plugin_handle_t
        {
            auto handle = LoadLibrary(path);
            if(handle != nullptr)
                return handle;

            throw std::runtime_error{make_last_error_string()};
        }

        /**
         * \brief The Win32-specific function loader.
         * \ingroup bactria_core_internal
         *
         * Loads a function from the plugin specified by the user through environment variables.
         *
         * \tparam Sig The signature of the function to load from the plugin.
         * \param handle The Windows-specific plugin handle.
         * \param ptr The function pointer to bind the plugin function to.
         * \param name The name of the function to load from the plugin.
         * \throws std::runtime_error If loading of the function failed.
         * \sa open_plugin(), close_plugin()
         */
        template<typename Sig>
        auto load_func(plugin_handle_t handle, Sig& ptr, const char* name) -> void
        {
            if(ptr == nullptr)
            {
                ptr = reinterpret_cast<Sig>(GetProcAddress(handle, name));
                if(ptr == nullptr)
                    throw std::runtime_error{make_last_error_string()};
            }
        }

        /**
         * \brief The Win32-specific plugin unloader
         * \ingroup bactria_core_internal
         *
         * This function closes a plugin loaded by open_plugin().
         *
         * \param handle The Windows-specific plugin handle to close.
         * \sa open_plugin(), load_func()
         */
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
    } // namespace system
} // namespace bactria

#endif // _WIN32
