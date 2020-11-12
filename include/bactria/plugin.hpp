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

#ifndef BACTRIA_PLUGIN_HPP
#define BACTRIA_PLUGIN_HPP

#include <bactria/event.hpp>
#include <bactria/detail/plugin_interface.hpp>
#include <bactria/detail/posix.hpp>
#include <bactria/detail/win32.hpp>

namespace bactria::plugin
{
    using plugin_handle_t = detail::plugin_handle_t;

    auto load_plugin() noexcept(false) -> plugin_handle_t
    {
        if(const auto path = std::getenv("BACTRIA_PLUGIN"); path != nullptr)
        {
            auto handle = detail::open_plugin(path);

            detail::load_func(handle, detail::create_region_ptr, "bactria_plugin_create_region");
            detail::load_func(handle, detail::destroy_region_ptr, "bactria_plugin_destroy_region");
            detail::load_func(handle, detail::create_phase_ptr, "bactria_plugin_create_phase");
            detail::load_func(handle, detail::destroy_phase_ptr, "bactria_plugin_destroy_phase");
            detail::load_func(handle, detail::create_event_ptr, "bactria_plugin_create_event");
            detail::load_func(handle, detail::destroy_event_ptr, "bactria_plugin_destroy_event");
            detail::load_func(handle, detail::assign_region_phase_ptr, "bactria_plugin_assign_region_phase");
            detail::load_func(handle, detail::start_recording_ptr, "bactria_plugin_start_recording");
            detail::load_func(handle, detail::stop_recording_ptr, "bactria_plugin_stop_recording");
            detail::load_func(handle, detail::record_event_ptr, "bactria_plugin_record_event");

            return handle;
        }

        // getenv failed
        throw std::runtime_error{"BACTRIA_PLUGIN not specified"};
    }

    auto unload_plugin(plugin_handle_t handle) noexcept
    {
        detail::close_plugin(handle);
    }

    [[gnu::always_inline, clang::acquire_handle("bactria region")]]
    inline auto create_region(const char* name) noexcept
    {
        return (detail::create_region_ptr)(name);
    }

    [[gnu::always_inline]]
    inline auto destroy_region(void* region_handle [[clang::release_handle("bactria region")]]) noexcept
    {
        (detail::destroy_region_ptr)(region_handle);
    }

    [[gnu::always_inline, clang::acquire_handle("bactria phase")]]
    inline auto create_phase(const char* name) noexcept
    {
        return (detail::create_phase_ptr)(name);
    }

    [[gnu::always_inline]]
    inline auto destroy_phase(void* phase_handle [[clang::release_handle("bactria phase")]]) noexcept
    {
        (detail::destroy_phase_ptr)(phase_handle);
    }

    [[gnu::always_inline, clang::acquire_handle("bactria event")]]
    inline auto create_event(const char* name) noexcept
    {
        return (detail::create_event_ptr)(name);
    }

    [[gnu::always_inline]]
    inline auto destroy_event(void* event_handle [[clang::release_handle("bactria event")]]) noexcept
    {
        (detail::destroy_event_ptr)(event_handle);
    }

    [[gnu::always_inline]]
    inline auto assign_region_phase(void* region_handle [[clang::use_handle("bactria region")]],
                                    void* phase_handle [[clang::use_handle("bactria phase")]]) noexcept
    {
        (detail::assign_region_phase_ptr)(region_handle, phase_handle);
    }

    [[gnu::always_inline]]
    inline auto start_recording(void* region_handle [[clang::use_handle("bactria region")]]) noexcept
    {
        (detail::start_recording_ptr)(region_handle);
    }

    [[gnu::always_inline]]
    inline auto stop_recording(void* region_handle [[clang::use_handle("bactria region")]]) noexcept
    {
        (detail::stop_recording_ptr)(region_handle);
    }

    [[gnu::always_inline]]
    inline auto record_event(void* region_handle [[clang::use_handle("bactria region")]],
                             void* event_handle [[clang::use_handle("bactria event")]]) noexcept
    {
        (detail::record_event_ptr)(region_handle, event_handle);
    }
}

extern "C"
{
    [[clang::acquire_handle("bactria region")]]
    auto bactria_plugin_create_region(const char* name) noexcept -> void*;

    auto bactria_plugin_destroy_region(void* region_handle [[clang::release_handle("bactria region")]]) noexcept -> void;

    [[clang::acquire_handle("bactria phase")]]
    auto bactria_plugin_create_phase(const char* name) noexcept -> void*;
    
    auto bactria_plugin_destroy_phase(void* phase_handle [[clang::release_handle("bactria phase")]]) noexcept -> void;

    [[clang::acquire_handle("bactria event")]]
    auto bactria_plugin_create_event(const char* name) noexcept -> void*;
    
    auto bactria_plugin_destroy_event(void* event_handle [[clang::release_handle("bactria event")]]) noexcept -> void;

    auto bactria_plugin_assign_region_phase(void* region_handle [[clang::use_handle("bactria region")]],
                                            void* phase_handle [[clang::use_handle("bactria phase")]]) noexcept -> void;

    auto bactria_plugin_start_recording(void* region_handle [[clang::use_handle("bactria region")]]) noexcept -> void;

    auto bactria_plugin_stop_recording(void* region_handle [[clang::use_handle("bactria region")]]) noexcept-> void;

    auto bactria_plugin_record_event(void* region_handle [[clang::use_handle("bactria region")]],
                                     void* event_handle [[clang::use_handle("bactria event")]]) noexcept -> void;
}

#endif
