/* Copyright 2020 Jan Stephan
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
#define BACTRIA_PHASE_HPP

#include <string>
#include <utility>

namespace bactria
{
    /**
     * Phases are used for structuring the program into logical phases. Regions
     * can be added to any phase in the program as long as they are assigned to
     * exactly one phase.
     */
    class phase
    {
        public:
            phase() = default;

            /**
             * The phase constructor.
             *
             * \param phase_name The phase name as it should appear on the
             *                   output file or visualizer.
             */
            explicit phase(std::string phase_name)
            : name{std::move(phase_name)}
            {}

            phase(const phase&) = delete;
            auto operator=(const phase&) -> phase& = delete;
            phase(phase&& other) = default;
            auto operator=(phase&& other) -> phase& = default;

            ~phase() = default;

            /**
             * Returns the phase name.
             */
            auto get_name() const noexcept -> const std::string&
            {
                return name;
            }

        private:
            std::string name = "BACTRIA_GENERIC_PHASE";
    };
}

#endif
