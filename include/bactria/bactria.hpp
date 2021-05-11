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
 * \brief bactria's main include file.
 *
 * This is bactria's main include file. It pulls in all functionality required by the user.
 */

#ifndef BACTRIA_BACTRIA_HPP
#   define BACTRIA_BACTRIA_HPP

#   include <bactria/Colors.hpp>
#   include <bactria/Context.hpp>
#   include <bactria/Event.hpp>
#   include <bactria/Incident.hpp>
#   include <bactria/IncidentRecorder.hpp>
#   include <bactria/Plugin.hpp>
#   include <bactria/Range.hpp>
#   include <bactria/Report.hpp>
#   include <bactria/Phase.hpp>
#   include <bactria/Sector.hpp>

/**
 * \brief A macro that fires an event.
 *
 * A macro that internally creates an event, fires it and destroys it afterwards. If you want to customize the
 * event's behaviour you will have to manage the event's lifetime and fire operation on your own by instantiating
 * the Event class.
 *
 * \param[in] name     The name of the event as it should later appear on the visualizer.
 * \param[in] color    The color of the event as it should later appear on the visualizer.
 * \param[in] category The Category of the event.
 */
#   define bactria_Event(name, color, category) \
    { \
        auto e = bactria::Event(name, color, category); \
        e.fire(__FILE__, __LINE__, __func__); \
    }

/**
 * \brief A macro that fires an event with an action.
 *
 * A macro that internally creates an event, assigns it an action, fires it and destroys it afterwards. If you want to
 * customize the event's behaviour you will have to manage the event's lifetime and fire operation on your own by
 * instantiating the Event class.
 *
 * \param[in] action   The action generating the event name as it should later appear on the visualizer.
 * \param[in] color    The color of the event as it should later appear on the visualizer.
 * \param[in] category The Category of the event.
 */
#   define bactria_ActionEvent(action, color, category) \
    { \
        auto e = bactria::Event("BACTRIA_ACTION_EVENT", color, category); \
        e.set_action(action); \
        e.fire(__FILE__, __LINE__, __func__); \
    }

/**
 * \brief A macro that creates a phase and immediately enters it.
 *
 * A macro that creates a phase and immediately enters it. If you want to create a phase but enter it later use
 * Phase's constructor and the #bactria_Enter() and #bactria_Leave() macros. Note that all phases and sectors have to
 * be correctly nested.
 *
 * \param[in] name The name of the phase as it should later appear in the output or the visualizer.
 * \sa bactria_Enter, bactria_Leave, bactria_Sector, Phase
 */
#   define bactria_Phase(name) ::bactria::Phase{name, __FILE__, __LINE__, __func__}

/**
 * \brief A macro that creates a sector and immediately enters it.
 *
 * A macro that creates a sector and immediately enters it. If you want to create a phase but enter it later use
 * Sector's constructor and the #bactria_Enter() and #bactria_Leave() macros. Note that all phases and sectors have to
 * be correctly nested.
 *
 * \param[in] name The name of the sector as it should later appear in the output or the visualizer.
 * \param[in] tag The tag of the sector.
 * \sa bactria_Enter, bactria_Leave, bactria_Phase, Sector, Generic, Function, Loop, Body
 */
#   define bactria_Sector(name, tag) ::bactria::Sector<tag>{name, __FILE__, __LINE__, __func__}

/**
 * \brief Enter a phase or sector.
 *
 * A macro that enters a phase or sector. Requires a (correctly nested) corresponding call to #bactria_Leave() or
 * the destructor of the phase / sector.
 *
 * \param[in] sec The previously created Phase or Sector object.
 * \sa bactria_Leave, Phase, Sector
 */
#   define bactria_Enter(sec) sec.enter(__FILE__, __LINE__, __func__)

/**
 * \brief Leave a phase or sector.
 *
 * A macro that leaves a phase or sector. Requires a (correctly nested) corresponding call to #bactria_Enter() or
 * the constructor of the phase / sector.
 *
 * \param[in] sec The previously created Phase or Sector object.
 * \sa bactria_Leave, Phase, Sector
 */
#   define bactria_Leave(sec) sec.leave(__FILE__, __LINE__, __func__)

#endif
