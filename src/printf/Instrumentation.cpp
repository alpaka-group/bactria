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

#include "BodyInstrumentation.hpp"
#include "Common.hpp"
#include "FunctionInstrumentation.hpp"
#include "GenericInstrumentation.hpp"
#include "LoopInstrumentation.hpp"
#include "PhaseInstrumentation.hpp"

#include <bactria/Colors.hpp>
#include <bactria/PluginInterface.hpp>

#include <fmt/color.h>
#include <fmt/core.h>

#include <chrono>
#include <cstdint>
#include <functional>
#include <memory>
#include <stack>
#include <utility>

thread_local std::stack<sector*> sector_stack;

extern "C"
{
    [[clang::acquire_handle("bactria sector")]]
    auto bactria_plugin_create_sector(char const* name, std::uint32_t type) noexcept -> void*
    {
        switch(type)
        {
            case 2u:
                return new sector{name, type::function};

            case 3u:
                return new sector{name, type::loop};

            case 4u:
                return new sector{name, type::body, sector_data_ptr{new BodyData, delete_body}};

            case 5u:
                return new sector{name, type::phase};

            default:
                return new sector{name, type::generic};

        }
    }

    auto bactria_plugin_destroy_sector(void* sector_handle [[clang::release_handle("bactria sector")]]) noexcept -> void
    {
        auto sec = static_cast<sector*>(sector_handle);
        delete sec;
    }

    auto bactria_plugin_enter_sector(void* sector_handle [[clang::use_handle("bactria sector")]],
                                     const char* source, std::uint32_t lineno, const char* caller) noexcept -> void
    {
        auto const sec = static_cast<sector*>(sector_handle);
        switch(sec->t)
        {
            case type::generic:
                enter_generic(sec, source, lineno, caller);
                break;

            case type::function:
                enter_function(sec, source, lineno);
                break;

            case type::loop:
                enter_loop(sec, source, lineno);
                break;

            case type::body:
                enter_body(sec, source, lineno);
                break;

            case type::phase:
                enter_phase(sec, source, lineno);
                break;
        }
    }

    auto bactria_plugin_leave_sector(void* sector_handle [[clang::use_handle("bactria sector")]],
                                     const char* source, std::uint32_t lineno, const char* caller) noexcept-> void
    {
        const auto sec = static_cast<sector*>(sector_handle);
        switch(sec->t)
        {
            case type::generic:
                leave_generic(sec, source, lineno, caller);
                break;

            case type::function:
                leave_function(sec, source, lineno);
                break;

            case type::loop:
                leave_loop(sec, source, lineno);
                break;

            case type::body:
                leave_body(sec, source, lineno);
                break;

            case type::phase:
                leave_phase(sec, source, lineno);
                break;
        }
    }

    auto bactria_plugin_sector_summary(void* sector_handle [[clang::use_handle("bactria sector")]]) noexcept -> void
    {
        const auto sec = static_cast<sector*>(sector_handle);
        switch(sec->t)
        {
            case type::generic:
                generic_summary(sec);
                break;

            case type::function:
                function_summary(sec);
                break;

            case type::loop:
                loop_summary(sec);
                break;

            case type::body:
                body_summary(sec);
                break;

            case type::phase:
                phase_summary(sec);
                break;
        }
    }

    [[clang::acquire_handle("bactria phase")]] auto bactria_plugin_create_phase(const char* name) noexcept -> void*
    {
        return bactria_plugin_create_sector(name, 5);
    }
    
    auto bactria_plugin_destroy_phase(void* phase_handle [[clang::release_handle("bactria phase")]]) noexcept -> void
    {
        bactria_plugin_destroy_sector(phase_handle);
    }

    auto bactria_plugin_enter_phase(void* phase_handle [[clang::use_handle("bactria phase")]],
                                     const char* source, std::uint32_t lineno, const char* caller) noexcept -> void
    {
        bactria_plugin_enter_sector(phase_handle, source, lineno, caller);
    }

    auto bactria_plugin_leave_phase(void* phase_handle [[clang::use_handle("bactria phase")]],
                                     const char* source, std::uint32_t lineno, const char* caller) noexcept-> void
    {
        bactria_plugin_leave_sector(phase_handle, source, lineno, caller);
    }
}
