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

#ifndef BACTRIA_PLUGIN_PRINTF_COMMON_HPP
#define BACTRIA_PLUGIN_PRINTF_COMMON_HPP

#include <bactria/Colors.hpp>

#include <fmt/color.h>
#include <fmt/core.h>

#include <chrono>
#include <functional>
#include <memory>
#include <stack>
#include <utility>

using TimePair = std::pair<std::chrono::steady_clock::time_point, std::chrono::steady_clock::time_point>;

enum class type
{
    generic,
    function,
    loop,
    body,
    phase
};

using sector_data_ptr = std::unique_ptr<void, std::function<void(void*)>>;
struct sector
{
    char const* name;
    type t;
    sector_data_ptr data{nullptr};
};

extern thread_local std::stack<sector*> sector_stack;

[[gnu::always_inline]] inline auto handle_pop(sector* sec)
{
    if(sector_stack.top() != sec)
    {
        fmt::print(
            stderr,
            fg(fmt::rgb(bactria::color::bactria_red)),
            "WARNING: enter/leave of sector {} were invalidly nested. This is likely to produce wrong results.\n",
            sec->name);
    }
    else
        sector_stack.pop();
}

#endif
