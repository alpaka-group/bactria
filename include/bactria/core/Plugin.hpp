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
 * \brief Library-facing plugin interface.
 *
 * This file includes the library's view of the plugin functionality. This should never be included by the user. As
 * the functionality defined here is intended for bactria's internal use the user should never use anything found
 * in this file.
 */

#pragma once

#include <bactria/core/POSIX.hpp>
#include <bactria/core/Win32.hpp>

#include <iostream>

namespace bactria
{
    using plugin_handle_t = system::plugin_handle_t;

    auto unload_plugin(plugin_handle_t handle) noexcept
    {
        system::close_plugin(handle);
    }
} // namespace bactria
