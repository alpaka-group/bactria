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
 * \brief Library-facing plugin interface.
 *
 * This file includes the library's view of the plugin functionality. This should never be included by the user. As
 * the functionality defined here is intended for bactria's internal use the user should never use anything found
 * in this file.
 */

#pragma once

#include <bactria/detail/POSIX.hpp>
#include <bactria/detail/PluginInterface.hpp>
#include <bactria/detail/Win32.hpp>

#include <iostream>

namespace bactria
{
    namespace plugin
    {
        using plugin_handle_t = detail::plugin_handle_t;

        [[nodiscard]] inline auto load_plugin() -> plugin_handle_t
        {
            auto const path = std::getenv("BACTRIA_PLUGIN");
            if(path != nullptr)
            {
                auto handle = detail::open_plugin(path);

                detail::load_func(handle, detail::create_event_ptr, "bactria_plugin_create_event");
                detail::load_func(handle, detail::destroy_event_ptr, "bactria_plugin_destroy_event");
                detail::load_func(handle, detail::fire_event_ptr, "bactria_plugin_fire_event");

                detail::load_func(handle, detail::create_range_ptr, "bactria_plugin_create_range");
                detail::load_func(handle, detail::destroy_range_ptr, "bactria_plugin_destroy_range");
                detail::load_func(handle, detail::start_range_ptr, "bactria_plugin_start_range");
                detail::load_func(handle, detail::stop_range_ptr, "bactria_plugin_stop_range");

                detail::load_func(handle, detail::create_sector_ptr, "bactria_plugin_create_sector");
                detail::load_func(handle, detail::destroy_sector_ptr, "bactria_plugin_destroy_sector");
                detail::load_func(handle, detail::enter_sector_ptr, "bactria_plugin_enter_sector");
                detail::load_func(handle, detail::leave_sector_ptr, "bactria_plugin_leave_sector");
                detail::load_func(handle, detail::sector_summary_ptr, "bactria_plugin_sector_summary");

                detail::load_func(handle, detail::create_phase_ptr, "bactria_plugin_create_phase");
                detail::load_func(handle, detail::destroy_phase_ptr, "bactria_plugin_destroy_phase");
                detail::load_func(handle, detail::enter_phase_ptr, "bactria_plugin_enter_phase");
                detail::load_func(handle, detail::leave_phase_ptr, "bactria_plugin_leave_phase");

                return handle;
            }

            // getenv failed
            std::cerr << "BACTRIA_PLUGIN not specified. Plugin functionality deactivated." << std::endl;
            return plugin_handle_t{};
        }

        [[nodiscard]] auto load_report_plugin() -> plugin_handle_t
        {
            auto const path = std::getenv("BACTRIA_REPORT_PLUGIN");
            if(path != nullptr)
            {
                auto handle = detail::open_plugin(path);

                detail::load_func(handle, detail::report_create_report_ptr, "bactria_report_plugin_create_report");
                detail::load_func(handle, detail::report_destroy_report_ptr, "bactria_report_plugin_destroy_report");
                detail::load_func(handle, detail::report_write_report_ptr, "bactria_report_plugin_write_report");
                detail::load_func(
                    handle,
                    detail::report_record_bool_ptr,
                    "bactria_report_plugin_record_incident_bool");
                detail::load_func(
                    handle,
                    detail::report_record_int8_ptr,
                    "bactria_report_plugin_record_incident_int8");
                detail::load_func(
                    handle,
                    detail::report_record_uint8_ptr,
                    "bactria_report_plugin_record_incident_uint8");
                detail::load_func(
                    handle,
                    detail::report_record_int16_ptr,
                    "bactria_report_plugin_record_incident_int16");
                detail::load_func(
                    handle,
                    detail::report_record_uint16_ptr,
                    "bactria_report_plugin_record_incident_uint16");
                detail::load_func(
                    handle,
                    detail::report_record_int32_ptr,
                    "bactria_report_plugin_record_incident_int32");
                detail::load_func(
                    handle,
                    detail::report_record_uint32_ptr,
                    "bactria_report_plugin_record_incident_uint32");
                detail::load_func(
                    handle,
                    detail::report_record_int64_ptr,
                    "bactria_report_plugin_record_incident_int64");
                detail::load_func(
                    handle,
                    detail::report_record_uint64_ptr,
                    "bactria_report_plugin_record_incident_uint64");
                detail::load_func(
                    handle,
                    detail::report_record_float_ptr,
                    "bactria_report_plugin_record_incident_float");
                detail::load_func(
                    handle,
                    detail::report_record_double_ptr,
                    "bactria_report_plugin_record_incident_double");
                detail::load_func(
                    handle,
                    detail::report_record_string_ptr,
                    "bactria_report_plugin_record_incident_string");

                return handle;
            }

            // getenv failed
            std::cerr << "BACTRIA_REPORT_PLUGIN not specified. Report functionality deactivated." << std::endl;
            return plugin_handle_t{};
        }

