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

/**
 * \file Incident.hpp
 * \brief Incident definition.
 *
 * Contains the definitions for the Incident class. It should not be included directly by the user.
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

        /**
         * \brief The incident type.
         * \ingroup bactria_reports_user
         *
         * Users can define their own metrics by recording incidents. These are key-value pairs. The key is always a
         * user-defined string, the value must be an arithmetic type or a `std::string`.
         *
         * \tparam TValue The value recorded by the incident.
         * \sa IncidentRecorder
         */
        template<typename TValue>
        class Incident
        {
            static_assert(
                std::is_arithmetic<TValue>::value || std::is_same<TValue, std::string>::value,
                "Incident value must be an arithmetic type or std::string");

            template<typename... TIncidents>
            friend class Report;

        public:
            /**
             * \brief Default constructor.
             *
             * Constructs an Incident with the key `BACTRIA_INCIDENT` and a default-initialized value.
             */
            Incident() = default;

            /**
             * \brief Constructor.
             *
             * Constructs an Incident with the key \a key and the value \a value.
             *
             * \param key The key to store the value under.
             * \param value The value to store.
             */
            Incident(std::string key, TValue value) : m_key{std::move(key)}, m_value{value}
            {
            }

            /**
             * \brief Copy constructor.
             *
             * Copy-constructs an Incident from the \a other Incident. After construction, both `this` and \a other
             * will contain identical copies of the key and the value.
             *
             * \param other The Incident to copy from.
             */
            Incident(Incident const& other) : m_key{other.m_key}, m_value{other.m_value}
            {
            }

            /**
             * \brief Copy-assignment operator.
             *
             * Copies the contents of \a rhs into `this`. After the copy, both `this` and \a rhs will contain
             * identical copies of the key and the value.
             *
             * \param rhs The Incident to copy from.
             */
            auto operator=(Incident const& rhs) -> Incident&
            {
                m_key = rhs.m_key;
                m_value = rhs.m_value;
                return *this;
            }

            /**
             * \brief Move constructor.
             *
             * Constructs an Incident by moving \a other into `this`. After construction, `this` will have taken
             * over the contents of \a other, while \a other is in an undefined state.
             *
             * \param other The Incident to move into `this`.
             */
            Incident(Incident&& other) noexcept : m_key{std::move(other.m_key)}, m_value{std::move(other.m_value)}
            {
            }

            /**
             * \brief Move-assignment operator.
             *
             * Moves the contents of \a rhs into `this`. After the move, `this` will have taken over the contents of
             * \a rhs, while \a rhs is in an undefined state.
             *
             * \param rhs
             */
            auto operator=(Incident&& rhs) noexcept -> Incident&
            {
                m_key = std::move(rhs.m_key);
                m_value = std::move(rhs.m_value);
                return *this;
            }

            /**
             * \brief Destructor.
             */
            ~Incident() = default;

        private:
            std::string m_key{"BACTRIA_INCIDENT"};
            TValue m_value{};
        };

        /**
         * \brief Create an incident from a key and a value.
         * \ingroup bactria_reports_user
         *
         * Creates an Incident from a \a key and a \a value.
         *
         * \tparam TValue The type of the value to store in the Incident.
         * \param key The key to store the value under.
         * \param value The value to record. If \a value is a reference type, it will be copied to a
         *              new object which is stored in the Incident.
         * \return An Incident object that can be stored in a Report.
         */
        template<typename TValue>
        auto make_incident(std::string key, TValue value) -> Incident<std::remove_reference_t<TValue>>
        {
            using ValueType = std::remove_reference_t<TValue>;
            return Incident<ValueType>{std::move(key), value};
        }
    } // namespace reports
} // namespace bactria
