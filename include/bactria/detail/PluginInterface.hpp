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

#include <cstdint>
#include <type_traits>

namespace bactria
{
    namespace plugin
    {
        namespace detail
        {
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

            // Sector
            using create_sector_t = std::add_pointer_t<void*(char const*, std::uint32_t) noexcept>;
            auto create_sector_ptr = create_sector_t{nullptr};

            using destroy_sector_t = std::add_pointer_t<void(void*) noexcept>;
            auto destroy_sector_ptr = destroy_sector_t{nullptr};

            using enter_sector_t = std::add_pointer_t<void(void*, char const*, std::uint32_t, char const*) noexcept>;
            auto enter_sector_ptr = enter_sector_t{nullptr};

            using leave_sector_t = std::add_pointer_t<void(void*, char const*, std::uint32_t, char const*) noexcept>;
            auto leave_sector_ptr = leave_sector_t{nullptr};

            using sector_summary_t = std::add_pointer_t<void(void*) noexcept>;
            auto sector_summary_ptr = sector_summary_t{nullptr};

            // Phase
            using create_phase_t = std::add_pointer_t<void*(char const*) noexcept>;
            auto create_phase_ptr = create_phase_t{nullptr};

            using destroy_phase_t = std::add_pointer_t<void(void*) noexcept>;
            auto destroy_phase_ptr = destroy_phase_t{nullptr};

            using enter_phase_t = std::add_pointer_t<void(void*, char const*, std::uint32_t, char const*) noexcept>;
            auto enter_phase_ptr = enter_phase_t{nullptr};

            using leave_phase_t = std::add_pointer_t<void(void*, char const*, std::uint32_t, char const*) noexcept>;
            auto leave_phase_ptr = leave_phase_t{nullptr};

            // Reports
            using report_create_report_t = std::add_pointer_t<void*(char const*)>;
            auto report_create_report_ptr = report_create_report_t{nullptr};

            using report_destroy_report_t = std::add_pointer_t<void(void*) noexcept>;
            auto report_destroy_report_ptr = report_destroy_report_t{nullptr};

            using report_write_report_t = std::add_pointer_t<void(void*)>;
            auto report_write_report_ptr = report_write_report_t{nullptr};

            using report_record_bool_t = std::add_pointer_t<void(void*, char const*, bool)>;
            auto report_record_bool_ptr = report_record_bool_t{nullptr};

            using report_record_int8_t = std::add_pointer_t<void(void*, char const*, std::int8_t)>;
            auto report_record_int8_ptr = report_record_int8_t{nullptr};

            using report_record_uint8_t = std::add_pointer_t<void(void*, char const*, std::uint8_t)>;
            auto report_record_uint8_ptr = report_record_uint8_t{nullptr};

            using report_record_int16_t = std::add_pointer_t<void(void*, char const*, std::int16_t)>;
            auto report_record_int16_ptr = report_record_int16_t{nullptr};

            using report_record_uint16_t = std::add_pointer_t<void(void*, char const*, std::uint16_t)>;
            auto report_record_uint16_ptr = report_record_uint16_t{nullptr};

            using report_record_int32_t = std::add_pointer_t<void(void*, char const*, std::int32_t)>;
            auto report_record_int32_ptr = report_record_int32_t{nullptr};

            using report_record_uint32_t = std::add_pointer_t<void(void*, char const*, std::uint32_t)>;
            auto report_record_uint32_ptr = report_record_uint32_t{nullptr};

            using report_record_int64_t = std::add_pointer_t<void(void*, char const*, std::int64_t)>;
            auto report_record_int64_ptr = report_record_int64_t{nullptr};

            using report_record_uint64_t = std::add_pointer_t<void(void*, char const*, std::uint64_t)>;
            auto report_record_uint64_ptr = report_record_uint64_t{nullptr};

            using report_record_float_t = std::add_pointer_t<void(void*, char const*, float)>;
            auto report_record_float_ptr = report_record_float_t{nullptr};

            using report_record_double_t = std::add_pointer_t<void(void*, char const*, double)>;
            auto report_record_double_ptr = report_record_double_t{nullptr};

            using report_record_string_t = std::add_pointer_t<void(void*, char const*, char const*)>;
            auto report_record_string_ptr = report_record_string_t{nullptr};
        } // namespace detail
    } // namespace plugin
} // namespace bactria