        auto unload_plugin(plugin_handle_t handle) noexcept
        {
            detail::close_plugin(handle);
        }

        [[nodiscard, gnu::always_inline]] inline auto create_event(
            std::uint32_t color,
            char const* cat_name,
            std::uint32_t cat_id) noexcept
        {
            if(detail::create_event_ptr != nullptr)
                return (detail::create_event_ptr)(color, cat_name, cat_id);

            return static_cast<void*>(nullptr);
        }

        [[gnu::always_inline]] inline auto destroy_event(void* event_handle) noexcept
        {
            if(detail::destroy_event_ptr != nullptr)
                (detail::destroy_event_ptr)(event_handle);
        }

        [[gnu::always_inline]] inline auto fire_event(
            void* event_handle,
            char const* event_name,
            char const* source,
            std::uint32_t lineno,
            char const* caller) noexcept
        {
            if(detail::fire_event_ptr != nullptr)
                (detail::fire_event_ptr)(event_handle, event_name, source, lineno, caller);
        }

        [[nodiscard, gnu::always_inline]] inline auto create_range(
            char const* name,
            std::uint32_t color,
            char const* cat_name,
            std::uint32_t cat_id) noexcept
        {
            if(detail::create_range_ptr != nullptr)
                return (detail::create_range_ptr)(name, color, cat_name, cat_id);

            return static_cast<void*>(nullptr);
        }

        [[gnu::always_inline]] inline auto destroy_range(void* range_handle) noexcept
        {
            if(detail::destroy_range_ptr != nullptr)
                (detail::destroy_range_ptr)(range_handle);
        }

        [[gnu::always_inline]] inline auto start_range(void* range_handle) noexcept
        {
            if(detail::start_range_ptr != nullptr)
                (detail::start_range_ptr)(range_handle);
        }

        [[gnu::always_inline]] inline auto stop_range(void* range_handle) noexcept
        {
            if(detail::stop_range_ptr != nullptr)
                (detail::stop_range_ptr)(range_handle);
        }

        [[nodiscard, gnu::always_inline]] inline auto create_sector(char const* name, std::uint32_t tag) noexcept
        {
            if(detail::create_sector_ptr != nullptr)
                return (detail::create_sector_ptr)(name, tag);

            return static_cast<void*>(nullptr);
        }

        [[gnu::always_inline]] inline auto destroy_sector(void* sector_handle) noexcept
        {
            if(detail::destroy_sector_ptr != nullptr)
                (detail::destroy_sector_ptr)(sector_handle);
        }

        [[gnu::always_inline]] inline auto enter_sector(
            void* sector_handle,
            char const* source,
            std::uint32_t lineno,
            char const* caller) noexcept
        {
            if(detail::enter_sector_ptr != nullptr)
                (detail::enter_sector_ptr)(sector_handle, source, lineno, caller);
        }

        [[gnu::always_inline]] inline auto leave_sector(
            void* sector_handle,
            char const* source,
            std::uint32_t lineno,
            char const* caller) noexcept
        {
            if(detail::leave_sector_ptr != nullptr)
                (detail::leave_sector_ptr)(sector_handle, source, lineno, caller);
        }

        [[gnu::always_inline]] inline auto sector_summary(void* sector_handle) noexcept
        {
            if(detail::sector_summary_ptr != nullptr)
                (detail::sector_summary_ptr)(sector_handle);
        }

        [[nodiscard, gnu::always_inline]] inline auto create_phase(char const* name) noexcept
        {
            if(detail::create_phase_ptr != nullptr)
                return (detail::create_phase_ptr)(name);

            return static_cast<void*>(nullptr);
        }

        [[gnu::always_inline]] inline auto destroy_phase(void* phase_handle) noexcept
        {
            if(detail::destroy_range_ptr != nullptr)
                (detail::destroy_phase_ptr)(phase_handle);
        }

