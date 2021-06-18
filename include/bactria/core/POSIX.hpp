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
 * \file POSIX.hpp
 * \brief POSIX-specific internals.
 *
 * The functionality described here is part of bactria's internals. It should not be included directly by the user.
 */

#pragma once

#ifndef _WIN32

#    include <dlfcn.h>

#    include <cstdio>
#    include <cstdlib>
#    include <stdexcept>
#    include <string>

namespace bactria
{
    namespace system
    {
        /**
         * \brief The POSIX-specific handle type.
         * \ingroup bactria_core_internal
         *
         * Plugin handle type for POSIX systems.
         */
        using plugin_handle_t = void*;

        /**
         * \brief The POSIX-specific plugin loader.
         * \ingroup bactria_core_internal
         *
         * Opens the plugin specified by the user through the corresponding environment variable.
         *
         * \param[in] path The file path to the plugin library.
         * \return A POSIX plugin handle.
         * \throws std::runtime_error If loading of the plugin failed.
         * \sa close_plugin(), load_func()
         */
        [[nodiscard, gnu::always_inline]] inline auto open_plugin(const char* path)
        {
            auto handle = dlopen(path, RTLD_NOW | RTLD_GLOBAL);
            if(handle != nullptr)
                return handle;

            throw std::runtime_error{dlerror()};
        }

        /**
         * \brief The POSIX-specific function loader.
         * \ingroup bactria_core_internal
         *
         * Loads a function from the plugin specified by the user through environment variables.
         *
         * \tparam Sig The signature of the function to load from the plugin.
         * \param handle The POSIX-specific plugin handle.
         * \param ptr The function pointer to bind the plugin function to.
         * \param name The name of the function to load from the plugin.
         * \throws std::runtime_error If loading of the function failed.
         * \sa open_plugin(), close_plugin()
         */
        template<typename Sig>
        [[gnu::always_inline]] inline auto load_func(plugin_handle_t handle, Sig& ptr, const char* name)
        {
            if(ptr == nullptr)
            {
                ptr = reinterpret_cast<Sig>(dlsym(handle, name));
                if(ptr == nullptr)
                    throw std::runtime_error{dlerror()};
            }
        }

        /**
         * \brief The POSIX-specific plugin unloader
         * \ingroup bactria_core_internal
         *
         * This function closes a plugin loaded by open_plugin().
         *
         * \param handle The POSIX-specific plugin handle to close.
         * \sa open_plugin(), load_func()
         */
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
    } // namespace system
} // namespace bactria

#endif // _WIN32
