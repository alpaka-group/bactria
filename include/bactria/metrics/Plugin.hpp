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
 * \brief bactria-internal handling of metrics plugins.
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
    namespace metrics
    {
        /**
         * \defgroup bactria_metrics Metrics functionality
         *
         * bactria's metrics part. This provides functionality for collecting various metrics, such as hardware
         * counters, loop iterations, and so on.
         */
        namespace plugin
        {
            /**
             * \defgroup bactria_metrics_internal Internal documentation. Not intended or useful for the user.
             * \ingroup bactria_metrics
             * \{
             */
            /**
             * \brief Checks for an active metrics plugin.
             *
             * This function checks for an activate metrics plugin. It should never be called by the user directly.
             *
             * \return true If `BACTRIA_DEACTIVATE` is NOT defined and `BACTRIA_METRICS_PLUGIN` is defined.
             * \return false If either `BACTRIA_DEACTIVATE` is defined or `BACTRIA_METRICS_PLUGIN` is NOT defined.
             */
            inline auto activated() -> bool
            {
                static bool const activated = is_active() && (std::getenv("BACTRIA_METRICS_PLUGIN") != nullptr);
                return activated;
            }

            /* Standard function pointer declaration style is forbidden because of noexcept */
            /**
             * \brief Signature for plugin function bactria_metrics_create_sector().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            using create_sector_t = std::add_pointer_t<void*(char const*, std::uint32_t) noexcept>;

            /**
             * \brief Pointer to plugin function bactria_metrics_create_sector().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            auto create_sector_ptr = create_sector_t{nullptr};

            /**
             * \brief Signature for plugin function bactria_metrics_destroy_sector().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            using destroy_sector_t = std::add_pointer_t<void(void*) noexcept>;

            /**
             * \brief Pointer to plugin function bactria_metrics_destroy_sector().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            auto destroy_sector_ptr = destroy_sector_t{nullptr};

            /**
             * \brief Signature for plugin function bactria_metrics_enter_sector().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            using enter_sector_t = std::add_pointer_t<void(void*, char const*, std::uint32_t, char const*) noexcept>;

            /**
             * \brief Pointer to plugin function bactria_metrics_enter_sector().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            auto enter_sector_ptr = enter_sector_t{nullptr};

            /**
             * \brief Signature for plugin function bactria_metrics_leave_sector().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            using leave_sector_t = std::add_pointer_t<void(void*, char const*, std::uint32_t, char const*) noexcept>;

            /**
             * \brief Pointer to plugin function bactria_metrics_leave_sector().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            auto leave_sector_ptr = leave_sector_t{nullptr};

            /**
             * \brief Signature for plugin function bactria_metrics_sector_summary().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            using sector_summary_t = std::add_pointer_t<void(void*) noexcept>;

            /**
             * \brief Pointer to plugin function bactria_metrics_sector_summary().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            auto sector_summary_ptr = sector_summary_t{nullptr};

            /**
             * \brief Signature for plugin function bactria_metrics_create_phase().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            using create_phase_t = std::add_pointer_t<void*(char const*) noexcept>;

            /**
             * \brief Pointer to plugin function bactria_metrics_create_phase().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            auto create_phase_ptr = create_phase_t{nullptr};

            /**
             * \brief Signature for plugin function bactria_metrics_destroy_phase().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            using destroy_phase_t = std::add_pointer_t<void(void*) noexcept>;

            /**
             * \brief Pointer to plugin function bactria_metrics_destroy_phase().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            auto destroy_phase_ptr = destroy_phase_t{nullptr};

            /**
             * \brief Signature for plugin function bactria_metrics_enter_phase().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            using enter_phase_t = std::add_pointer_t<void(void*, char const*, std::uint32_t, char const*) noexcept>;

            /**
             * \brief Pointer to plugin function bactria_metrics_enter_phase().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            auto enter_phase_ptr = enter_phase_t{nullptr};

            /**
             * \brief Signature for plugin function bactria_metrics_leave_phase().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            using leave_phase_t = std::add_pointer_t<void(void*, char const*, std::uint32_t, char const*) noexcept>;

            /**
             * \brief Pointer to plugin function bactria_metrics_leave_phase().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            auto leave_phase_ptr = leave_phase_t{nullptr};

            /**
             * \brief Initializes the metrics plugin.
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             *
             * \return A platform-specific plugin handle.
             * \throws std::runtime_error On failure during plugin initialization.
             */
            [[nodiscard]] inline auto load() -> plugin_handle_t
            {
                auto const path = std::getenv("BACTRIA_METRICS_PLUGIN");
                if(path != nullptr)
                {
                    auto handle = system::open_plugin(path);

                    system::load_func(handle, create_sector_ptr, "bactria_metrics_create_sector");
                    system::load_func(handle, destroy_sector_ptr, "bactria_metrics_destroy_sector");
                    system::load_func(handle, enter_sector_ptr, "bactria_metrics_enter_sector");
                    system::load_func(handle, leave_sector_ptr, "bactria_metrics_leave_sector");
                    system::load_func(handle, sector_summary_ptr, "bactria_metrics_sector_summary");

                    system::load_func(handle, create_phase_ptr, "bactria_metrics_create_phase");
                    system::load_func(handle, destroy_phase_ptr, "bactria_metrics_destroy_phase");
                    system::load_func(handle, enter_phase_ptr, "bactria_metrics_enter_phase");
                    system::load_func(handle, leave_phase_ptr, "bactria_metrics_leave_phase");

                    return handle;
                }

                // getenv failed
                throw std::runtime_error{std::string{"Failed to load bactria metrics plugin "} + path};
            }

            /**
             * \brief Creates a plugin-specific sector handle.
             *
             * Used internally by the Sector class. Users should not call this directly.
             *
             * \sa Sector::Sector()
             */
            [[nodiscard, gnu::always_inline]] inline auto create_sector(char const* name, std::uint32_t tag) noexcept
            {
                if(create_sector_ptr != nullptr)
                    return (create_sector_ptr) (name, tag);

                return static_cast<void*>(nullptr);
            }

            /**
             * \brief Destroys a plugin-specific sector handle.
             *
             * Used internally by the Sector class. Users should not call this directly.
             *
             * \sa Sector::~Sector()
             */
            [[gnu::always_inline]] inline auto destroy_sector(void* sector_handle) noexcept
            {
                if(destroy_sector_ptr != nullptr)
                    (destroy_sector_ptr)(sector_handle);
            }

            /**
             * \brief Plugin-specific sector entering.
             *
             * Used internally by the Sector class. Users should not call this directly.

             * \sa Sector::enter()
             */
            [[gnu::always_inline]] inline auto enter_sector(
                void* sector_handle,
                char const* source,
                std::uint32_t lineno,
                char const* caller) noexcept
            {
                if(enter_sector_ptr != nullptr)
                    (enter_sector_ptr)(sector_handle, source, lineno, caller);
            }

            /**
             * \brief Plugin-specific sector leaving.
             *
             * Used internally by the Sector class. Users should not call this directly.
             *
             * \sa Sector::leave()
             */
            [[gnu::always_inline]] inline auto leave_sector(
                void* sector_handle,
                char const* source,
                std::uint32_t lineno,
                char const* caller) noexcept
            {
                if(leave_sector_ptr != nullptr)
                    (leave_sector_ptr)(sector_handle, source, lineno, caller);
            }

            /**
             * \brief Plugin-specific sector summary.
             *
             * Used internally by the Sector class. Users should not call this directly.
             *
             * \sa Sector::summary()
             */
            [[gnu::always_inline]] inline auto sector_summary(void* sector_handle) noexcept
            {
                if(sector_summary_ptr != nullptr)
                    (sector_summary_ptr)(sector_handle);
            }

            /**
             * \brief Creates a plugin-specific phase handle.
             *
             * Used internally by the Phase class. Users should not call this directly.
             *
             * \return A plugin-specific phase handle.
             * \sa Phase::Phase()
             */
            [[nodiscard, gnu::always_inline]] inline auto create_phase(char const* name) noexcept
            {
                if(create_phase_ptr != nullptr)
                    return (create_phase_ptr) (name);

                return static_cast<void*>(nullptr);
            }

            /**
             * \brief Destroys a plugin-specific phase handle.
             *
             * Used internally by the Phase class. Users should not call this direcctly.
             *
             * \sa Phase::~Phase()
             */
            [[gnu::always_inline]] inline auto destroy_phase(void* phase_handle) noexcept
            {
                if(destroy_phase_ptr != nullptr)
                    (destroy_phase_ptr)(phase_handle);
            }

            /**
             * \brief Plugin-specific phase entering.
             *
             * Used internally by the Phase class. Users should not call this directly.
             *
             * \sa Phase::enter()
             */
            [[gnu::always_inline]] inline auto enter_phase(
                void* phase_handle,
                char const* source,
                std::uint32_t lineno,
                char const* caller) noexcept
            {
                if(enter_phase_ptr != nullptr)
                    (enter_phase_ptr)(phase_handle, source, lineno, caller);
            }

            /**
             * \brief Plugin-specific phase leaving.
             *
             * Used internally by the Phase class. Users should not call this directly.
             *
             * \sa Phase::leave()
             */
            [[gnu::always_inline]] inline auto leave_phase(
                void* phase_handle,
                char const* source,
                std::uint32_t lineno,
                char const* caller) noexcept
            {
                if(leave_phase_ptr != nullptr)
                    (leave_phase_ptr)(phase_handle, source, lineno, caller);
            }
            /** \} */
        } // namespace plugin
    } // namespace metrics
} // namespace bactria