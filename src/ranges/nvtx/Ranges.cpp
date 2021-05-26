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

#include <bactria/ranges/PluginInterface.hpp>

#include <nvToolsExt.h>

#include <cstdint>

namespace
{
    struct event
    {
        std::uint32_t color;
        char const* cat_name;
        std::uint32_t cat_id;
    };

    struct range
    {
        char const* name;
        std::uint32_t color;
        char const* cat_name;
        std::uint32_t cat_id;
        nvtxRangeId_t id;
    };
} // namespace

extern "C"
{
    auto bactria_ranges_create_event(std::uint32_t color, char const* cat_name, std::uint32_t cat_id) noexcept -> void*
    {
        return new event{color, cat_name, cat_id};
    }

    auto bactria_ranges_destroy_event(void* event_handle) noexcept -> void
    {
        auto ev = static_cast<event*>(event_handle);
        delete ev;
    }

    auto bactria_ranges_fire_event(
        void* event_handle,
        char const* event_name,
        char const* source,
        std::uint32_t lineno,
        char const* caller) noexcept -> void
    {
        auto const ev = static_cast<event*>(event_handle);

        auto const attributes = nvtxEventAttributes_t{
            /* .version = */ NVTX_VERSION,
            /* .size = */ NVTX_EVENT_ATTRIB_STRUCT_SIZE,
            /* .category = */ ev->cat_id,
            /* .colorType = */ NVTX_COLOR_ARGB,
            /* .color = */ ev->color,
            /* .payloadType = */ NVTX_PAYLOAD_UNKNOWN, // currently not supported
            /* .reserved0 = */ 0,
            /* .payload = */ 0,
            /* .messageType = */ NVTX_MESSAGE_TYPE_ASCII,
            /* .message = */ event_name};

        nvtxNameCategoryA(ev->cat_id, ev->cat_name);

        nvtxMarkEx(&attributes);
    }

    auto bactria_ranges_create_range(
        char const* name,
        std::uint32_t color,
        char const* cat_name,
        std::uint32_t cat_id) noexcept -> void*
    {
        return new range{name, color, cat_name, cat_id, nvtxRangeId_t{}};
    }

    auto bactria_ranges_destroy_range(void* range_handle) noexcept -> void
    {
        auto r = static_cast<range*>(range_handle);
        delete r;
    }

    auto bactria_ranges_start_range(void* range_handle) noexcept -> void
    {
        auto r = static_cast<range*>(range_handle);

        auto const attributes = nvtxEventAttributes_t{
            /* .version = */ NVTX_VERSION,
            /* .size = */ NVTX_EVENT_ATTRIB_STRUCT_SIZE,
            /* .category = */ r->cat_id,
            /* .colorType = */ NVTX_COLOR_ARGB,
            /* .color = */ r->color,
            /* .payloadType = */ NVTX_PAYLOAD_UNKNOWN, // currently not supported
            /* .reserved0 = */ 0,
            /* .payload = */ 0,
            /* .messageType = */ NVTX_MESSAGE_TYPE_ASCII,
            /* .message = */ r->name};

        nvtxNameCategoryA(r->cat_id, r->cat_name);

        r->id = nvtxRangeStartEx(&attributes);
    }

    auto bactria_ranges_stop_range(void* range_handle) noexcept -> void
    {
        auto const r = static_cast<range*>(range_handle);
        nvtxRangeEnd(r->id);
    }
}
