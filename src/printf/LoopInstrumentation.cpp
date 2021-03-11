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

#include "LoopInstrumentation.hpp"

#include "Common.hpp"

#include <fmt/core.h>

#include <cstdint>

auto enter_loop(sector* sec [[clang::use_handle("bactria sector")]], char const* source, std::uint32_t lineno) -> void
{
    auto const parents = sector_stack.size();
    fmt::print("{:>{}} Entering loop {} - {}:{}.\n", "|", 4u * parents, sec->name, source, lineno);
    sector_stack.push(sec);
}

auto leave_loop(sector* sec [[clang::use_handle("bactria sector")]], char const* source, std::uint32_t lineno) -> void
{
    auto const parents = sector_stack.size();
    fmt::print("{:>{}} Leaving loop {} - {}:{}.\n", "|", 4u * (parents - 1u), sec->name, source, lineno);
    handle_pop(sec);
}

auto loop_summary(sector* sec [[maybe_unused, clang::use_handle("bactria sector")]]) -> void
{
}
