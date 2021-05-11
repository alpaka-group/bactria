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

#include <bactria/PluginInterface.hpp>

#include <nlohmann/json.hpp>

#include <cstdint>
#include <fstream>
#include <iomanip>
#include <string>

struct report
{
    std::string name{};
    nlohmann::json j{};
};

namespace
{
    template <typename TValue>
    auto record_incident(void* handle, char const* key, TValue value)
    {
        auto r = static_cast<report*>(handle);
        r->j[key] = value;
    }
}

extern "C"
{
    auto bactria_report_plugin_create_report(char const* name) -> void*
    {
        return new report{name};
    }

    auto bactria_report_plugin_destroy_report(void* handle) noexcept -> void
    {
        auto r = static_cast<report*>(handle);
        delete r;
    }

    auto bactria_report_plugin_write_report(void* handle) -> void
    {
        auto r = static_cast<report const*>(handle);
        auto const filename = r->name + ".json";

        auto&& file = std::ofstream{filename.c_str(), std::ios_base::app};
        file << std::setw(4) << r->j << std::endl;
    }

    auto bactria_report_plugin_record_incident_bool(void* handle, char const* key, bool value) -> void
    {
        record_incident(handle, key, value);
    }

    auto bactria_report_plugin_record_incident_int8(void* handle, char const* key, std::int8_t value) -> void
    {
        record_incident(handle, key, value);
    }

    auto bactria_report_plugin_record_incident_uint8(void* handle, char const* key, std::uint8_t value) -> void
    {
        record_incident(handle, key, value);
    }

    auto bactria_report_plugin_record_incident_int16(void* handle, char const* key, std::int16_t value) -> void
    {
        record_incident(handle, key, value);
    }

    auto bactria_report_plugin_record_incident_uint16(void* handle, char const* key, std::uint16_t value) -> void
    {
        record_incident(handle, key, value);
    }

    auto bactria_report_plugin_record_incident_int32(void* handle, char const* key, std::int16_t value) -> void
    {
        record_incident(handle, key, value);
    }

    auto bactria_report_plugin_record_incident_uint32(void* handle, char const* key, std::uint16_t value) -> void
    {
        record_incident(handle, key, value);
    }

    auto bactria_report_plugin_record_incident_int64(void* handle, char const* key, std::int64_t value) -> void
    {
        record_incident(handle, key, value);
    }

    auto bactria_report_plugin_record_incident_uint64(void* handle, char const* key, std::uint64_t value) -> void
    {
        record_incident(handle, key, value);
    }

    auto bactria_report_plugin_record_incident_float(void* handle, char const* key, float value) -> void
    {
        record_incident(handle, key, value);
    }

    auto bactria_report_plugin_record_incident_double(void* handle, char const* key, double value) -> void
    {
        record_incident(handle, key, value);
    }

    auto bactria_report_plugin_record_incident_string(void* handle, char const* key, char const* value) -> void
    {
        record_incident(handle, key, value);
    }
}
