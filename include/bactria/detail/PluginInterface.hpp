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

#ifndef BACTRIA_DETAIL_PLUGIN_INTERFACE_HPP
#   define BACTRIA_DETAIL_PLUGIN_INTERFACE_HPP

#   include <cstdint>
#   include <type_traits>

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

            using fire_event_t = std::add_pointer_t<void(void*, char const*, char const*, std::uint32_t, char const*) noexcept>;
            auto fire_event_ptr = fire_event_t{nullptr};

            // Range
            using create_range_t = std::add_pointer_t<void*(char const*, std::uint32_t, char const*, std::uint32_t) noexcept>;
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
        }
    }
}

#endif
