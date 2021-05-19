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
    namespace reports
    {
        namespace plugin
        {
            inline auto activated() -> bool
            {
                static bool const activated = is_active() && (std::getenv("BACTRIA_REPORTS_PLUGIN") != nullptr);
                return activated;
            }

            /* Standard function pointer declaration style is forbidden because of noexcept */

            // Reports
            using create_report_t = std::add_pointer_t<void*(char const*)>;
            auto create_report_ptr = create_report_t{nullptr};

            using destroy_report_t = std::add_pointer_t<void(void*) noexcept>;
            auto destroy_report_ptr = destroy_report_t{nullptr};

            using write_report_t = std::add_pointer_t<void(void*)>;
            auto write_report_ptr = write_report_t{nullptr};

            using record_bool_t = std::add_pointer_t<void(void*, char const*, bool)>;
            auto record_bool_ptr = record_bool_t{nullptr};

            using record_int8_t = std::add_pointer_t<void(void*, char const*, std::int8_t)>;
            auto record_int8_ptr = record_int8_t{nullptr};

            using record_uint8_t = std::add_pointer_t<void(void*, char const*, std::uint8_t)>;
            auto record_uint8_ptr = record_uint8_t{nullptr};

            using record_int16_t = std::add_pointer_t<void(void*, char const*, std::int16_t)>;
            auto record_int16_ptr = record_int16_t{nullptr};

            using record_uint16_t = std::add_pointer_t<void(void*, char const*, std::uint16_t)>;
            auto record_uint16_ptr = record_uint16_t{nullptr};

            using record_int32_t = std::add_pointer_t<void(void*, char const*, std::int32_t)>;
            auto record_int32_ptr = record_int32_t{nullptr};

            using record_uint32_t = std::add_pointer_t<void(void*, char const*, std::uint32_t)>;
            auto record_uint32_ptr = record_uint32_t{nullptr};

            using record_int64_t = std::add_pointer_t<void(void*, char const*, std::int64_t)>;
            auto record_int64_ptr = record_int64_t{nullptr};

            using record_uint64_t = std::add_pointer_t<void(void*, char const*, std::uint64_t)>;
            auto record_uint64_ptr = record_uint64_t{nullptr};

            using record_float_t = std::add_pointer_t<void(void*, char const*, float)>;
            auto record_float_ptr = record_float_t{nullptr};

            using record_double_t = std::add_pointer_t<void(void*, char const*, double)>;
            auto record_double_ptr = record_double_t{nullptr};

            using record_string_t = std::add_pointer_t<void(void*, char const*, char const*)>;
            auto record_string_ptr = record_string_t{nullptr};

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

            [[gnu::always_inline]] inline auto create_report(char const* name)
            {
                if(create_report_ptr != nullptr)
                    return (create_report_ptr)(name);

                return static_cast<void*>(nullptr);
            }

            [[gnu::always_inline]] inline auto destroy_report(void* report_handle) noexcept
            {
                if(destroy_report_ptr != nullptr)
                    (destroy_report_ptr)(report_handle);
            }

            [[gnu::always_inline]] inline auto write_report(void* report_handle)
            {
                if(write_report_ptr != nullptr)
                    (write_report_ptr)(report_handle);
            }

            [[gnu::always_inline]] inline auto record_value(void* report_handle, char const* key, bool value) -> void
            {
                if(record_bool_ptr != nullptr)
                    (record_bool_ptr)(report_handle, key, value);
            }

            [[gnu::always_inline]] auto record_value(void* report_handle, char const* key, std::int8_t value) -> void
            {
                if(record_int8_ptr != nullptr)
                    (record_int8_ptr)(report_handle, key, value);
            }

            [[gnu::always_inline]] auto record_value(void* report_handle, char const* key, std::uint8_t value) -> void
            {
                if(record_uint8_ptr != nullptr)
                    (record_uint8_ptr)(report_handle, key, value);
            }

            [[gnu::always_inline]] auto record_value(void* report_handle, char const* key, std::int16_t value) -> void
            {
                if(record_int16_ptr != nullptr)
                    (record_int16_ptr)(report_handle, key, value);
            }

            [[gnu::always_inline]] auto record_value(void* report_handle, char const* key, std::uint16_t value) -> void
            {
                if(record_uint16_ptr != nullptr)
                    (record_uint16_ptr)(report_handle, key, value);
            }

            [[gnu::always_inline]] auto record_value(void* report_handle, char const* key, std::int32_t value) -> void
            {
                if(record_int32_ptr != nullptr)
                    (record_int32_ptr)(report_handle, key, value);
            }

            [[gnu::always_inline]] inline auto record_value(void* report_handle, char const* key, std::uint32_t value)
                -> void
            {
                if(record_uint32_ptr != nullptr)
                    (record_uint32_ptr)(report_handle, key, value);
            }

            [[gnu::always_inline]] inline auto record_value(void* report_handle, char const* key, std::int64_t value)
                -> void
            {
                if(record_int64_ptr != nullptr)
                    (record_int64_ptr)(report_handle, key, value);
            }

            [[gnu::always_inline]] inline auto record_value(void* report_handle, char const* key, std::uint64_t value)
                -> void
            {
                if(record_uint64_ptr != nullptr)
                    (record_uint64_ptr)(report_handle, key, value);
            }

            [[gnu::always_inline]] inline auto record_value(void* report_handle, char const* key, float value) -> void
            {
                if(record_float_ptr != nullptr)
                    (record_float_ptr)(report_handle, key, value);
            }

            [[gnu::always_inline]] inline auto record_value(void* report_handle, char const* key, double value) -> void
            {
                if(record_double_ptr != nullptr)
                    (record_double_ptr)(report_handle, key, value);
            }

            [[gnu::always_inline]] inline auto record_value(void* report_handle, char const* key, char const* value)
                -> void
            {
                if(record_string_ptr != nullptr)
                    (record_string_ptr)(report_handle, key, value);
            }
        } // namespace plugin
    } // namespace reports
} // namespace bactria
