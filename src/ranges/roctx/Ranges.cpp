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

#include <bactria/ranges/PluginInterface.hpp>

#include <roctx.h>

namespace
{
    struct event
    {
    };

    struct range
    {
        char const* message;
        roctx_range_id_t id;
    };
} // namespace

extern "C"
{
    auto bactria_ranges_create_event(
        std::uint32_t /* color */,
        char const* cat_name,
        std::uint32_t /* cat_id */) noexcept -> void*
    {
        // rocTX currently doesn't support colors or categories
        return new event;
    }

    auto bactria_ranges_destroy_event(void* event_handle) noexcept -> void
    {
        auto ev = static_cast<event*>(event_handle);
        delete ev;
    }

    auto bactria_ranges_fire_event(
        void* event_handle,
        char const* event_name,
        char const* source,
        std::uint32_t lineno,
        char const* caller) noexcept -> void
    {
        auto const ev = static_cast<event*>(event_handle);
        roctxMarkA(event_name);
    }

    auto bactria_ranges_create_range(
        char const* name,
        std::uint32_t /* color */,
        char const* /* cat_name */,
        std::uint32_t /* cat_id */) noexcept -> void*
    {
        // rocTX currently doesn't support colors or categories
        return new range{name, roctx_range_id_t{}};
    }

    auto bactria_ranges_destroy_range(void* range_handle) noexcept -> void
    {
        auto r = static_cast<range*>(range_handle);
        delete r;
    }

    auto bactria_ranges_start_range(void* range_handle) noexcept -> void
    {
        auto r = static_cast<range*>(range_handle);
        r->id = roctxRangeStartA(r->message);
    }

    auto bactria_ranges_stop_range(void* range_handle) noexcept -> void
    {
        auto const r = static_cast<range*>(range_handle);
        roctxRangeStop(r->id);
    }
}