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
 * \brief bactria-internal handling of reports plugins.
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
    namespace reports
    {
        /**
         * \defgroup bactria_reports Reports functionality
         *
         * bactria's reports part. This provides functionality for recording user-defined metrics.
         */

        namespace plugin
        {
            /**
             * \defgroup bactria_reports_internal Internal documentation. Not intended or useful for the user.
             * \ingroup bactria_reports
             * \{
             */

            /**
             * \brief Checks for an active reports plugin.
             *
             * This function checks for an active reports plugin.
             *
             * \return true If `BACTRIA_DEACTIVATE` is NOT defined and `BACTRIA_REPORTS_PLUGIN` is defined.
             * \return false If either `BACTRIA_DEACTIVATE` is defined or `BACTRIA_REPORTS_PLUGIN` is NOT defined.
             */
            inline auto activated() -> bool
            {
                static bool const activated = is_active() && (std::getenv("BACTRIA_REPORTS_PLUGIN") != nullptr);
                return activated;
            }

            /* Standard function pointer declaration style is forbidden because of noexcept */
            /**ange
             * \brief Signature for plugin function bactria_reports_create_report().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            using create_report_t = std::add_pointer_t<void*(char const*)>;

            /**
             * \brief Pointer to plugin function bactria_reports_create_report().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            auto create_report_ptr = create_report_t{nullptr};

            /**
             * \brief Signature for plugin function bactria_reports_destroy_report().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            using destroy_report_t = std::add_pointer_t<void(void*) noexcept>;

            /**
             * \brief Pointer to plugin function bactria_reports_destroy_report().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            auto destroy_report_ptr = destroy_report_t{nullptr};

            /**
             * \brief Signature for plugin function bactria_reports_write_report().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            using write_report_t = std::add_pointer_t<void(void*)>;

            /**
             * \brief Pointer to plugin function bactria_reports_write_report().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            auto write_report_ptr = write_report_t{nullptr};

            /**
             * \brief Signature for plugin function bactria_reports_record_bool().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            using record_bool_t = std::add_pointer_t<void(void*, char const*, bool)>;

            /**
             * \brief Pointer to plugin function bactria_reports_record_bool().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            auto record_bool_ptr = record_bool_t{nullptr};

            /**
             * \brief Signature for plugin function bactria_reports_record_int8().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            using record_int8_t = std::add_pointer_t<void(void*, char const*, std::int8_t)>;

            /**
             * \brief Pointer to plugin function bactria_reports_record_int8().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            auto record_int8_ptr = record_int8_t{nullptr};

            /**
             * \brief Signature for plugin function bactria_reports_record_uint8().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            using record_uint8_t = std::add_pointer_t<void(void*, char const*, std::uint8_t)>;

            /**
             * \brief Pointer to plugin function bactria_reports_record_uint8().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            auto record_uint8_ptr = record_uint8_t{nullptr};

            /**
             * \brief Signature for plugin function bactria_reports_record_int16().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            using record_int16_t = std::add_pointer_t<void(void*, char const*, std::int16_t)>;

            /**
             * \brief Pointer to plugin function bactria_reports_record_int16().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            auto record_int16_ptr = record_int16_t{nullptr};

            /**
             * \brief Signature for plugin function bactria_reports_record_uint16().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            using record_uint16_t = std::add_pointer_t<void(void*, char const*, std::uint16_t)>;

            /**
             * \brief Pointer to plugin function bactria_reports_record_uint16().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            auto record_uint16_ptr = record_uint16_t{nullptr};

            /**
             * \brief Signature for plugin function bactria_reports_record_int32().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            using record_int32_t = std::add_pointer_t<void(void*, char const*, std::int32_t)>;

            /**
             * \brief Pointer to plugin function bactria_reports_record_int32().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            auto record_int32_ptr = record_int32_t{nullptr};

            /**
             * \brief Signature for plugin function bactria_reports_record_uint32().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            using record_uint32_t = std::add_pointer_t<void(void*, char const*, std::uint32_t)>;

            /**
             * \brief Pointer to plugin function bactria_reports_record_uint32().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            auto record_uint32_ptr = record_uint32_t{nullptr};

            /**
             * \brief Signature for plugin function bactria_reports_record_int64().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            using record_int64_t = std::add_pointer_t<void(void*, char const*, std::int64_t)>;

            /**
             * \brief Pointer to plugin function bactria_reports_record_int64().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            auto record_int64_ptr = record_int64_t{nullptr};

            /**
             * \brief Signature for plugin function bactria_reports_record_uint64().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            using record_uint64_t = std::add_pointer_t<void(void*, char const*, std::uint64_t)>;

            /**
             * \brief Pointer to plugin function bactria_reports_record_uint64().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            auto record_uint64_ptr = record_uint64_t{nullptr};

            /**
             * \brief Signature for plugin function bactria_reports_record_float().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            using record_float_t = std::add_pointer_t<void(void*, char const*, float)>;

            /**
             * \brief Pointer to plugin function bactria_reports_record_float().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            auto record_float_ptr = record_float_t{nullptr};

            /**
             * \brief Signature for plugin function bactria_reports_record_double().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            using record_double_t = std::add_pointer_t<void(void*, char const*, double)>;

            /**
             * \brief Pointer to plugin function bactria_reports_record_double().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            auto record_double_ptr = record_double_t{nullptr};

            /**
             * \brief Signature for plugin function bactria_reports_record_string().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            using record_string_t = std::add_pointer_t<void(void*, char const*, char const*)>;

            /**
             * \brief Pointer to plugin function bactria_reports_record_string().
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             */
            auto record_string_ptr = record_string_t{nullptr};

            /**
             * \brief Initializes the reports plugin.
             *
             * Used internally by bactria during plugin initialization. Should never be used by the user.
             *
             * \return A platform-specific plugin handle.
             * \throws std::runtime_error On failure during plugin initialization.
             */
            [[nodiscard]] inline auto load() -> plugin_handle_t
            {
                auto const path = std::getenv("BACTRIA_REPORTS_PLUGIN");
                if(path != nullptr)
                {
                    auto handle = system::open_plugin(path);

                    system::load_func(handle, create_report_ptr, "bactria_reports_create_report");
                    system::load_func(handle, destroy_report_ptr, "bactria_reports_destroy_report");
                    system::load_func(handle, write_report_ptr, "bactria_reports_write_report");
                    system::load_func(handle, record_bool_ptr, "bactria_reports_record_bool");
                    system::load_func(handle, record_int8_ptr, "bactria_reports_record_int8");
                    system::load_func(handle, record_uint8_ptr, "bactria_reports_record_uint8");
                    system::load_func(handle, record_int16_ptr, "bactria_reports_record_int16");
                    system::load_func(handle, record_uint16_ptr, "bactria_reports_record_uint16");
                    system::load_func(handle, record_int32_ptr, "bactria_reports_record_int32");
                    system::load_func(handle, record_uint32_ptr, "bactria_reports_record_uint32");
                    system::load_func(handle, record_int64_ptr, "bactria_reports_record_int64");
                    system::load_func(handle, record_uint64_ptr, "bactria_reports_record_uint64");
                    system::load_func(handle, record_float_ptr, "bactria_reports_record_float");
                    system::load_func(handle, record_double_ptr, "bactria_reports_record_double");
                    system::load_func(handle, record_string_ptr, "bactria_reports_record_string");

                    return handle;
                }

                // getenv failed
                throw std::runtime_error{std::string{"Failed to load bactria reports plugin "} + path};
            }

            /**
             * \brief Creates a plugin-specific report handle.
             *
             * Used internally by the Report class. Should never be used directly.
             *
             * \return A plugin-specific report handle.
             * \sa Report::Report()
             */
            [[gnu::always_inline]] inline auto create_report(char const* name)
            {
                if(create_report_ptr != nullptr)
                    return (create_report_ptr) (name);

                return static_cast<void*>(nullptr);
            }

            /**
             * \brief Destroys a plugin-specific report handle.
             *
             * Used internally by the Report class. Should never be used directly.
             *
             * \sa Report::~Report()
             */
            [[gnu::always_inline]] inline auto destroy_report(void* report_handle) noexcept
            {
                if(destroy_report_ptr != nullptr)
                    (destroy_report_ptr)(report_handle);
            }

            /**
             * \brief Plugin-specific report writing.
             *
             * Used internally by the Report class. Should never be used directly.
             *
             * \sa Report::submit()
             */
            [[gnu::always_inline]] inline auto write_report(void* report_handle)
            {
                if(write_report_ptr != nullptr)
                    (write_report_ptr)(report_handle);
            }

            /**
             * \brief Plugin-specific boolean recording.
             *
             * Used internally by the IncidentRecorder class. Should never be used directly.
             *
             * \sa IncidentRecorder::store()
             */
            [[gnu::always_inline]] inline auto record_value(void* report_handle, char const* key, bool value) -> void
            {
                if(record_bool_ptr != nullptr)
                    (record_bool_ptr)(report_handle, key, value);
            }

            /**
             * \brief Plugin-specific int8_t recording.
             *
             * Used internally by the IncidentRecorder class. Should never be used directly.
             *
             * \sa IncidentRecorder::store()
             */
            [[gnu::always_inline]] auto record_value(void* report_handle, char const* key, std::int8_t value) -> void
            {
                if(record_int8_ptr != nullptr)
                    (record_int8_ptr)(report_handle, key, value);
            }

            /**
             * \brief Plugin-specific uint8_t recording.
             *
             * Used internally by the IncidentRecorder class. Should never be used directly.
             *
             * \sa IncidentRecorder::store()
             */
            [[gnu::always_inline]] auto record_value(void* report_handle, char const* key, std::uint8_t value) -> void
            {
                if(record_uint8_ptr != nullptr)
                    (record_uint8_ptr)(report_handle, key, value);
            }

            /**
             * \brief Plugin-specific int16_t recording.
             *
             * Used internally by the IncidentRecorder class. Should never be used directly.
             *
             * \sa IncidentRecorder::store()
             */
            [[gnu::always_inline]] auto record_value(void* report_handle, char const* key, std::int16_t value) -> void
            {
                if(record_int16_ptr != nullptr)
                    (record_int16_ptr)(report_handle, key, value);
            }

            /**
             * \brief Plugin-specific uint16_t recording.
             *
             * Used internally by the IncidentRecorder class. Should never be used directly.
             *
             * \sa IncidentRecorder::store()
             */
            [[gnu::always_inline]] auto record_value(void* report_handle, char const* key, std::uint16_t value) -> void
            {
                if(record_uint16_ptr != nullptr)
                    (record_uint16_ptr)(report_handle, key, value);
            }

            /**
             * \brief Plugin-specific int32_t recording.
             *
             * Used internally by the IncidentRecorder class. Should never be used directly.
             *
             * \sa IncidentRecorder::store()
             */
            [[gnu::always_inline]] auto record_value(void* report_handle, char const* key, std::int32_t value) -> void
            {
                if(record_int32_ptr != nullptr)
                    (record_int32_ptr)(report_handle, key, value);
            }

            /**
             * \brief Plugin-specific uint32_t recording.
             *
             * Used internally by the IncidentRecorder class. Should never be used directly.
             *
             * \sa IncidentRecorder::store()
             */
            [[gnu::always_inline]] inline auto record_value(void* report_handle, char const* key, std::uint32_t value)
                -> void
            {
                if(record_uint32_ptr != nullptr)
                    (record_uint32_ptr)(report_handle, key, value);
            }

            /**
             * \brief Plugin-specific int64_t recording.
             *
             * Used internally by the IncidentRecorder class. Should never be used directly.
             *
             * \sa IncidentRecorder::store()
             */
            [[gnu::always_inline]] inline auto record_value(void* report_handle, char const* key, std::int64_t value)
                -> void
            {
                if(record_int64_ptr != nullptr)
                    (record_int64_ptr)(report_handle, key, value);
            }

            /**
             * \brief Plugin-specific uint64_t recording.
             *
             * Used internally by the IncidentRecorder class. Should never be used directly.
             *
             * \sa IncidentRecorder::store()
             */
            [[gnu::always_inline]] inline auto record_value(void* report_handle, char const* key, std::uint64_t value)
                -> void
            {
                if(record_uint64_ptr != nullptr)
                    (record_uint64_ptr)(report_handle, key, value);
            }

            /**
             * \brief Plugin-specific float recording.
             *
             * Used internally by the IncidentRecorder class. Should never be used directly.
             *
             * \sa IncidentRecorder::store()
             */
            [[gnu::always_inline]] inline auto record_value(void* report_handle, char const* key, float value) -> void
            {
                if(record_float_ptr != nullptr)
                    (record_float_ptr)(report_handle, key, value);
            }

            /**
             * \brief Plugin-specific double recording.
             *
             * Used internally by the IncidentRecorder class. Should never be used directly.
             *
             * \sa IncidentRecorder::store()
             */
            [[gnu::always_inline]] inline auto record_value(void* report_handle, char const* key, double value) -> void
            {
                if(record_double_ptr != nullptr)
                    (record_double_ptr)(report_handle, key, value);
            }

            /**
             * \brief Plugin-specific string recording.
             *
             * Used internally by the IncidentRecorder class. Should never be used directly.
             *
             * \sa IncidentRecorder::store()
             */
            [[gnu::always_inline]] inline auto record_value(void* report_handle, char const* key, char const* value)
                -> void
            {
                if(record_string_ptr != nullptr)
                    (record_string_ptr)(report_handle, key, value);
            }
            /** \} */
        } // namespace plugin
    } // namespace reports
} // namespace bactria
