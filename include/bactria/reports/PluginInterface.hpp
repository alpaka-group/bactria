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
 * This is bactria's reports plugin interface. Plugin developers should include this file and implement all functions
 * declared by it.
 */

#pragma once

#include <cstdint>

/**
 * \defgroup bactria_reports_plugin Plugin interface
 * \ingroup bactria_reports
 *
 * This is the interface for a reports plugin. Plugin developers should include reports/PluginInterface.hpp and
 * implement all functions listed here.
 *
 * \{
 */

extern "C"
{
    /**
     * \brief Creates a plugin-specific report handle.
     *
     * This function creates a plugin-specific report handle which is subsequently used by the Report class.
     *
     * \param name The (file)name without any file extension.
     * \return The plugin-specific report handle.
     * \sa Report::Report()
     */
    auto bactria_reports_create_report(char const* name) -> void*;

    /**
     * \brief Destroys a plugin-specific report handle.
     *
     * This function destroys a plugin-specific report handle. Accessing the handle after a call to this function
     * results in undefined behaviour.
     *
     * \param report_handle A plugin-specific report handle.
     * \sa Report::~Report()
     */
    auto bactria_reports_destroy_report(void* report_handle) noexcept -> void;

    /**
     * \brief Writes a report to disk (or other data sinks).
     *
     * This function saves a report to the plugin-specific data sink (a file, a database, ...).
     *
     * \param report_handle A plugin-specific report handle.
     * \sa IncidentRecorder::submit_report(), Report::submit()
     */
    auto bactria_reports_write_report(void* report_handle) -> void;

    /**
     * \brief Adds a boolean value to the report.
     *
     * Writes a boolean value to the report.
     *
     * \param report_handle A plugin-specific report handle.
     * \param key The identifier of the value.
     * \param value The value to be saved.
     * \sa IncidentRecorder::store()
     */
    auto bactria_reports_record_bool(void* report_handle, char const* key, bool value) -> void;

    /**
     * \brief Adds a `int8_t` value to the report.
     *
     * Writes a `int8_t` value to the report.
     *
     * \param report_handle A plugin-specific report handle.
     * \param key The identifier of the value.
     * \param value The value to be saved.
     * \sa IncidentRecorder::store()
     */
    auto bactria_reports_record_int8(void* report_handle, char const* key, std::int8_t value) -> void;

    /**
     * \brief Adds a `uint8_t` value to the report.
     *
     * Writes a `uint8_t` value to the report.
     *
     * \param report_handle A plugin-specific report handle.
     * \param key The identifier of the value.
     * \param value The value to be saved.
     * \sa IncidentRecorder::store()
     */
    auto bactria_reports_record_uint8(void* report_handle, char const* key, std::uint8_t value) -> void;

    /**
     * \brief Adds a `int16_t` value to the report.
     *
     * Writes a `int16_t` value to the report.
     *
     * \param report_handle A plugin-specific report handle.
     * \param key The identifier of the value.
     * \param value The value to be saved.
     * \sa IncidentRecorder::store()
     */
    auto bactria_reports_record_int16(void* report_handle, char const* key, std::int16_t value) -> void;

    /**
     * \brief Adds a `uint16_t` value to the report.
     *
     * Writes a `uint16_t` value to the report.
     *
     * \param report_handle A plugin-specific report handle.
     * \param key The identifier of the value.
     * \param value The value to be saved.
     * \sa IncidentRecorder::store()
     */
    auto bactria_reports_record_uint16(void* report_handle, char const* key, std::uint16_t value) -> void;

    /**
     * \brief Adds a `int32_t` value to the report.
     *
     * Writes a `int32_t` value to the report.
     *
     * \param report_handle A plugin-specific report handle.
     * \param key The identifier of the value.
     * \param value The value to be saved.
     * \sa IncidentRecorder::store()
     */
    auto bactria_reports_record_int32(void* report_handle, char const* key, std::int16_t value) -> void;

    /**
     * \brief Adds a `uint32_t` value to the report.
     *
     * Writes a `uint32_t` value to the report.
     *
     * \param report_handle A plugin-specific report handle.
     * \param key The identifier of the value.
     * \param value The value to be saved.
     * \sa IncidentRecorder::store()
     */
    auto bactria_reports_record_uint32(void* report_handle, char const* key, std::uint16_t value) -> void;

    /**
     * \brief Adds a `int64_t` value to the report.
     *
     * Writes a `int64_t` value to the report.
     *
     * \param report_handle A plugin-specific report handle.
     * \param key The identifier of the value.
     * \param value The value to be saved.
     * \sa IncidentRecorder::store()
     */
    auto bactria_reports_record_int64(void* report_handle, char const* key, std::int64_t value) -> void;

    /**
     * \brief Adds a `uint64_t` value to the report.
     *
     * Writes a `uint64_t` value to the report.
     *
     * \param report_handle A plugin-specific report handle.
     * \param key The identifier of the value.
     * \param value The value to be saved.
     * \sa IncidentRecorder::store()
     */
    auto bactria_reports_record_uint64(void* report_handle, char const* key, std::uint64_t value) -> void;

    /**
     * \brief Adds a `float` value to the report.
     *
     * Writes a `float` value to the report.
     *
     * \param report_handle A plugin-specific report handle.
     * \param key The identifier of the value.
     * \param value The value to be saved.
     * \sa IncidentRecorder::store()
     */
    auto bactria_reports_record_float(void* report_handle, char const* key, float value) -> void;

    /**
     * \brief Adds a `double` value to the report.
     *
     * Writes a `double` value to the report.
     *
     * \param report_handle A plugin-specific report handle.
     * \param key The identifier of the value.
     * \param value The value to be saved.
     * \sa IncidentRecorder::store()
     */
    auto bactria_reports_record_double(void* report_handle, char const* key, double value) -> void;

    /**
     * \brief Adds a string value to the report.
     *
     * Writes a string value to the report.
     *
     * \param report_handle A plugin-specific report handle.
     * \param key The identifier of the value.
     * \param value The value to be saved.
     * \sa IncidentRecorder::store()
     */
    auto bactria_reports_record_string(void* report_handle, char const* key, char const* value) -> void;
}

/** \} */