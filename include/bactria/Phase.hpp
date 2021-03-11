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

#ifndef BACTRIA_PHASE_HPP
#   define BACTRIA_PHASE_HPP

#   include <bactria/Plugin.hpp>

#   include <string>
#   include <utility>

namespace bactria
{
    /**
     * Phases are used for structuring the program into logical phases. Sectors
     * can be added to any phase in the program. Like Sectors, Phases have to be
     * correctly nested.
     */
    class Phase
    {
        public:
            Phase() = default;

            /**
             * The phase constructor.
             *
             * \param name The phase name as it should appear on the output file or visualizer.
             */
            explicit Phase(std::string name)
            : m_name{std::move(name)}
            {}

            Phase(std::string name, std::string source, std::uint32_t lineno, std::string caller)
            : m_name{std::move(name)}
            {
                enter(std::move(source), lineno, std::move(caller));
            }

            Phase(const Phase&) = delete;
            auto operator=(const Phase&) -> Phase& = delete;
            Phase(Phase&& other) = default;
            auto operator=(Phase&& other) -> Phase& = default;

            ~Phase()
            {
                if(m_entered)
                    leave(__FILE__, __LINE__, __func__);

                plugin::destroy_phase(m_handle);
            }

            auto enter(std::string source, std::uint32_t lineno, std::string caller) -> void
            {
                plugin::enter_phase(m_handle, source.c_str(), lineno, caller.c_str());
                m_entered = true;
            }

            auto leave(std::string source, std::uint32_t lineno, std::string caller) -> void
            {
                plugin::leave_phase(m_handle, source.c_str(), lineno, caller.c_str());
                m_entered = false;
            }

        private:
            std::string m_name{"BACTRIA_GENERIC_PHASE"};
            void* m_handle{plugin::create_phase(m_name.c_str())};
            bool m_entered{false}; 
    };
}

#endif
