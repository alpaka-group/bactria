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

#include <iostream>

#include <bactria/plugin.hpp>

namespace bactria::plugin::printf
{
    struct phase
    {
        const char* name;
    };

    struct region
    {
        const char* name;
        phase* p;
    };

    struct event
    {
        const char* name;
    };
}

extern "C"
{
    [[clang::acquire_handle("bactria region")]]
    auto bactria_plugin_create_region(const char* name) noexcept -> void*
    {
        return new bactria::plugin::printf::region{name, nullptr};
    }

    auto bactria_plugin_destroy_region(void* region_handle [[clang::release_handle("bactria region")]]) noexcept -> void
    {
        auto region = static_cast<bactria::plugin::printf::region*>(region_handle);
        delete region;
    }

    [[clang::acquire_handle("bactria phase")]]
    auto bactria_plugin_create_phase(const char* name) noexcept -> void*
    {
        return new bactria::plugin::printf::phase{name};
    }
    
    auto bactria_plugin_destroy_phase(void* phase_handle [[clang::release_handle("bactria phase")]]) noexcept -> void
    {
        auto phase = static_cast<bactria::plugin::printf::phase*>(phase_handle);
        delete phase;
    }

    [[clang::acquire_handle("bactria event")]]
    auto bactria_plugin_create_event(const char* name) noexcept -> void*
    {
        return new bactria::plugin::printf::event{name};
    }
    
    auto bactria_plugin_destroy_event(void* event_handle [[clang::release_handle("bactria event")]]) noexcept -> void
    {
        auto event = static_cast<bactria::plugin::printf::event*>(event_handle);
        delete event;
    }

    auto bactria_plugin_assign_region_phase(void* region_handle [[clang::use_handle("bactria region")]],
                                            void* phase_handle [[clang::use_handle("bactria phase")]]) noexcept -> void
    {
        auto region = static_cast<bactria::plugin::printf::region*>(region_handle);
        auto phase = static_cast<bactria::plugin::printf::phase*>(phase_handle);

        region->p = phase;
    }

    auto bactria_plugin_start_recording(void* region_handle [[clang::use_handle("bactria region")]]) noexcept -> void
    {
        const auto region = static_cast<bactria::plugin::printf::region*>(region_handle);
        std::cout << "Entering region " << region->name << '\n';
    }

    auto bactria_plugin_stop_recording(void* region_handle [[clang::use_handle("bactria region")]]) noexcept-> void
    {
        const auto region = static_cast<bactria::plugin::printf::region*>(region_handle);
        std::cout << "Leaving region " << region->name << '\n';
    }

    auto bactria_plugin_record_event(void* region_handle [[clang::use_handle("bactria region")]],
                                     void* event_handle [[clang::use_handle("bactria event")]]) noexcept -> void
    {
        const auto region = static_cast<bactria::plugin::printf::region*>(region_handle);
        const auto event = static_cast<bactria::plugin::printf::event*>(event_handle);

        std::cout << "Recording event " << event->name << " in region " << region->name << '\n';
    }
}
