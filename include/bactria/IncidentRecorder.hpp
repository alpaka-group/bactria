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

#ifndef BACTRIA_INCIDENT_RECORDER_HPP
#define BACTRIA_INCIDENT_RECORDER_HPP

#   include <bactria/Report.hpp>

#   include <cstddef>
#   include <string>
#   include <tuple>
#   include <utility>

namespace bactria
{
    template <typename... TValues>
    class IncidentRecorder
    {
    public:
        template <typename TFunc>
        auto record_step(TFunc&& f) -> void
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

#endif
