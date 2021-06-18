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
 * \file PluginInterface.hpp
 * \brief Interface for plugin developers.
 *
 * This is bactria's ranges plugin interface. Plugin developers should include this file and implement all functions
 * declared by it.
 */

#pragma once

#include <cstdint>

/**
 * \defgroup bactria_ranges_plugin Plugin interface
 * \ingroup bactria_ranges
 *
 * This is the interface for a ranges plugin. Plugin developers should include ranges/PluginInterface.hpp and
 * implement all functions listed here.
 * \{
 */

extern "C"
{
    /**
     * \brief Create an event handle.
     *
     * This function creates a plugin-specific event handle. This is internally used by bactria::Event to communicate
     * with the plugin. Each bactria::Event encapsulates its own event handle.
     *
     * \param[in] color The color of the event (as it should appear on the visualizer).
     * \param[in] cat_name The category's name (for filtering).
     * \param[in] cat_id The category's id (for filtering).
     * \return A handle to the plugin-specific event.
     * \sa bactria_ranges_destroy_event, bactria_ranges_fire_event
     */
    auto bactria_ranges_create_event(std::uint32_t color, char const* cat_name, std::uint32_t cat_id) noexcept
        -> void*;

    /**
     * \brief Destroy an event handle.
     *
     * This function destroys a plugin-specific event handle. It is called internally by bactria::Event::~Event().
     * The \a event_handle must not be used after the call unless it has been reinitialized with
     * bactria_ranges_create_event().
     *
     * \param[in] event_handle The event handle created by bactria_ranges_create_event().
     * \sa bactria_ranges_create_event, bactria_ranges_fire_event
     */
    auto bactria_ranges_destroy_event(void* event_handle) noexcept -> void;

    /**
     * \brief Fire an event.
     *
     * This function fires a plugin-specific event. It is called internally by bactria::Event::fire().
     *
     * \param[in,out] event_handle The event handle created by bactria_ranges_create_event().
     * \param[in] event_name The name of the event (as it should appear on the visualizer).
     * \param[in] source The event's source file location.
     * \param[in] lineno The event's source line location.
     * \param[in] caller The event's calling function.
     * \sa bactria_ranges_create_event, bactria_ranges_destroy_event
     */
    auto bactria_ranges_fire_event(
        void* event_handle,
        char const* event_name,
        char const* source,
        std::uint32_t lineno,
        char const* caller) noexcept -> void;

    /**
     * \brief Create a range handle.
     *
     * This function creates a plugin-specific range handle. This is internally used by bactria::Range to communicate
     * with the plugin. Each bactria::Range encapsulates its own range handle.
     *
     * \param[in] name The name of the range (as it should appear on the visualizer).
     * \param[in] color The color of the range (as it should appear on the visualizer).
     * \param[in] cat_name The category's name (for filtering).
     * \param[in] cat_id The category's id (for filtering).
     * \return A handle to the plugin-specific range.
     * \sa bactria_ranges_destroy_range, bactria_ranges_start_range, bactria_ranges_stop_range
     */
    auto bactria_ranges_create_range(
        char const* name,
        std::uint32_t color,
        char const* cat_name,
        std::uint32_t cat_id) noexcept -> void*;

    /**
     * \brief Destroy a range handle.
     *
     * This function destroys a plugin-specific range handle. It is called internally by bactria::Range::~Range(). The
     * \a range_handle must not be used after the call unless it has been reinitialized with
     * bactria_ranges_create_range().
     *
     * \param[in] range_handle The event handle created by bactria_ranges_create_event().
     * \sa bactria_ranges_create_range, bactria_ranges_start_range, bactria_ranges_stop_range
     */
    auto bactria_ranges_destroy_range(void* range_handle) noexcept -> void;

    /**
     * \brief Start a range.
     *
     * This function starts a plugin-specific range. It is called internally by bactria::Range::start().
     *
     * \param[in,out] range_handle The range handle created by bactria_ranges_create_range().
     * \sa bactria_ranges_create_range, bactria_ranges_destroy_range, bactria_ranges_stop_range
     */
    auto bactria_ranges_start_range(void* range_handle) noexcept -> void;

    /**
     * \brief Stop a range.
     *
     * This function stops a plugin-specific range. It is called internally by bactria::Range::stop().
     *
     * \param[in,out] range_handle The range handle created by bactria_ranges_create_range().
     * \sa bactria_ranges_create_range, bactria_ranges_destroy_range, bactria_ranges_start_range
     */
    auto bactria_ranges_stop_range(void* range_handle) noexcept -> void;
}

/**
 * \}
 */
