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
 * \file Marker.hpp
 * \brief bactria's Marker include file.
 *
 * This file contains the definition for the Marker class. It should not be included by the
 * user.
 */

#ifndef BACTRIA_MARKER_HPP
#   define BACTRIA_MARKER_HPP

#   include <bactria/Colors.hpp>
#   include <bactria/Category.hpp>

#   include <cstdint>
#   include <string>
#   include <utility>

namespace bactria
{
    /**
     * \defgroup Markers Visualization markers
     *
     * These markers enable user-defined highlighting during visualization.
     * \{
     */

    /**
     * \brief The abstract base class for markers.
     *
     * This class serves as abstract base for Events and Ranges. It should not be used directly by the user.
     */
    class Marker
    {
        public:
            Marker() = default;

            Marker(std::string name, std::uint32_t color, Category category)
            : m_name{std::move(name)}, m_color{color}, m_category{std::move(category)}
            {}

            Marker(Marker const&) = default;
            auto operator=(Marker const&) -> Marker& = default;

            Marker(Marker&&) = default;
            auto operator=(Marker&&) -> Marker& = default;

            virtual ~Marker() = default;

            /**
             * \brief Return the marker's name.
             *
             * Returns the name assigned to \a this event / range.
             *
             * \return The name.
             */
            auto get_name() const noexcept -> std::string const&
            {
                return m_name;
            }

            /**
             * \brief Return the marker's name (C string).
             *
             * Returns the name assigned to \a this event / range as a C string.
             *
             * \return The name.
             */
            auto get_c_name() const noexcept -> char const*
            {
                return m_name.c_str();
            }

            /**
             * \brief Return the marker's color.
             *
             * Returns the color assigned to \a this event / range.
             *
             * \return The color.
             */
            auto get_color() const noexcept -> std::uint32_t
            {
                return m_color;
            }

            /**
             * \brief Return the marker's category.
             *
             * Returns the Category assigned to \a this event / range.
             *
             * \return The Category.
             */
            auto get_category() const noexcept -> Category const&
            {
                return m_category;
            }

        protected:
            std::string m_name{"BACTRIA_GENERIC_MARKER"};
            std::uint32_t m_color{bactria::color::orange};
            Category m_category{};
    };

    /**
     * \}
     */
}

#endif
