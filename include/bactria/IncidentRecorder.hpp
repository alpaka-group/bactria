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

#pragma once

#include <bactria/Report.hpp>

#include <cstddef>
#include <functional>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>

namespace bactria
{
    template <typename... TValues>
    class IncidentRecorder
    {
    public:
        using record_t = IncidentRecorder<TValues...>;

    public:
        template <typename TFunc>
        auto record_step(TFunc&& f,
                         /* Poor man's std::is_invocable until we have access to C++17 */
                         std::enable_if_t<std::is_constructible<std::function<void(record_t&)>,
                                                                std::reference_wrapper<
                                                                    typename std::remove_reference<TFunc>::type>
                                            >::value, int> = 0)
        {
            f(*this);
        }

        template <typename TFunc>
        auto record_step(TFunc&& f,
                         std::enable_if_t<std::is_constructible<std::function<void(void)>,
                                                                std::reference_wrapper<typename std::remove_reference<TFunc>::type>
                                            >::value, int> = 0)
        {
            f();
        }

        template <std::size_t TIndex>
        auto load()
        {
            static_assert(TIndex < std::tuple_size<decltype(m_values)>::value, "Data index out of bounds");
            return std::get<TIndex>(m_values);
        }

        template <std::size_t TIndex, typename TValue>
        auto store(TValue&& value)
        {
            static_assert(TIndex < std::tuple_size<decltype(m_values)>::value, "Data index out of bounds");
            std::get<TIndex>(m_values) = value;
        }

        template <std::size_t... TIndices>
        auto submit_report(std::string name) const
        {
            auto const r = make_report(std::move(name), std::get<TIndices>(m_values)...);
            r.submit();
        }

    private:
        std::tuple<TValues...> m_values{std::make_tuple(TValues{}...)};
    };
}

