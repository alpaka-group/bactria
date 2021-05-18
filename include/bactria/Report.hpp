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

#include <bactria/Incident.hpp>
#include <bactria/Plugin.hpp>
#include <bactria/detail/Activation.hpp>

#include <functional>
#include <string>
#include <tuple>
#include <utility>

namespace bactria
{
    template<typename... TIncidents>
    class Report
    {
    public:
        Report() = default;

        Report(std::string name, TIncidents&&... incidents)
            : m_name{std::move(name)}
            , m_incidents{std::forward<TIncidents>(incidents)...}
        {
        }

        Report(Report const& other) : m_name{other.m_name}, m_incidents{other.m_incidents}
        {
        }

        auto operator=(Report const& rhs) -> Report&
        {
            m_name = rhs.m_name;
            m_incidents = rhs.m_incidents;
            return *this;
        }

        Report(Report&& other) noexcept : m_name{std::move(other.m_name)}, m_incidents{std::move(other.m_incidents)}
        {
        }

        auto operator=(Report&& rhs) noexcept -> Report&
        {
            m_name = std::move(rhs.m_name);
            m_incidents = std::move(rhs.m_incidents);
            return *this;
        }

        ~Report()
        {
            if(detail::reports_activated())
                plugin::destroy_report(m_handle);
        }

        auto submit() const
        {
            using namespace std::placeholders;
            using TTuple = decltype(m_incidents);

            if(detail::reports_activated())
            {
                submit_incidents(std::make_index_sequence<std::tuple_size<TTuple>::value>{});
                plugin::write_report(m_handle);
            }
        }

    private:
        template<std::size_t... Is>
        auto submit_incidents(std::index_sequence<Is...>) const
        {
            auto dummy = {(submit_incident(std::get<Is>(m_incidents)), 0)...};
        }

        template<typename TIncident>
        auto submit_incident(TIncident const& incident) const
        {
            plugin::record_value(m_handle, incident.m_key.c_str(), incident.m_value);
        }

        std::string m_name{"BACTRIA_REPORT"};
        std::tuple<TIncidents...> m_incidents{};
        void* m_handle{detail::reports_activated() ? plugin::create_report(m_name.c_str()) : nullptr};
    };

    template<typename... TIncidents>
    auto make_report(std::string name, TIncidents&&... incidents) -> Report<TIncidents...>
    {
        return Report<TIncidents...>{std::move(name), std::forward<TIncidents>(incidents)...};
    }
} // namespace bactria
