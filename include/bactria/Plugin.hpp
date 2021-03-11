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

#ifndef BACTRIA_PLUGIN_HPP
#   define BACTRIA_PLUGIN_HPP

#   include <bactria/detail/PluginInterface.hpp>
#   include <bactria/detail/POSIX.hpp>
#   include <bactria/detail/Win32.hpp>

namespace bactria
{
    namespace plugin
    {
        using plugin_handle_t = detail::plugin_handle_t;

        [[nodiscard]] auto load_plugin() -> plugin_handle_t
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
            throw std::runtime_error{"BACTRIA_PLUGIN not specified"};
        }

        auto unload_plugin(plugin_handle_t handle) noexcept
        {
            detail::close_plugin(handle);
        }

        [[nodiscard, gnu::always_inline, clang::acquire_handle("bactria event")]]
        inline auto create_event(const char* name, std::uint32_t color, std::uint32_t category) noexcept
        {
            return (detail::create_event_ptr)(name, color, category);
        }

        [[gnu::always_inline]]
        inline auto destroy_event(void* event_handle [[clang::release_handle("bactria event")]]) noexcept
        {
            (detail::destroy_event_ptr)(event_handle);
        }

        [[gnu::always_inline]]
        inline auto fire_event(void* event_handle [[clang::use_handle("bactria event")]]) noexcept
        {
            (detail::fire_event_ptr)(event_handle);
        }

        [[nodiscard, gnu::always_inline, clang::acquire_handle("bactria range")]]
        inline auto create_range(const char* name, std::uint32_t color, std::uint32_t category) noexcept
        {
            return (detail::create_range_ptr)(name, color, category);
        }

        [[gnu::always_inline]]
        inline auto destroy_range(void* range_handle [[clang::release_handle("bactria range")]]) noexcept
        {
            (detail::destroy_range_ptr)(range_handle);
        }

        [[gnu::always_inline]]
        inline auto start_range(void* range_handle [[clang::use_handle("bactria range")]]) noexcept
        {
            (detail::start_range_ptr)(range_handle);
        }

        [[gnu::always_inline]]
        inline auto stop_range(void* range_handle [[clang::use_handle("bactria range")]]) noexcept
        {
            (detail::stop_range_ptr)(range_handle);
        }

        [[nodiscard, gnu::always_inline, clang::acquire_handle("bactria sector")]]
        inline auto create_sector(const char* name, std::uint32_t tag) noexcept
        {
            return (detail::create_sector_ptr)(name, tag);
        }

        [[gnu::always_inline]]
        inline auto destroy_sector(void* sector_handle [[clang::release_handle("bactria sector")]]) noexcept
        {
            (detail::destroy_sector_ptr)(sector_handle);
        }

        [[gnu::always_inline]]
        inline auto enter_sector(void* sector_handle [[clang::use_handle("bactria sector")]],
                                 const char* source, std::uint32_t lineno, const char* caller) noexcept
        {
            (detail::enter_sector_ptr)(sector_handle, source, lineno, caller);
        }

        [[gnu::always_inline]]
        inline auto leave_sector(void* sector_handle [[clang::use_handle("bactria sector")]],
                                 const char* source, std::uint32_t lineno, const char* caller) noexcept
        {
            (detail::leave_sector_ptr)(sector_handle, source, lineno, caller);
        }

        [[gnu::always_inline]]
        inline auto sector_summary(void* sector_handle [[clang::use_handle("bactria sector")]]) noexcept
        {
            (detail::sector_summary_ptr)(sector_handle);
        }

        [[nodiscard, gnu::always_inline, clang::acquire_handle("bactria phase")]]
        inline auto create_phase(const char* name) noexcept
        {
            return (detail::create_phase_ptr)(name);
        }

        [[gnu::always_inline]]
        inline auto destroy_phase(void* phase_handle [[clang::release_handle("bactria phase")]]) noexcept
        {
            (detail::destroy_phase_ptr)(phase_handle);
        }

        [[gnu::always_inline]]
        inline auto enter_phase(void* phase_handle [[clang::use_handle("bactria phase")]],
                                char const* source, std::uint32_t lineno, char const* caller) noexcept
        {
            (detail::enter_phase_ptr)(phase_handle, source, lineno, caller);
        }

        [[gnu::always_inline]]
        inline auto leave_phase(void* phase_handle [[clang::use_handle("bactria phase")]],
                                char const* source, std::uint32_t lineno, char const* caller) noexcept
        {
            (detail::leave_phase_ptr)(phase_handle, source, lineno, caller);
        }
    }
}

#endif
