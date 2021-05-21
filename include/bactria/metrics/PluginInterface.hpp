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

/**
 * \file PluginInterface.hpp
 * \brief bactria's metrics plugin interface include.
 *
 * This is bactria's metrics plugin interface. Plugin developers should include this file and implement all functions
 * declared by it.
 */

#pragma once

#include <cstdint>

extern "C"
{
    /**
     * \brief Create a sector handle.
     *
     * This function creates a plugin-specific sector handle. This is internally used by bactria::Sector to
     * communicate with the plugin. Each bactria::Sector encapsulates its own sector handle.
     *
     * \param[in] name The name of the sector (as it should appear in the output).
     * \param[in] type The type of the sector. See Tags.hpp for the possible values.
     *
     * \return A handle to the plugin-specific sector.
     * \sa bactria_metrics_destroy_sector, bactria_metrics_enter_sector, bactria_metrics_leave_sector,
     *     bactria_metrics_sector_summary
     */
    auto bactria_metrics_create_sector(char const* name, std::uint32_t type) noexcept -> void*;

    /**
     * \brief Destroy a sector handle.
     *
     * Destroys a plugin-specific sector handle. This is internally called by bactria::Sector::~Sector(). The
     * \a sector_handle must not be used after the call unless it has been reinitialized with
     * bactria_metrics_create_sector().
     *
     * \param[in] sector_handle The sector handle created by bactria_metrics_create_sector().
     * \sa bactria_metrics_create_sector, bactria_metrics_enter_sector, bactria_metrics_leave_sector,
     *     bactria_metrics_sector_summary
     */
    auto bactria_metrics_destroy_sector(void* sector_handle) noexcept -> void;

    /**
     * \brief Enter a sector.
     *
     * Enters the plugin-specific sector. It is called internally by bactria::Sector::enter().
     *
     * \param[in,out] sector_handle The sector handle created by bactria_metrics_create_sector().
     * \param[in] source The source file of the call to bactria::Sector::enter().
     * \param[in] lineno The source line of the call to bactria::Sector::enter().
     * \param[in] caller The surrounding function of the call to bactria::Sector::enter().
     * \sa bactria_metrics_create_sector, bactria_metrics_destroy_sector, bactria_metrics_leave_sector,
     *     bactria_metrics_sector_summary
     */
    auto bactria_metrics_enter_sector(
        void* sector_handle,
        char const* source,
        std::uint32_t lineno,
        char const* caller) noexcept -> void;

    /**
     * \brief Leave a sector.
     *
     * Leaves the plugin-specific sector. It is called internally by bactria::Sector::leave().
     *
     * \param[in,out] sector_handle The sector handle created by bactria_metrics_create_sector().
     * \param[in] source The source file of the call to bactria::Sector::leave().
     * \param[in] lineno The source line of the call to bactria::Sector::leave().
     * \param[in] caller The surrounding function of the call to bactria::Sector::leave().
     * \sa bactria_metrics_create_sector, bactria_metrics_destroy_sector, bactria_metrics_enter_sector,
     *     bactria_metrics_sector_summary
     */
    auto bactria_metrics_leave_sector(
        void* sector_handle,
        char const* source,
        std::uint32_t lineno,
        char const* caller) noexcept -> void;

    /**
     * \brief Summarize a sector.
     *
     * Flushes the sector summary. This is called internally by bactria::Sector::summary() or by
     * bactria::Sector::~Sector() if bactria::Sector::summary() has not been called before.
     *
     * \param[in,out] sector_handle The sector handle created by bactria_metrics_create_sector().
     * \sa bactria_metrics_create_sector, bactria_metrics_destroy_sector, bactria_metrics_enter_sector,
     *     bactria_metrics_leave_sector
     */
    auto bactria_metrics_sector_summary(void* sector_handle) noexcept -> void;

    /**
     * \brief Create a phase handle.
     *
     * Creates a plugin-specific phase handle. This is called internally by bactria::Phase::Phase().
     *
     * \param[in] name The phase name as it should appear in the output.
     * \return A plugin-specific phase handle.
     * \sa bactria_metrics_destroy_phase
     */
    auto bactria_metrics_create_phase(char const* name) noexcept -> void*;

    /**
     * \brief Destroy a phase handle.
     *
     * Destroys a plugin-specific phase handle. This is called internally by bactria::Phase::~Phase().
     * The phase handle must not be used after the call unless it has been reinitialized by a call to
     * bactria_metrics_create_phase().
     *
     * \param[in] phase_handle The phase handle created by bactria_metrics_create_phase().
     * \sa bactria_metrics_create_phase
     */
    auto bactria_metrics_destroy_phase(void* phase_handle) noexcept -> void;

    /**
     * \brief Enter a phase.
     *
     * Enters the plugin-specific phase. It is called internally by bactria::Phase::enter().
     *
     * \param[in,out] phase_handle The phase handle created by bactria_metrics_create_phase().
     * \param[in] source The source file of the call to bactria::Phase::enter().
     * \param[in] lineno The source line of the call to bactria::Phase::enter().
     * \param[in] caller The surrounding function of the call to bactria::Phase::enter().
     * \sa bactria_metrics_create_phase, bactria_metrics_destroy_phase, bactria_metrics_leave_phase
     */
    auto bactria_metrics_enter_phase(
        void* phase_handle,
        char const* source,
        std::uint32_t lineno,
        char const* caller) noexcept -> void;

    /**
     * \brief Leave a phase.
     *
     * Leaves the plugin-specific sector. It is called internally by bactria::Phase::leave().
     *
     * \param[in,out] phase_handle The phase handle created by bactria_metrics_create_phase().
     * \param[in] source The source file of the call to bactria::Phase::leave().
     * \param[in] lineno The source line of the call to bactria::Phase::leave().
     * \param[in] caller The surrounding function of the call to bactria::Phase::leave().
     * \sa bactria_metrics_create_phase, bactria_metrics_destroy_phase, bactria_metrics_enter_phase
     *
     */
    auto bactria_metrics_leave_phase(
        void* phase_handle,
        char const* source,
        std::uint32_t lineno,
        char const* caller) noexcept -> void;
}
