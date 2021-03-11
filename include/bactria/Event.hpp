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

#ifndef BACTRIA_EVENT_HPP
#   define BACTRIA_EVENT_HPP

#   include <bactria/Colors.hpp>
#   include <bactria/Plugin.hpp>
#   include <bactria/Record.hpp>


#   include <string>
#   include <utility>

namespace bactria
{
    /**
     * Apart from the built-in events the user can record his own events
     * through the region interface. He can either use the generic event
     * class or use one of the derived types for special cases.
     */
    class Event : public Record
    {
        public:
            Event() : Record("BACTRIA_GENERIC_EVENT", bactria::color::orange, Category{})
            {}

            Event(std::string name, std::uint32_t color = bactria::color::orange, Category category = Category{})
            : Record(std::move(name), color, std::move(category))
            {}

            Event(const Event& other)
            : Record(other)
            , m_handle{plugin::create_event(m_name.c_str(), m_color, m_category.id)}
            {}

            auto operator=(const Event& rhs) -> Event&
            {
                Record::operator=(rhs);
                m_handle = plugin::create_event(m_name.c_str(), m_color, m_category.id);

                return *this;
            }
            
            Event(Event&& other) noexcept = default;
            auto operator=(Event&& rhs) noexcept -> Event& = default;

            ~Event() override
            {
                plugin::destroy_event(m_handle);
            }

            auto fire() noexcept -> void
            {
                plugin::fire_event(m_handle);
            }

        private:
            void* m_handle{plugin::create_event(m_name.c_str(), m_color, m_category.id)};
    };
}

#endif
