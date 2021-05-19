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

#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/core.h>

#include <chrono>
#include <cstdint>
#include <iostream>

namespace
{
    auto const exec_stamp = std::chrono::steady_clock::now();

    struct event
    {
        std::uint32_t color;
        char const* cat_name;
        std::uint32_t cat_id;
    };

    struct range
    {
        char const* name;
        std::uint32_t color;
        char const* cat_name;
        std::uint32_t cat_id;
        std::chrono::steady_clock::time_point start{};
    };
} // namespace

extern "C"
{
    auto bactria_ranges_create_event(std::uint32_t color, char const* cat_name, std::uint32_t cat_id) noexcept -> void*
    {
        return new event{color, cat_name, cat_id};
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
        using precise_duration = std::chrono::duration<double, std::micro>;
        auto const timestamp = std::chrono::steady_clock::now();
        auto const elapsed = std::chrono::duration_cast<precise_duration>(timestamp - exec_stamp);

        auto ev = static_cast<event*>(event_handle);

        fmt::print(
            fg(fmt::rgb(ev->color)),
            "Event {} (Category {}) fired in {} at {}:{} after {:.3}.\n",
            event_name,
            ev->cat_name,
            caller,
            source,
            lineno,
            elapsed);
    }

    auto bactria_ranges_create_range(
        char const* name,
        std::uint32_t color,
        char const* cat_name,
        std::uint32_t cat_id) noexcept -> void*
    {
        return new range{name, color, cat_name, cat_id};
    }

    auto bactria_ranges_destroy_range(void* range_handle) noexcept -> void
    {
        auto r = static_cast<range*>(range_handle);
        delete r;
    }

    auto bactria_ranges_start_range(void* range_handle) noexcept -> void
    {
        auto const now = std::chrono::steady_clock::now();

        auto r = static_cast<range*>(range_handle);
        r->start = now;

        fmt::print(fg(fmt::rgb(r->color)), "Entering range {} (Category {})\n", r->name, r->cat_name);
    }

    auto bactria_ranges_stop_range(void* range_handle) noexcept -> void
    {
        using precise_duration = std::chrono::duration<double, std::micro>;

        auto const now = std::chrono::steady_clock::now();
        auto r = static_cast<range*>(range_handle);

        auto const elapsed = std::chrono::duration_cast<precise_duration>(now - r->start);

        fmt::print(
            fg(fmt::rgb(r->color)),
            "Leaving range {} (Category {}) after {:.3}\n",
            r->name,
            r->cat_name,
            elapsed);
    }
}
