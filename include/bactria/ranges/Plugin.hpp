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
 * \brief bactria-internal handling of ranges plugins.
 *
 * The functionality described here is part of bactria's internals. It should not be included directly by the user.
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
        /**
         * \defgroup bactria_ranges Ranges functionality
         *
         * bactria's ranges part. This provides functionality for highlighting code parts in a visual profiler.
         */
        namespace plugin
        {
            /**
             * \defgroup bactria_ranges_internal Internal documentation. Not intended or useful for the user.
             * \ingroup bactria_ranges
             * \{
             */

            /**
             * \brief Checks for an active ranges plugin.
             *
             * This function checks for an activate ranges plugin. It should never be called by the user directly.
             *
             * \return true If `BACTRIA_DEACTIVATE` is NOT defined and `BACTRIA_RANGES_PLUGIN` is defined.
             * \return false If either `BACTRIA_DEACTIVATE` is defined or `BACTRIA_RANGES_PLUGIN` is NOT defined.
             */
            inline auto activated() -> bool
            {
                static bool const activated = is_active() && (std::getenv("BACTRIA_RANGES_PLUGIN") != nullptr);
                return activated;
            }

            /* Standard function pointer declaration style is forbidden because of noexcept */
            /**
             * \brief Signature for plugin function bactria_ranges_create_event().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            using create_event_t = std::add_pointer_t<void*(std::uint32_t, char const*, std::uint32_t) noexcept>;

            /**
             * \brief Pointer to plugin function bactria_ranges_create_event().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            auto create_event_ptr = create_event_t{nullptr};

            /**
             * \brief Signature for plugin function bactria_ranges_destroy_event().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            using destroy_event_t = std::add_pointer_t<void(void*) noexcept>;

            /**
             * \brief Pointer to plugin function bactria_ranges_destroy_event().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            auto destroy_event_ptr = destroy_event_t{nullptr};

            /**
             * \brief Signature for plugin function bactria_ranges_fire_event().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            using fire_event_t
                = std::add_pointer_t<void(void*, char const*, char const*, std::uint32_t, char const*) noexcept>;

            /**
             * \brief Pointer to plugin function bactria_ranges_fire_event().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            auto fire_event_ptr = fire_event_t{nullptr};

            /**
             * \brief Signature for plugin function bactria_ranges_create_range().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            using create_range_t
                = std::add_pointer_t<void*(char const*, std::uint32_t, char const*, std::uint32_t) noexcept>;

            /**
             * \brief Pointer to plugin function bactria_ranges_create_range().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            auto create_range_ptr = create_range_t{nullptr};

            /**
             * \brief Signature for plugin function bactria_ranges_destroy_range().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            using destroy_range_t = std::add_pointer_t<void(void*) noexcept>;

            /**
             * \brief Pointer to plugin function bactria_ranges_destroy_range().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            auto destroy_range_ptr = destroy_range_t{nullptr};

            /**
             * \brief Signature for plugin function bactria_ranges_start_range().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            using start_range_t = std::add_pointer_t<void(void*) noexcept>;

            /**
             * \brief Pointer to plugin function bactria_ranges_start_range().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.Internal
             * documentation. Not intended or useful for the user.
             */
            auto start_range_ptr = start_range_t{nullptr};

            /**
             * \brief Signature for plugin function bactria_ranges_stop_range().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            using stop_range_t = std::add_pointer_t<void(void*) noexcept>;

            /**
             * \brief Pointer to plugin function bactria_ranges_stop_range().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            auto stop_range_ptr = stop_range_t{nullptr};

            /**
             * \brief Initializes the ranges plugin.
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             *
             * \return A platform-specific plugin handle.
             * \throws std::runtime_error On failure during plugin initialization.
             */
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

            /**
             * \brief Creates a plugin-specific event handle.
             *
             * Used internally by the Event class. Users should not call this directly.
             *
             * \sa Event::Event()
             */
            [[nodiscard, gnu::always_inline]] inline auto create_event(
                std::uint32_t color,
                char const* cat_name,
                std::uint32_t cat_id) noexcept
            {
                if(create_event_ptr != nullptr)
                    return (create_event_ptr) (color, cat_name, cat_id);

                return static_cast<void*>(nullptr);
            }

            /**
             * \brief Destroys a plugin-specific event handle.
             *
             * Used internally by the Event class. Users should not call this directly.
             *
             * \sa Event::~Event()
             */
            [[gnu::always_inline]] inline auto destroy_event(void* event_handle) noexcept
            {
                if(destroy_event_ptr != nullptr)
                    (destroy_event_ptr)(event_handle);
            }

            /**
             * \brief Plugin-specific event firing.
             *
             * Used internally by the Event class. Users should not call this directly.
             *
             * \sa Event::fire()
             */
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

            /**
             * \brief Creates a plugin-specific range handle.
             *
             * Used internally by the Range class. Users should not call this directly.
             *
             * \sa Range::Range()
             */
            [[nodiscard, gnu::always_inline]] inline auto create_range(
                char const* name,
                std::uint32_t color,
                char const* cat_name,
                std::uint32_t cat_id) noexcept
            {
                if(create_range_ptr != nullptr)
                    return (create_range_ptr) (name, color, cat_name, cat_id);

                return static_cast<void*>(nullptr);
            }

            /**
             * \brief Destroys a plugin-specific range handle.
             *
             * Used internally by the Range class. Users should not call this directly.
             *
             * \sa Range::~Range()
             */
            [[gnu::always_inline]] inline auto destroy_range(void* range_handle) noexcept
            {
                if(destroy_range_ptr != nullptr)
                    (destroy_range_ptr)(range_handle);
            }

            /**
             * \brief Plugin-specific range starting.
             *
             * Used internally by the Range class. Users should not call this directly.
             *
             * \sa Range::start()
             */
            [[gnu::always_inline]] inline auto start_range(void* range_handle) noexcept
            {
                if(start_range_ptr != nullptr)
                    (start_range_ptr)(range_handle);
            }

            /**
             * \brief Plugin-specific range stopping.
             *
             * Used internally by the Range class. Users should not call this directly.
             *
             * \sa Range::stop()
             */
            [[gnu::always_inline]] inline auto stop_range(void* range_handle) noexcept
            {
                if(stop_range_ptr != nullptr)
                    (stop_range_ptr)(range_handle);
            }
            /** \} */
        } // namespace plugin
    } // namespace ranges
} // namespace bactria