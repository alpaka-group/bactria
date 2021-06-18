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
 * \file IncidentRecorder.hpp
 * \brief IncidentRecorder definitions.
 *
 * Contains the definitions for the IncidentRecorder class. It should not be included directly by the user.
 */

#pragma once

#include <bactria/reports/Report.hpp>

#include <cstddef>
#include <functional>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>

namespace bactria
{
    namespace reports
    {
        /**
         * \brief Class for dynamic recording of Incident%s.
         * \ingroup bactria_reports_user
         *
         * The IncidentRecorder can be used to dynamically collect user-defined metrics in one or more steps. The
         * user needs to know the final Incident type(s) as well as any preceeding intermediate type at compile time.
         * However, the actual instantiation of the types and the calculation of their values may happen at runtime.
         *
         * \tparam TValues Values stored by an IncidentRecorder.
         */
        template<typename... TValues>
        class IncidentRecorder
        {
        public:
            /**
             * \brief The recorder type used inside the recording functions.
             *
             * If the user wants to record a value inside the record_step() method, their supplied function object
             * needs to take exactly one parameter of the corresponding `record_t` type (defined by the same class
             * instantiation).
             *
             * Curently, this type is identical to the class it is defined in; however, for future compatibility users
             * should use record_t instead of its parent class.
             */
            using record_t = IncidentRecorder<TValues...>;

        public:
            /**
             * \brief Perform a recording step.
             *
             * This overload allows to use the load() and store() methods in the supplied function object. This is
             * useful for recording user-defined metrics at runtime.
             *
             * \tparam TFunc Function object type.
             * \param f Function object with the signature `void(record_t&)`.
             * \sa record_t
             */
            template<typename TFunc>
            auto record_step(
                TFunc&& f,
                /* Poor man's std::is_invocable until we have access to C++17 */
                std::enable_if_t<
                    std::is_constructible<
                        std::function<void(record_t&)>,
                        std::reference_wrapper<typename std::remove_reference<TFunc>::type>>::value,
                    int> = 0)
            {
                f(*this);
            }

            /**
             * \brief Perform a recording step without loading or storing data.
             *
             * This overload does not permit to call the load() and store() methods inside the supplied function
             * object. This is useful for intermediate recording steps that do not touch any data, for example
             * for additional logging.
             *
             * \tparam TFunc Function object type.
             * \param f Function object with the signature `void(void)`.
             */
            template<typename TFunc>
            auto record_step(
                TFunc&& f,
                std::enable_if_t<
                    std::is_constructible<
                        std::function<void(void)>,
                        std::reference_wrapper<typename std::remove_reference<TFunc>::type>>::value,
                    int> = 0)
            {
                f();
            }

            /**
             * \brief Load a value.
             *
             * Inside the record_step() method, this method can be used to load a value. The provided index needs to
             * match the position of the desired type in the type list defined during construction. The first type in
             * the type list has the index 0.
             *
             * \tparam TIndex The position of the type in the type list.
             */
            template<std::size_t TIndex>
            auto load()
            {
                static_assert(TIndex < std::tuple_size<decltype(m_values)>::value, "Data index out of bounds");
                return std::get<TIndex>(m_values);
            }

            /**
             * \brief Record a value.
             *
             * Inside the record_step() method, this method can be used to record a value. Note that the provided
             * index has to match the value's type position in the tdype list defined during construction. The first
             * type in the type list has the index 0.
             *
             * \tparam TIndex The position of the corresponding type in the type list.
             * \tparam TValue The type of the value to be stored.
             * \param value The value to be stored.
             */
            template<std::size_t TIndex, typename TValue>
            auto store(TValue&& value)
            {
                static_assert(TIndex < std::tuple_size<decltype(m_values)>::value, "Data index out of bounds");
                std::get<TIndex>(m_values) = value;
            }

            /**
             * \brief Generate report from stored Incident%s.
             *
             * Once all required Incident%s have been stored, the submit_report() method can be used to save them (the
             * exact saving operation depends on the plugin in use). This is achieved by providing the corresponding
             * indices for the types in the type list that was defined during construction. The first type in the list
             * has the index 0.
             *
             * \tparam TIndices Incident indices to be used for report generation. The indices must match the
             *                  positions of Incident types in the type list.
             * \param name The name of the generated Report.
             */
            template<std::size_t... TIndices>
            auto submit_report(std::string name) const
            {
                auto const r = make_report(std::move(name), std::get<TIndices>(m_values)...);
                r.submit();
            }

        private:
            std::tuple<TValues...> m_values{std::make_tuple(TValues{}...)};
        };
    } // namespace reports

} // namespace bactria
