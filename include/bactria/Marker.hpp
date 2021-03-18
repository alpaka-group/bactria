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

#ifndef BACTRIA_MARKER_HPP
#   define BACTRIA_MARKER_HPP

#   include <bactria/Colors.hpp>
#   include <bactria/Category.hpp>

#   include <cstdint>
#   include <string>
#   include <utility>

namespace bactria
{
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

            virtual auto get_name() const noexcept -> const std::string&
            {
                return m_name;
            }

            virtual auto get_color() const noexcept -> std::uint32_t
            {
                return m_color;
            }

            virtual auto get_category() const noexcept -> const Category&
            {
                return m_category;
            }

        protected:
            std::string m_name{"BACTRIA_GENERIC_MARKER"};
            std::uint32_t m_color{bactria::color::orange};
            Category m_category{};
    };
}

#endif
