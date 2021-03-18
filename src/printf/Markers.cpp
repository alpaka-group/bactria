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

#include <bactria/PluginInterface.hpp>

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
        char const* name;
        std::uint32_t color;
        std::uint32_t category;
    };

    struct range
    {
        char const* name;
        std::uint32_t color;
        std::uint32_t category;
        std::chrono::steady_clock::time_point start{};
    };
}

extern "C"
{
    [[clang::acquire_handle("bactria event")]]
    auto bactria_plugin_create_event(char const* name, std::uint32_t color, std::uint32_t category) noexcept -> void*
    {
        return new event{name, color, category};
    }
    
    auto bactria_plugin_destroy_event(void* event_handle [[clang::release_handle("bactria event")]]) noexcept -> void
    {
        auto ev = static_cast<event*>(event_handle);
        delete ev;
    }

    auto bactria_plugin_fire_event(void* event_handle [[clang::use_handle("bactria event")]]) noexcept -> void
    {

        using precise_duration = std::chrono::duration<double, std::micro>;
        auto const timestamp = std::chrono::steady_clock::now();
        auto const elapsed = std::chrono::duration_cast<precise_duration>(timestamp - exec_stamp);

        auto ev = static_cast<event*>(event_handle);

        fmt::print(fg(fmt::rgb(ev->color)),
                   "Event fired after {:.3}: {} (Category {})\n", elapsed, ev->name, ev->category);
    }

    [[nodiscard, clang::acquire_handle("bactria range")]]
    auto bactria_plugin_create_range(char const* name, std::uint32_t color, std::uint32_t category) noexcept -> void*
    {
        return new range{name, color, category};
    }

    auto bactria_plugin_destroy_range(void* range_handle [[clang::release_handle("bactria range")]]) noexcept -> void
    {
        auto r = static_cast<range*>(range_handle);
        delete r;
    }

    auto bactria_plugin_start_range(void* range_handle [[clang::use_handle("bactria range")]]) noexcept -> void
    {
        auto const now = std::chrono::steady_clock::now();

        auto r = static_cast<range*>(range_handle);
        r->start = now;

        fmt::print(fg(fmt::rgb(r->color)), "Entering range {} (Category {})\n", r->name, r->category);
    }

    auto bactria_plugin_stop_range(void* range_handle [[clang::use_handle("bactria range")]]) noexcept -> void
    {
        using precise_duration = std::chrono::duration<double, std::micro>;

        auto const now = std::chrono::steady_clock::now();
        auto r = static_cast<range*>(range_handle);

        auto const elapsed = std::chrono::duration_cast<precise_duration>(now - r->start);

        fmt::print(fg(fmt::rgb(r->color)), "Leaving range {} (Category {}) after {:.3}\n",
                   r->name, r->category, elapsed);
    }
}
