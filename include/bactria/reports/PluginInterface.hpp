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
 * \brief bactria's reports plugin interface include.
 *
 * This is bactria's reports plugin interface. Plugin developers should include this file and implement all functions
 * declared by it.
 */

#pragma once

#include <cstdint>

extern "C"
{
    auto bactria_reports_create_report(char const* name) -> void*;
    auto bactria_reports_destroy_report(void* report_handle) noexcept -> void;
    auto bactria_reports_write_report(void* report_handle) -> void;
    auto bactria_reports_record_bool(void* report_handle, char const* key, bool value) -> void;
    auto bactria_reports_record_int8(void* report_handle, char const* key, std::int8_t value) -> void;
    auto bactria_reports_record_uint8(void* report_handle, char const* key, std::uint8_t value) -> void;
    auto bactria_reports_record_int16(void* report_handle, char const* key, std::int16_t value) -> void;
    auto bactria_reports_record_uint16(void* report_handle, char const* key, std::uint16_t value) -> void;
    auto bactria_reports_record_int32(void* report_handle, char const* key, std::int16_t value) -> void;
    auto bactria_reports_record_uint32(void* report_handle, char const* key, std::uint16_t value) -> void;
    auto bactria_reports_record_int64(void* report_handle, char const* key, std::int64_t value) -> void;
    auto bactria_reports_record_uint64(void* report_handle, char const* key, std::uint64_t value) -> void;
    auto bactria_reports_record_float(void* report_handle, char const* key, float value) -> void;
    auto bactria_reports_record_double(void* report_handle, char const* key, double value) -> void;
    auto bactria_reports_record_string(void* report_handle, char const* key, char const* value) -> void;
}