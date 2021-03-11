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

#ifndef BACTRIA_PLUGIN_INTERFACE_HPP
#   define BACTRIA_PLUGIN_INTERFACE_HPP

#   include <cstdint>

extern "C"
{
    [[nodiscard, clang::acquire_handle("bactria event")]]
    auto bactria_plugin_create_event(const char* name, std::uint32_t color, std::uint32_t category) noexcept -> void*;
    auto bactria_plugin_destroy_event(void* event_handle [[clang::release_handle("bactria event")]]) noexcept -> void;
    auto bactria_plugin_fire_event(void* event_handle [[clang::use_handle("bactria event")]]) noexcept -> void;

    [[nodiscard, clang::acquire_handle("bactria range")]]
    auto bactria_plugin_create_range(const char* name, std::uint32_t color, std::uint32_t category) noexcept -> void*; 
    auto bactria_plugin_destroy_range(void* range_handle [[clang::release_handle("bactria range")]]) noexcept -> void;
    auto bactria_plugin_start_range(void* range_handle [[clang::use_handle("bactria range")]]) noexcept -> void;
    auto bactria_plugin_stop_range(void* range_handle [[clang::use_handle("bactria range")]]) noexcept -> void;

    [[nodiscard, clang::acquire_handle("bactria sector")]]
    auto bactria_plugin_create_sector(const char* name, std::uint32_t type) noexcept -> void*;
    auto bactria_plugin_destroy_sector(void* sector_handle [[clang::release_handle("bactria sector")]]) noexcept -> void;
    auto bactria_plugin_enter_sector(void* sector_handle [[clang::use_handle("bactria sector")]],
                                     const char* source, std::uint32_t lineno, const char* caller) noexcept -> void;
    auto bactria_plugin_leave_sector(void* sector_handle [[clang::use_handle("bactria sector")]],
                                     const char* source, std::uint32_t lineno, const char* caller) noexcept-> void;
    auto bactria_plugin_sector_summary(void* sector_handle [[clang::use_handle("bactria sector")]]) noexcept -> void;

    [[nodiscard, clang::acquire_handle("bactria phase")]]
    auto bactria_plugin_create_phase(const char* name) noexcept -> void*;
    
    auto bactria_plugin_destroy_phase(void* phase_handle [[clang::release_handle("bactria phase")]]) noexcept -> void;

    auto bactria_plugin_assign_sector_phase(void* sector_handle [[clang::use_handle("bactria sector")]],
                                            void* phase_handle [[clang::use_handle("bactria phase")]]) noexcept -> void;
}

#endif
