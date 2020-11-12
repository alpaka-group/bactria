/* Copyright 2020 Jan Stephan
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
#define BACTRIA_DETAIL_PLUGIN_INTERFACE_HPP

namespace bactria::plugin::detail
{
    using create_region_t = void* (*)(const char*) noexcept;
    auto create_region_ptr = create_region_t{nullptr};

    using destroy_region_t = void (*)(void*) noexcept;
    auto destroy_region_ptr = destroy_region_t{nullptr};

    using create_phase_t = void* (*)(const char*) noexcept;
    auto create_phase_ptr = create_phase_t{nullptr};

    using destroy_phase_t = void (*)(void*) noexcept;
    auto destroy_phase_ptr = destroy_phase_t{nullptr};

    using create_event_t = void* (*)(const char*) noexcept;
    auto create_event_ptr = create_event_t{nullptr};

    using destroy_event_t = void (*)(void*) noexcept;
    auto destroy_event_ptr = destroy_event_t{nullptr};

    using assign_region_phase_t = void (*)(void*, void*) noexcept;
    auto assign_region_phase_ptr = assign_region_phase_t{nullptr};

    using start_recording_t = void (*)(void*) noexcept;
    auto start_recording_ptr = start_recording_t{nullptr};

    using stop_recording_t = void (*)(void*) noexcept;
    auto stop_recording_ptr = stop_recording_t{nullptr};

    using record_event_t = void (*)(void*, void*) noexcept;
    auto record_event_ptr = record_event_t{nullptr};
}

#endif
