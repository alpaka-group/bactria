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

namespace bactria
{
    namespace plugin
    {
        namespace printf
        {
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
    }
}

namespace
{
    auto const exec_stamp = std::chrono::steady_clock::now();
}

extern "C"
{
    [[clang::acquire_handle("bactria event")]]
    auto bactria_plugin_create_event(const char* name, std::uint32_t color, std::uint32_t category) noexcept -> void*
    {
        return new bactria::plugin::printf::event{name, color, category};
    }
    
    auto bactria_plugin_destroy_event(void* event_handle [[clang::release_handle("bactria event")]]) noexcept -> void
    {
        auto event = static_cast<bactria::plugin::printf::event*>(event_handle);
        delete event;
    }

    auto bactria_plugin_fire_event(void* event_handle [[clang::use_handle("bactria event")]]) noexcept -> void
    {

        using precise_duration = std::chrono::duration<double, std::micro>;
        auto const timestamp = std::chrono::steady_clock::now();
        auto const elapsed = std::chrono::duration_cast<precise_duration>(timestamp - exec_stamp);

        auto event = static_cast<bactria::plugin::printf::event*>(event_handle);

        fmt::print(fg(fmt::rgb(event->color)),
                   "Event fired after {:.3}: {} (Category {})\n", elapsed, event->name, event->category);
    }

    [[nodiscard, clang::acquire_handle("bactria range")]]
    auto bactria_plugin_create_range(const char* name, std::uint32_t color, std::uint32_t category) noexcept -> void*
    {
        return new bactria::plugin::printf::range{name, color, category};
    }

    auto bactria_plugin_destroy_range(void* range_handle [[clang::release_handle("bactria range")]]) noexcept -> void
    {
        auto range = static_cast<bactria::plugin::printf::range*>(range_handle);
        delete range;
    }

    auto bactria_plugin_start_range(void* range_handle [[clang::use_handle("bactria range")]]) noexcept -> void
    {
        auto const now = std::chrono::steady_clock::now();

        auto range = static_cast<bactria::plugin::printf::range*>(range_handle);
        range->start = now;

        fmt::print(fg(fmt::rgb(range->color)), "Entering range {} (Category {})\n", range->name, range->category);
    }

    auto bactria_plugin_stop_range(void* range_handle [[clang::use_handle("bactria range")]]) noexcept -> void
    {
        using precise_duration = std::chrono::duration<double, std::micro>;

        auto const now = std::chrono::steady_clock::now();
        auto range = static_cast<bactria::plugin::printf::range*>(range_handle);

        auto const elapsed = std::chrono::duration_cast<precise_duration>(now - range->start);

        fmt::print(fg(fmt::rgb(range->color)), "Leaving range {} (Category {}) after {:.3}\n",
                   range->name, range->category, elapsed);
    }
}
