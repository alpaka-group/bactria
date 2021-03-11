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

#ifndef BACTRIA_SECTOR_HPP
#   define BACTRIA_SECTOR_HPP

#   include <bactria/Plugin.hpp>
#   include <bactria/Tags.hpp>

#   include <iostream>
#   include <string>
#   include <type_traits>
#   include <utility>

namespace bactria
{
    template <typename TTag>
    class Sector final
    {
    public:
        Sector() = default;

        Sector(std::string sector_name)
        : m_name{std::move(sector_name)}
        {
        }

        Sector(std::string sector_name, std::string source, std::uint32_t lineno, std::string caller)
        : m_name{std::move(sector_name)}
        {
            plugin::enter_sector(m_handle, source.c_str(), lineno, caller.c_str());
            m_entered = true;
        }

        Sector(Sector const&) = delete;
        auto operator=(Sector const&) -> Sector& = delete;

        Sector(Sector&&) = default;
        auto operator=(Sector&&) -> Sector& = default;

        ~Sector()
        {
            if(m_entered)
                leave(__FILE__, __LINE__, __func__);

            if(!m_summary)
                summary();

            plugin::destroy_sector(m_handle);
        }

        auto enter(std::string source, std::uint32_t lineno, std::string caller) -> void
        {
            plugin::enter_sector(m_handle, source.c_str(), lineno, caller.c_str());
            m_entered = true;
        }

        auto leave(std::string source, std::uint32_t lineno, std::string caller) -> void
        {
            plugin::leave_sector(m_handle, source.c_str(), lineno, caller.c_str());
            m_entered = false;
        }

        auto summary() -> void
        {
            plugin::sector_summary(m_handle);
            m_summary = true;
        }

    private:
        std::string m_name{"BACTRIA_GENERIC_SECTOR"};
        void* m_handle{plugin::create_sector(m_name.c_str(), TTag::id)};
        bool m_entered{false};
        bool m_summary{false};
    };
}


#endif
