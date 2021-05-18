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

#include <fmt/chrono.h>
#include <fmt/core.h>

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <numeric>
#include <vector>

auto enter_body(sector* sec, char const* source, std::uint32_t lineno) -> void
{
    auto const now = std::chrono::steady_clock::now();
    auto data_ptr = static_cast<BodyData*>(sec->data.get());

    ++data_ptr->iterations;

    if(!data_ptr->first_is_set)
    {
        data_ptr->global.first = now;
        data_ptr->first_is_set = true;
    }

    data_ptr->locals.emplace_back(now, now);

    auto const parents = sector_stack.size();
    fmt::print("{:>{}} Entering body {} - {}:{}.\n", "|", 4u * parents, sec->name, source, lineno);
    sector_stack.push(sec);
}

auto leave_body(sector* sec, char const* source, std::uint32_t lineno) -> void
{
    auto const now = std::chrono::steady_clock::now();
    auto data_ptr = static_cast<BodyData*>(sec->data.get());

    data_ptr->global.second = now;
    data_ptr->locals.back().second = now;

    auto const parents = sector_stack.size();
    fmt::print("{:>{}} Leaving body {} - {}:{}.\n", "|", 4u * (parents - 1u), sec->name, source, lineno);
    handle_pop(sec);
}

auto body_summary(sector* sec) -> void
{
    auto data_ptr = static_cast<BodyData*>(sec->data.get());

    using precise_duration = std::chrono::duration<double, std::micro>;

    auto dur_vec = std::vector<double>(data_ptr->locals.size());
    std::transform(
        std::begin(data_ptr->locals),
        std::end(data_ptr->locals),
        std::begin(dur_vec),
        [](TimePair const& p) { return (std::chrono::duration_cast<precise_duration>(p.second - p.first)).count(); });

    // duration
    auto const dur = std::chrono::duration_cast<precise_duration>(data_ptr->global.second - data_ptr->global.first);

    // min, max
    auto const minmax_ticks = std::minmax_element(std::begin(dur_vec), std::end(dur_vec));
    auto const min = precise_duration{*minmax_ticks.first};
    auto const max = precise_duration{*minmax_ticks.second};

    // average
    auto const sum_ticks = std::accumulate(std::begin(dur_vec), std::end(dur_vec), 0.0);
    auto const avg_ticks = sum_ticks / dur_vec.size();
    auto const avg = precise_duration{avg_ticks};

    // stddev
    auto const squared_ticks = std::inner_product(std::begin(dur_vec), std::end(dur_vec), std::begin(dur_vec), 0.0);
    auto const stddev_ticks = std::sqrt(squared_ticks / dur_vec.size() - (avg_ticks * avg_ticks));
    auto const stddev = precise_duration{stddev_ticks};

    auto const parents = sector_stack.size();
    fmt::print("{:>{}} Duration summary of body {}:\n", "|", 4u * parents, sec->name);
    fmt::print("{:>{}} Overall:\t\t\t{}\n", "|", 4u * (parents + 1), dur);
    fmt::print("{:>{}} Minimum:\t\t\t{}\n", "|", 4u * (parents + 1), min);
    fmt::print("{:>{}} Maximum:\t\t\t{}\n", "|", 4u * (parents + 1), max);
    fmt::print("{:>{}} Average:\t\t\t{}\n", "|", 4u * (parents + 1), avg);
    fmt::print("{:>{}} Standard deviation:\t{}\n", "|", 4u * (parents + 1), stddev);
}
