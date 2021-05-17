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

#include "Common.hpp"

#include <fmt/core.h>

#include <cstdint>

auto enter_generic(sector* sec, char const* source, std::uint32_t lineno, char const* caller)
{
    auto const parents = sector_stack.size();
    fmt::print("{:>{}} Entering sector {} in {}() - {}:{}.\n", "|", 4u * parents, sec->name, caller, source, lineno);
    sector_stack.push(sec);
}

auto leave_generic(sector* sec, char const* source, std::uint32_t lineno, char const* caller)
{
    const auto parents = sector_stack.size();
    fmt::print(
        "{:>{}} Leaving sector {} in {}() - {}:{}.\n",
        "|",
        4u * (parents - 1u),
        sec->name,
        caller,
        source,
        lineno);
    handle_pop(sec);
}

auto generic_summary(sector* sec [[maybe_unused]])
{
}
