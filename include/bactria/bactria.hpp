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
 * \file bactria.hpp
 * \brief Main include file. Users must (only) include this file.
 *
 * This is bactria's main include file. It pulls in all functionality required by the user.
 */

#pragma once

#include <bactria/core/Activation.hpp>
#include <bactria/core/Context.hpp>
#include <bactria/metrics/Phase.hpp>
#include <bactria/metrics/Sector.hpp>
#include <bactria/metrics/Tags.hpp>
#include <bactria/ranges/Category.hpp>
#include <bactria/ranges/Colors.hpp>
#include <bactria/ranges/Event.hpp>
#include <bactria/ranges/Marker.hpp>
#include <bactria/ranges/Range.hpp>
#include <bactria/reports/Incident.hpp>
#include <bactria/reports/IncidentRecorder.hpp>
#include <bactria/reports/Report.hpp>