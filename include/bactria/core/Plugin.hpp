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
 * \file Plugin.hpp
 * \brief bactria-internal plugin handling.
 *
 * This file includes bactria's internal view of the plugin functionality. It should not be included directly by the
 * user. As the functionality defined here is intended for bactria's internal use the user should never use anything
 * found in this file.
 */

#pragma once

#include <bactria/core/POSIX.hpp>
#include <bactria/core/Win32.hpp>

#include <iostream>

namespace bactria
{
    /**
     * \brief The platform-specific plugin handle type.
     * \ingroup bactria_core_internal
     *
     * A system-specific typedef for a plugin handle. This typedef is an abstraction for the various native handles,
     * e.g. the handles returned by POSIX' `dlopen()` and Windows' `LoadLibrary()`.
     */
    using plugin_handle_t = system::plugin_handle_t;

    /**
     * \brief Unloads the plugin.
     * \ingroup bactria_core_internal
     *
     * Forwards an open library handle to the native functions for closing shared libraries.
     *
     * \param handle The handle to the plugin in question.
     */
    [[gnu::always_inline]] inline auto unload_plugin(plugin_handle_t handle) noexcept
    {
        system::close_plugin(handle);
    }
} // namespace bactria
