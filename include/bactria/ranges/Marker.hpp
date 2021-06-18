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
 * \brief Marker definitions.
 *
 * This file contains the definition for the Marker class. It should not be included by the
 * user.
 */

#pragma once

#include <bactria/ranges/Category.hpp>
#include <bactria/ranges/Colors.hpp>

#include <cstdint>
#include <string>
#include <utility>

namespace bactria
{
    namespace ranges
    {
        /**
         * \defgroup bactria_ranges_user User API
         * \ingroup bactria_ranges
         *
         * User API for bactria's ranges functionality.
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
            /**
             * \brief Default constructor.
             *
             * Constructs a marker with the name `BACTRIA_GENERIC_MARKER`, the color bactria::ranges::color::orange
             * and a default-initialized category.
             */
            Marker() = default;

            /**
             * \brief Constructor.
             *
             * Constructs a marker with the name \a name, the color \a color and the category \a category.
             *
             * \param name The name shown in the visual output.
             * \param color The color shown in the visual output.
             * \param category The category.
             */
            Marker(std::string name, std::uint32_t color, Category category)
                : m_name{std::move(name)}
                , m_color{color}
                , m_category{std::move(category)}
            {
            }

            /**
             * \brief Copy constructor.
             *
             * Copy-constructs a Marker by copying the internals from \a other. After the copy, `this` and \a other
             * will have copies of the same name, color and category.
             *
             * \param other The Marker to copy from.
             */
            Marker(Marker const& other) = default;

            /**
             * \brief Copy-assignment operator.
             *
             * Copies the contents of \a rhs into `this`. After the copy, `this` and \a rhs will have copies of the
             * same name, color and category.
             *
             * \param rhs The Marker to copy from.
             */
            auto operator=(Marker const& rhs) -> Marker& = default;

            /**
             * \brief Move constructor.
             *
             * Move-constructs a Marker by moving the internals from \a other. After the move, `this` will have taken
             * over the internals from \a other which is in an undefined state afterwards.
             *
             * \param other The Marker to move into `this`.
             */
            Marker(Marker&& other) = default;

            /**
             * \brief Move-assignment operator.
             *
             * Moves the contents of \a rhs into `this`. After the move, `this` will have taken over the internals
             * from \a rhs which is in an undefined state afterwards.
             *
             * \param rhs The Marker to move into `this`.
             */
            auto operator=(Marker&& rhs) -> Marker& = default;

            /**
             * \brief Destroy the Marker object.
             */
            virtual ~Marker() = default;

            /**
             * \brief Return the marker's name.
             *
             * Returns the name assigned to `this` Marker.
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
             * Returns the name assigned to `this` Marker as a C string.
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
             * Returns the color assigned to `this` Marker.
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
             * Returns the Category assigned to `this` Marker.
             *
             * \return The Category.
             */
            auto get_category() const noexcept -> Category const&
            {
                return m_category;
            }

        protected:
            /**
             * \brief The name assigned to the Marker.
             *
             * Users should not rely on this member to be stable. It may change between versions without further
             * notice.
             */
            std::string m_name{"BACTRIA_GENERIC_MARKER"};

            /**
             * \brief The color assigned to the Marker.
             *
             * Users should not rely on this member to be stable. It may change between versions without further
             * notice.
             */
            std::uint32_t m_color{color::orange};

            /**
             * \brief The Category assigned to the Marker.
             *
             * Users should not rely on this member to be stable. It may change between versions without further
             * notice.
             */
            Category m_category{};
        };

        /**
         * \}
         */
    } // namespace ranges
} // namespace bactria
