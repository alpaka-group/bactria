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
 * \brief bactria's plugin interface include.
 *
 * This is bactria's plugin interface. Plugin developers should include this file and implement all functions declared
 * by it.
 */

#pragma once

#include <cstdint>

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
     * \sa bactria_plugin_destroy_event, bactria_plugin_fire_event
     */
    auto bactria_plugin_create_event(std::uint32_t color, char const* cat_name, std::uint32_t cat_id) noexcept
        -> void*;

    /**
     * \brief Destroy an event handle.
     *
     * This function destroys a plugin-specific event handle. It is called internally by bactria::Event::~Event().
     * The \a event_handle must not be used after the call unless it has been reinitialized with
     * bactria_plugin_create_event().
     *
     * \param[in] event_handle The event handle created by bactria_plugin_create_event().
     * \sa bactria_plugin_create_event, bactria_plugin_fire_event
     */
    auto bactria_plugin_destroy_event(void* event_handle) noexcept -> void;

    /**
     * \brief Fire an event.
     *
     * This function fires a plugin-specific event. It is called internally by bactria::Event::fire().
     *
     * \param[in,out] event_handle The event handle created by bactria_plugin_create_event().
     * \param[in] event_name The name of the event (as it should appear on the visualizer).
     * \param[in] source The event's source file location.
     * \param[in] lineno The event's source line location.
     * \param[in] caller The event's calling function.
     * \sa bactria_plugin_create_event, bactria_plugin_destroy_event
     */
    auto bactria_plugin_fire_event(
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
     * \sa bactria_plugin_destroy_range, bactria_plugin_start_range, bactria_plugin_stop_range
     */
    auto bactria_plugin_create_range(
        char const* name,
        std::uint32_t color,
        char const* cat_name,
        std::uint32_t cat_id) noexcept -> void*;

    /**
     * \brief Destroy a range handle.
     *
     * This function destroys a plugin-specific range handle. It is called internally by bactria::Range::~Range(). The
     * \a range_handle must not be used after the call unless it has been reinitialized with
     * bactria_plugin_create_range().
     *
     * \param[in] range_handle The event handle created by bactria_plugin_create_event().
     * \sa bactria_plugin_create_range, bactria_plugin_start_range, bactria_plugin_stop_range
     */
    auto bactria_plugin_destroy_range(void* range_handle) noexcept -> void;

    /**
     * \brief Start a range.
     *
     * This function starts a plugin-specific range. It is called internally by bactria::Range::start().
     *
     * \param[in,out] range_handle The range handle created by bactria_plugin_create_range().
     * \sa bactria_plugin_create_range, bactria_plugin_destroy_range, bactria_plugin_stop_range
     */
    auto bactria_plugin_start_range(void* range_handle) noexcept -> void;

    /**
     * \brief Stop a range.
     *
     * This function stops a plugin-specific range. It is called internally by bactria::Range::stop().
     *
     * \param[in,out] range_handle The range handle created by bactria_plugin_create_range().
     * \sa bactria_plugin_create_range, bactria_plugin_destroy_range, bactria_plugin_start_range
     */
    auto bactria_plugin_stop_range(void* range_handle) noexcept -> void;

    /**
     * \brief Create a sector handle.
     *
     * This function creates a plugin-specific sector handle. This is internally used by bactria::Sector to
     * communicate with the plugin. Each bactria::Sector encapsulates its own sector handle.
     *
     * \param[in] name The name of the sector (as it should appear in the output).
     * \param[in] type The type of the sector. See Tags.hpp for the possible values.
     *
     * \return A handle to the plugin-specific sector.
     * \sa bactria_plugin_destroy_sector, bactria_plugin_enter_sector, bactria_plugin_leave_sector,
     *     bactria_plugin_sector_summary
     */
    auto bactria_plugin_create_sector(char const* name, std::uint32_t type) noexcept -> void*;

    /**
     * \brief Destroy a sector handle.
     *
     * Destroys a plugin-specific sector handle. This is internally called by bactria::Sector::~Sector(). The
     * \a sector_handle must not be used after the call unless it has been reinitialized with
     * bactria_plugin_create_sector().
     *
     * \param[in] sector_handle The sector handle created by bactria_plugin_create_sector().
     * \sa bactria_plugin_create_sector, bactria_plugin_enter_sector, bactria_plugin_leave_sector,
     *     bactria_plugin_sector_summary
     */
    auto bactria_plugin_destroy_sector(void* sector_handle) noexcept -> void;

    /**
     * \brief Enter a sector.
     *
     * Enters the plugin-specific sector. It is called internally by bactria::Sector::enter().
     *
     * \param[in,out] sector_handle The sector handle created by bactria_plugin_create_sector().
     * \param[in] source The source file of the call to bactria::Sector::enter().
     * \param[in] lineno The source line of the call to bactria::Sector::enter().
     * \param[in] caller The surrounding function of the call to bactria::Sector::enter().
     * \sa bactria_plugin_create_sector, bactria_plugin_destroy_sector, bactria_plugin_leave_sector,
     *     bactria_plugin_sector_summary
     */
    auto bactria_plugin_enter_sector(
        void* sector_handle,
        char const* source,
        std::uint32_t lineno,
        char const* caller) noexcept -> void;

    /**
     * \brief Leave a sector.
     *
     * Leaves the plugin-specific sector. It is called internally by bactria::Sector::leave().
     *
     * \param[in,out] sector_handle The sector handle created by bactria_plugin_create_sector().
     * \param[in] source The source file of the call to bactria::Sector::leave().
     * \param[in] lineno The source line of the call to bactria::Sector::leave().
     * \param[in] caller The surrounding function of the call to bactria::Sector::leave().
     * \sa bactria_plugin_create_sector, bactria_plugin_destroy_sector, bactria_plugin_enter_sector,
     *     bactria_plugin_sector_summary
     */
    auto bactria_plugin_leave_sector(
        void* sector_handle,
        char const* source,
        std::uint32_t lineno,
        char const* caller) noexcept -> void;

    /**
     * \brief Summarize a sector.
     *
     * Flushes the sector summary. This is called internally by bactria::Sector::summary() or by
     * bactria::Sector::~Sector() if bactria::Sector::summary() has not been called before.
     *
     * \param[in,out] sector_handle The sector handle created by bactria_plugin_create_sector().
     * \sa bactria_plugin_create_sector, bactria_plugin_destroy_sector, bactria_plugin_enter_sector,
     *     bactria_plugin_leave_sector
     */
    auto bactria_plugin_sector_summary(void* sector_handle) noexcept -> void;

    /**
     * \brief Create a phase handle.
     *
     * Creates a plugin-specific phase handle. This is called internally by bactria::Phase::Phase().
     *
     * \param[in] name The phase name as it should appear in the output.
     * \return A plugin-specific phase handle.
     * \sa bactria_plugin_destroy_phase
     */
    auto bactria_plugin_create_phase(char const* name) noexcept -> void*;

    /**
     * \brief Destroy a phase handle.
     *
     * Destroys a plugin-specific phase handle. This is called internally by bactria::Phase::~Phase().
     * The phase handle must not be used after the call unless it has been reinitialized by a call to
     * bactria_plugin_create_phase().
     *
     * \param[in] phase_handle The phase handle created by bactria_plugin_create_phase().
     * \sa bactria_plugin_create_phase
     */
    auto bactria_plugin_destroy_phase(void* phase_handle) noexcept -> void;

    auto bactria_report_plugin_create_report(char const* name) -> void*;
    auto bactria_report_plugin_destroy_report(void* report_handle) noexcept -> void;
    auto bactria_report_plugin_write_report(void* report_handle) -> void;
    auto bactria_report_plugin_record_incident_bool(void* report_handle, char const* key, bool value) -> void;
    auto bactria_report_plugin_record_incident_int8(void* report_handle, char const* key, std::int8_t value) -> void;
    auto bactria_report_plugin_record_incident_uint8(void* report_handle, char const* key, std::uint8_t value) -> void;
    auto bactria_report_plugin_record_incident_int16(void* report_handle, char const* key, std::int16_t value) -> void;
    auto bactria_report_plugin_record_incident_uint16(void* report_handle, char const* key, std::uint16_t value)
        -> void;
    auto bactria_report_plugin_record_incident_int32(void* report_handle, char const* key, std::int16_t value) -> void;
    auto bactria_report_plugin_record_incident_uint32(void* report_handle, char const* key, std::uint16_t value)
        -> void;
    auto bactria_report_plugin_record_incident_int64(void* report_handle, char const* key, std::int64_t value) -> void;
    auto bactria_report_plugin_record_incident_uint64(void* report_handle, char const* key, std::uint64_t value)
        -> void;
    auto bactria_report_plugin_record_incident_float(void* report_handle, char const* key, float value) -> void;
    auto bactria_report_plugin_record_incident_double(void* report_handle, char const* key, double value) -> void;
    auto bactria_report_plugin_record_incident_string(void* report_handle, char const* key, char const* value) -> void;
}