        [[gnu::always_inline]] inline auto enter_phase(
            void* phase_handle,
            char const* source,
            std::uint32_t lineno,
            char const* caller) noexcept
        {
            if(detail::enter_phase_ptr != nullptr)
                (detail::enter_phase_ptr)(phase_handle, source, lineno, caller);
        }

        [[gnu::always_inline]] inline auto leave_phase(
            void* phase_handle,
            char const* source,
            std::uint32_t lineno,
            char const* caller) noexcept
        {
            if(detail::leave_phase_ptr != nullptr)
                (detail::leave_phase_ptr)(phase_handle, source, lineno, caller);
        }

        [[gnu::always_inline]] auto create_report(char const* name)
        {
            if(detail::report_create_report_ptr != nullptr)
                return (detail::report_create_report_ptr)(name);

            return static_cast<void*>(nullptr);
        }

        [[gnu::always_inline]] auto destroy_report(void* report_handle) noexcept
        {
            if(detail::report_destroy_report_ptr != nullptr)
                (detail::report_destroy_report_ptr)(report_handle);
        }

        [[gnu::always_inline]] auto write_report(void* report_handle)
        {
            if(detail::report_write_report_ptr != nullptr)
                (detail::report_write_report_ptr)(report_handle);
        }

        [[gnu::always_inline]] auto record_value(void* report_handle, char const* key, bool value) -> void
        {
            if(detail::report_record_bool_ptr != nullptr)
                (detail::report_record_bool_ptr)(report_handle, key, value);
        }

        [[gnu::always_inline]] auto record_value(void* report_handle, char const* key, std::int8_t value) -> void
        {
            if(detail::report_record_int8_ptr != nullptr)
                (detail::report_record_int8_ptr)(report_handle, key, value);
        }

        [[gnu::always_inline]] auto record_value(void* report_handle, char const* key, std::uint8_t value) -> void
        {
            if(detail::report_record_uint8_ptr != nullptr)
                (detail::report_record_uint8_ptr)(report_handle, key, value);
        }

        [[gnu::always_inline]] auto record_value(void* report_handle, char const* key, std::int16_t value) -> void
        {
            if(detail::report_record_int16_ptr != nullptr)
                (detail::report_record_int16_ptr)(report_handle, key, value);
        }

        [[gnu::always_inline]] auto record_value(void* report_handle, char const* key, std::uint16_t value) -> void
        {
            if(detail::report_record_uint16_ptr != nullptr)
                (detail::report_record_uint16_ptr)(report_handle, key, value);
        }

        [[gnu::always_inline]] auto record_value(void* report_handle, char const* key, std::int32_t value) -> void
        {
            if(detail::report_record_int32_ptr != nullptr)
                (detail::report_record_int32_ptr)(report_handle, key, value);
        }

        [[gnu::always_inline]] auto record_value(void* report_handle, char const* key, std::uint32_t value) -> void
        {
            if(detail::report_record_uint32_ptr != nullptr)
                (detail::report_record_uint32_ptr)(report_handle, key, value);
        }

        [[gnu::always_inline]] auto record_value(void* report_handle, char const* key, std::int64_t value) -> void
        {
            if(detail::report_record_int64_ptr != nullptr)
                (detail::report_record_int64_ptr)(report_handle, key, value);
        }

        [[gnu::always_inline]] auto record_value(void* report_handle, char const* key, std::uint64_t value) -> void
        {
            if(detail::report_record_uint64_ptr != nullptr)
                (detail::report_record_uint64_ptr)(report_handle, key, value);
        }

        [[gnu::always_inline]] auto record_value(void* report_handle, char const* key, float value) -> void
        {
            if(detail::report_record_float_ptr != nullptr)
                (detail::report_record_float_ptr)(report_handle, key, value);
        }

        [[gnu::always_inline]] auto record_value(void* report_handle, char const* key, double value) -> void
        {
            if(detail::report_record_double_ptr != nullptr)
                (detail::report_record_double_ptr)(report_handle, key, value);
        }

        [[gnu::always_inline]] auto record_value(void* report_handle, char const* key, char const* value) -> void
        {
            if(detail::report_record_string_ptr != nullptr)
                (detail::report_record_string_ptr)(report_handle, key, value);
        }
    } // namespace plugin
} // namespace bactria
