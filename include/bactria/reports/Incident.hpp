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

#include <string>
#include <type_traits>
#include <utility>

namespace bactria
{
    namespace reports
    {
        template<typename... TIncidents>
        class Report;

        template<typename TValue>
        class Incident
        {
            static_assert(
                std::is_arithmetic<TValue>::value || std::is_same<TValue, std::string>::value,
                "Incident value must be an arithmetic type or std::string");

            template<typename... TIncidents>
            friend class Report;

        public:
            Incident() = default;

            Incident(std::string key, TValue value) : m_key{std::move(key)}, m_value{value}
            {
            }

            Incident(Incident const& other) : m_key{other.m_key}, m_value{other.m_value}
            {
            }

            auto operator=(Incident const& rhs) -> Incident&
            {
                m_key = rhs.m_key;
                m_value = rhs.m_value;
                return *this;
            }

            Incident(Incident&& other) noexcept : m_key{std::move(other.m_key)}, m_value{std::move(other.m_value)}
            {
            }

            auto operator=(Incident&& rhs) noexcept -> Incident&
            {
                m_key = std::move(rhs.m_key);
                m_value = std::move(rhs.m_value);
                return *this;
            }

            ~Incident() = default;

        private:
            std::string m_key{"BACTRIA_INCIDENT"};
            TValue m_value{};
        };

        template<typename TValue>
        auto make_incident(std::string key, TValue value) -> Incident<std::remove_reference_t<TValue>>
        {
            using ValueType = std::remove_reference_t<TValue>;
            return Incident<ValueType>{std::move(key), value};
        }
    } // namespace reports
} // namespace bactria
