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

#pragma once

#include <bactria/core/Activation.hpp>
#include <bactria/core/Plugin.hpp>

#include <cstdint>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <type_traits>

namespace bactria
{
    namespace ranges
    {
        namespace plugin
        {
            inline auto activated() -> bool
            {
                static bool const activated = is_active() && (std::getenv("BACTRIA_RANGES_PLUGIN") != nullptr);
                return activated;
            }

            /* Standard function pointer declaration style is forbidden because of noexcept */

            // Event
            using create_event_t = std::add_pointer_t<void*(std::uint32_t, char const*, std::uint32_t) noexcept>;
            auto create_event_ptr = create_event_t{nullptr};

            using destroy_event_t = std::add_pointer_t<void(void*) noexcept>;
            auto destroy_event_ptr = destroy_event_t{nullptr};

            using fire_event_t
                = std::add_pointer_t<void(void*, char const*, char const*, std::uint32_t, char const*) noexcept>;
            auto fire_event_ptr = fire_event_t{nullptr};

            // Range
            using create_range_t
                = std::add_pointer_t<void*(char const*, std::uint32_t, char const*, std::uint32_t) noexcept>;
            auto create_range_ptr = create_range_t{nullptr};

            using destroy_range_t = std::add_pointer_t<void(void*) noexcept>;
            auto destroy_range_ptr = destroy_range_t{nullptr};

            using start_range_t = std::add_pointer_t<void(void*) noexcept>;
            auto start_range_ptr = start_range_t{nullptr};

            using stop_range_t = std::add_pointer_t<void(void*) noexcept>;
            auto stop_range_ptr = stop_range_t{nullptr};

            [[nodiscard]] inline auto load() -> plugin_handle_t
            {
                auto const path = std::getenv("BACTRIA_RANGES_PLUGIN");
                if(path != nullptr)
                {
                    auto handle = system::open_plugin(path);

                    system::load_func(handle, create_event_ptr, "bactria_ranges_create_event");
                    system::load_func(handle, destroy_event_ptr, "bactria_ranges_destroy_event");
                    system::load_func(handle, fire_event_ptr, "bactria_ranges_fire_event");

                    system::load_func(handle, create_range_ptr, "bactria_ranges_create_range");
                    system::load_func(handle, destroy_range_ptr, "bactria_ranges_destroy_range");
                    system::load_func(handle, start_range_ptr, "bactria_ranges_start_range");
                    system::load_func(handle, stop_range_ptr, "bactria_ranges_stop_range");

                    return handle;
                }

                // getenv failed
                throw std::runtime_error{std::string{"Failed to load bactria ranges plugin "} + path};
            }

            [[nodiscard, gnu::always_inline]] inline auto create_event(
                std::uint32_t color,
                char const* cat_name,
                std::uint32_t cat_id) noexcept
            {
                if(create_event_ptr != nullptr)
                    return (create_event_ptr)(color, cat_name, cat_id);

                return static_cast<void*>(nullptr);
            }

            [[gnu::always_inline]] inline auto destroy_event(void* event_handle) noexcept
            {
                if(destroy_event_ptr != nullptr)
                    (destroy_event_ptr)(event_handle);
            }

            [[gnu::always_inline]] inline auto fire_event(
                void* event_handle,
                char const* event_name,
                char const* source,
                std::uint32_t lineno,
                char const* caller) noexcept
            {
                if(fire_event_ptr != nullptr)
                    (fire_event_ptr)(event_handle, event_name, source, lineno, caller);
            }

            [[nodiscard, gnu::always_inline]] inline auto create_range(
                char const* name,
                std::uint32_t color,
                char const* cat_name,
                std::uint32_t cat_id) noexcept
            {
                if(create_range_ptr != nullptr)
                    return (create_range_ptr)(name, color, cat_name, cat_id);

                return static_cast<void*>(nullptr);
            }

            [[gnu::always_inline]] inline auto destroy_range(void* range_handle) noexcept
            {
                if(destroy_range_ptr != nullptr)
                    (destroy_range_ptr)(range_handle);
            }

            [[gnu::always_inline]] inline auto start_range(void* range_handle) noexcept
            {
                if(start_range_ptr != nullptr)
                    (start_range_ptr)(range_handle);
            }

            [[gnu::always_inline]] inline auto stop_range(void* range_handle) noexcept
            {
                if(stop_range_ptr != nullptr)
                    (stop_range_ptr)(range_handle);
            }
        } // namespace plugin
    } // namespace ranges
} // namespace bactria