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

#pragma once

#include <cstdlib>

namespace bactria
{
    namespace detail
    {
        inline auto is_activated() -> bool
        {
            static auto const activated = (std::getenv("BACTRIA_DEACTIVATE") == nullptr);
            return activated;
        }

        inline auto reports_activated() -> bool
        {
            static bool const activated = is_activated() && (std::getenv("BACTRIA_REPORT_PLUGIN") != nullptr);
            return activated;
        }
    } // namespace detail
} // namespace bactria
