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

#ifndef BACTRIA_RANGE_HPP
#   define BACTRIA_RANGE_HPP

#   include <bactria/Colors.hpp>
#   include <bactria/Plugin.hpp>
#   include <bactria/Marker.hpp>

#   include <cstdint>
#   include <string>
#   include <utility>

namespace bactria
{
    class Range : public Marker
    {
    public:
        Range() : Marker("BACTRIA_GENERIC_RANGE", bactria::color::blue, Category{})
        {}

        Range(std::string name, std::uint32_t color = bactria::color::blue, Category category = Category{})
        : Marker(std::move(name), color, std::move(category))
        {}

        Range(Range const& other)
        : Marker(other), m_handle{plugin::create_range(m_name.c_str(), m_color, m_category.id)}
        {}

        auto operator=(Range const& rhs) -> Range&
        {
            Marker::operator=(rhs);
            m_handle = plugin::create_range(m_name.c_str(), m_color, m_category.id);

            return *this;
        }

        Range(Range&&) noexcept = default;
        auto operator=(Range&&) noexcept -> Range& = default;

        ~Range() override
        {
            plugin::destroy_range(m_handle);
        }

        auto start() noexcept -> void
        {
            plugin::start_range(m_handle);
        }

        auto stop() noexcept -> void
        {
            plugin::stop_range(m_handle);
        }

    private:
        void* m_handle{plugin::create_range(m_name.c_str(), m_color, m_category.id)};
    };
}

#endif
