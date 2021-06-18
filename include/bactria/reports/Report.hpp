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
 * \file Report.hpp
 * \brief Report definition.
 *
 * Contains the definitions for the Report class. It should not be included directly by the user.
 */

#pragma once

#include <bactria/reports/Incident.hpp>
#include <bactria/reports/Plugin.hpp>

#include <functional>
#include <string>
#include <tuple>
#include <utility>

namespace bactria
{
    namespace reports
    {
        /**
         * \defgroup bactria_reports_user User API
         * \ingroup bactria_reports
         *
         * User API for bactria's reports functionality.
         * \{
         */

        /**
         * \brief The report class.
         *
         * A report contains multiple entries (of type Incident). By submitting a report the user can save these
         * entries (the exact location depends on the selected plugin).
         *
         * \tparam TIncidents List of values (of type Incident) recorded by the report.
         */
        template<typename... TIncidents>
        class Report
        {
        public:
            /**
             * \brief Default constructor.
             *
             * Constructs a Report with the (file)name `BACTRIA_REPORT` and an empty list of Incident%s.
             */
            Report() = default;

            /**
             * \brief Constructor.
             *
             * Constructs a Report with the (file)name \a name and a list of Incident%s containing \a incidents.
             *
             * \param name The Report name. This is usally a filename which must not contain an extension.
             * \param incidents The Incident%s to record in the Report.
             */
            Report(std::string name, TIncidents&&... incidents)
                : m_name{std::move(name)}
                , m_incidents{std::forward<TIncidents>(incidents)...}
            {
            }

            /**
             * \brief Copy constructor.
             *
             * Constructs a Report by copying the contents of \a other. After the construction, `this` and \a other
             * will contain identical copies of the name and the Incident list.
             *
             * \param other The Report to copy from.
             */
            Report(Report const& other) : m_name{other.m_name}, m_incidents{other.m_incidents}
            {
            }

            /**
             * \brief Copy-assignment operator.
             *
             * Copies the contents of \a rhs into `this`. After the copy, `this` and \a rhs will contain identical
             * copies of the name and the Incident list.
             *
             * \param rhs The Report to copy from.
             */
            auto operator=(Report const& rhs) -> Report&
            {
                m_name = rhs.m_name;
                m_incidents = rhs.m_incidents;
                return *this;
            }

            /**
             * \brief Move constructor.
             *
             * Constructs a Report by moving the contents of \a other into `this`. After the move, `this` will have
             * taken over the contents of \a other, while \a other is in an undefined state.
             *
             * \param other The Report to move into `this`.
             */
            Report(Report&& other) noexcept
                : m_name{std::move(other.m_name)}
                , m_incidents{std::move(other.m_incidents)}
            {
            }

            /**
             * \brief Move-assignment operator.
             *
             * Moves the contents of \a rhs into `this`. After the move, `this` will have taken over the contents of
             * \a rhs, while \a rhs is in an undefined state.
             *
             * \param rhs The Report to move into `this`.
             */
            auto operator=(Report&& rhs) noexcept -> Report&
            {
                m_name = std::move(rhs.m_name);
                m_incidents = std::move(rhs.m_incidents);
                return *this;
            }

            /**
             * \brief Destructor.
             */
            ~Report()
            {
                if(plugin::activated())
                    plugin::destroy_report(m_handle);
            }

            /**
             * \brief Save the report.
             *
             * This method physically stores the report to a location defined by the plugin. This is usually a file
             * where the prefix corresponds to the name supplied by the user during Report construction, while the
             * suffix is a plugin-specific extension. Refer to the documentation of the plugin in question to gather
             * information about the concrete storage of the Report.
             */
            auto submit() const
            {
                using namespace std::placeholders;
                using TTuple = decltype(m_incidents);

                if(plugin::activated())
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
            void* m_handle{plugin::activated() ? plugin::create_report(m_name.c_str()) : nullptr};
        };

        /**
         * \brief Create a Report from several Incident%s.
         *
         * \tparam TIncidents The Incident types to save.
         * \param name The storage name. This is usually a filename which must not contain a file extension.
         * \param incidents The Incident%s to save.
         * \return A Report object containing the Incident%s.
         */
        template<typename... TIncidents>
        auto make_report(std::string name, TIncidents&&... incidents) -> Report<TIncidents...>
        {
            return Report<TIncidents...>{std::move(name), std::forward<TIncidents>(incidents)...};
        }

        /** \} */
    } // namespace reports
} // namespace bactria
