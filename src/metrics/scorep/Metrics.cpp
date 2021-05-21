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

#include <bactria/metrics/PluginInterface.hpp>

#include <scorep/SCOREP_User.h>
#include <scorep/SCOREP_User_Functions.h>
#include <scorep/SCOREP_User_Types.h>
#include <scorep/SCOREP_User_Variables.h>

#include <cstdint>

namespace
{
    struct Sector
    {
        SCOREP_User_RegionHandle region;
        char const* name;
        std::uint32_t type;
    };

    struct Phase
    {
        SCOREP_User_RegionHandle region;
        char const* name;
    };
} // namespace

extern "C"
{
    auto bactria_metrics_create_sector(char const* name, std::uint32_t type) noexcept -> void*
    {
        return new Sector{SCOREP_INVALID_REGION, name, type};
    }

    auto bactria_metrics_destroy_sector(void* sector_handle) noexcept -> void
    {
        auto s = static_cast<Sector*>(sector_handle);
        delete s;
    }

    auto bactria_metrics_enter_sector(
        void* sector_handle,
        char const* source,
        std::uint32_t lineno,
        char const* caller) noexcept -> void
    {
        auto s = static_cast<Sector*>(sector_handle);

        auto region_type = int{};
        switch(s->type)
        {
        case 2u:
            region_type = SCOREP_USER_REGION_TYPE_FUNCTION;
            break;

        case 3u:
            region_type = SCOREP_USER_REGION_TYPE_LOOP;
            break;

        case 4u:
            region_type = SCOREP_USER_REGION_TYPE_DYNAMIC;
            break;

        default:
            region_type = SCOREP_USER_REGION_TYPE_COMMON;
            break;
        }

        SCOREP_User_RegionBegin(
            &(s->region),
            &SCOREP_User_LastFileName,
            &SCOREP_User_LastFileHandle,
            s->name,
            region_type,
            source,
            lineno);
    }

    auto bactria_metrics_leave_sector(
        void* sector_handle,
        char const* source,
        std::uint32_t lineno,
        char const* caller) noexcept -> void
    {
        auto s = static_cast<Sector*>(sector_handle);
        SCOREP_User_RegionEnd(s->region);
    }

    auto bactria_metrics_sector_summary(void* sector_handle) noexcept -> void
    {
        // TODO
    }

    auto bactria_metrics_create_phase(char const* name) noexcept -> void*
    {
        return new Phase{SCOREP_INVALID_REGION, name};
    }

    auto bactria_metrics_destroy_phase(void* phase_handle) noexcept -> void
    {
        auto p = static_cast<Phase*>(phase_handle);
        delete p;
    }

    auto bactria_metrics_enter_phase(
        void* phase_handle,
        char const* source,
        std::uint32_t lineno,
        char const* caller) noexcept -> void
    {
        auto p = static_cast<Phase*>(phase_handle);
        SCOREP_User_RegionBegin(
            &(p->region),
            &SCOREP_User_LastFileName,
            &SCOREP_User_LastFileHandle,
            p->name,
            SCOREP_USER_REGION_TYPE_PHASE,
            source,
            lineno);
    }

    auto bactria_metrics_leave_phase(void* phase_handle, char const*, std::uint32_t, char const*) noexcept -> void
    {
        auto p = static_cast<Phase*>(phase_handle);
        SCOREP_User_RegionEnd(p->region);
    }
}