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

#ifndef BACTRIA_PLUGIN_PRINTF_PHASE_INSTRUMENTATION_HPP
#   define BACTRIA_PLUGIN_PRINTF_PHASE_INSTRUMENTATION_HPP

#   include "Common.hpp"

#   include <cstdint>

auto enter_phase(sector* sec, char const* source, std::uint32_t lineno) -> void;
auto leave_phase(sector* sec, char const* source, std::uint32_t lineno) -> void;
auto phase_summary(sector* sec) -> void;

#endif

