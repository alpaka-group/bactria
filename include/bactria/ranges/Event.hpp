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
 * \file Event.hpp
 * \brief Event definitions.
 *
 * This is bactria's event include file. It contains the definition for user-defined events that appear on the
 * visualizer. This file should not be included directly by the user.
 */

#pragma once

#include <bactria/ranges/Category.hpp>
#include <bactria/ranges/Colors.hpp>
#include <bactria/ranges/Marker.hpp>
#include <bactria/ranges/Plugin.hpp>

#include <functional>
#include <string>
#include <utility>

namespace bactria
{
    namespace ranges
    {
        /**
         * \brief The event class.
         * \ingroup bactria_ranges_user
         *
         * The user can record his own events which will appear as special markers on the visualizer. In contrast to
         * a Range, an event denotes a single point in time.
         *
         * \sa Range
         */
        class Event : public Marker
        {
        public:
            /**
             * \brief The default constructor.
             *
             * The default constructor will generate an event with the name \a BACTRIA_GENERIC_EVENT, orange color and
             * the generic Category.
             */
            Event() : Marker("BACTRIA_GENERIC_EVENT", color::bactria_orange, Category{})
            {
            }

            /**
             * \brief The constructor.
             *
             * The constructor will generate an event with the name \a name, the color \a color and the Category \a
             * category.
             *
             * \param name The name as it should appear on the visualizer.
             * \param color The color as it should appear on the visualizer. Needs to be supplied in ARGB format.
             * \param category The category this event should be assigned to. This allows for later filtering.
             */
            Event(std::string name, std::uint32_t color = color::bactria_orange, Category category = Category{})
                : Marker(std::move(name), color, std::move(category))
            {
            }

            /**
             * \brief The copy constructor.
             *
             * The copy constructor will generate a new event with the same properties as the original.
             *
             * \param other The event to copy the properties from.
             */
            Event(const Event& other)
                : Marker(other)
                , m_handle{plugin::activated() ? plugin::create_event(m_color, m_category.get_c_name(), m_category.get_id()) : nullptr}
                , m_action{other.m_action}
            {
            }

            /**
             * \brief The copy assignment operator.
             *
             * The copy assignment operator will generate a new event with the same properties as the original.
             *
             * \param rhs The event to copy the properties from.
             */
            auto operator=(const Event& rhs) -> Event&
            {
                Marker::operator=(rhs);

                if(plugin::activated())
                    m_handle = plugin::create_event(m_color, m_category.get_c_name(), m_category.get_id());
                else
                    m_handle = nullptr;

                m_action = rhs.m_action;

                return *this;
            }

            /**
             * \brief The move constructor.
             *
             * The move constructor will move the contents of the original event into this event. The original event
             * will be in an invalid state; using it is undefined behaviour.
             *
             * \param other The Event to be moved.
             */
            Event(Event&& other) noexcept : Marker(std::move(other)), m_handle{std::exchange(other.m_handle, nullptr)}
            {
                std::swap(m_action, other.m_action);
            }

            /**
             * \brief The move assignment operator.
             *
             * The move assignment operator will move the contents of the original event into \a this event. The
             * original event will be in an invalid state; using it is undefined behaviour.
             *
             * \param rhs The event to be moved.
             */
            auto operator=(Event&& rhs) noexcept -> Event&
            {
                Marker::operator=(std::move(rhs));
                m_handle = std::exchange(rhs.m_handle, nullptr);
                std::swap(m_action, rhs.m_action);

                return *this;
            }

            /**
             * \brief The destructor.
             *
             * The destructor will discard all internal contents of the event. After the call to the destructor the
             * event will be in an invalid state; using it is undefined behaviour.
             */
            ~Event() override
            {
                if(plugin::activated())
                    plugin::destroy_event(m_handle);
            }

            /**
             * \brief Fire the event.
             *
             * Firing the event generates an entry on the visualizer with this event's name, color and category. While
             * the interface requires the source file, the line number and the calling function, this information may
             * not be supported by all back-ends. In this case the parameters will be silently ignored.
             *
             * \param source The source file where the event is fired. Should be `__FILE__`.
             * \param lineno The source line where the event is fired. Should be `__LINE__`.
             * \param caller The surrounding function of the event firing. Should be `__func__`.
             */
            auto fire(std::string source, std::uint32_t lineno, std::string caller) noexcept -> void
            {
                if(plugin::activated())
                {
                    plugin::fire_event(m_handle, m_action().c_str(), source.c_str(), lineno, caller.c_str());
                }
            }

            /**
             * \brief Set a user-defined action for generating the event name.
             *
             * This method allows to specify a user-defined action which generates the name. It will be executed upon
             * firing the event. This method will override the name specified in the constructor.
             *
             * \param a The action to execute upon firing the event.
             * \sa fire
             */
            auto set_action(std::function<std::string(void)> a) noexcept -> void
            {
                m_action = std::move(a);
            }

        private:
            void* m_handle{
                plugin::activated() ? plugin::create_event(m_color, m_category.get_c_name(), m_category.get_id())
                                    : nullptr};
            std::function<std::string(void)> m_action = [this]() { return m_name; };
        };
    } // namespace ranges
} // namespace bactria

/**
 * \brief A macro that fires an event.
 * \ingroup bactria_ranges_user
 *
 * A macro that internally creates an event, fires it and destroys it afterwards. If you want to customize the
 * event's behaviour you will have to manage the event's lifetime and fire operation on your own by instantiating
 * the Event class.
 *
 * \param[in] name     The name of the event as it should later appear on the visualizer.
 * \param[in] color    The color of the event as it should later appear on the visualizer.
 * \param[in] category The Category of the event.
 */
#define bactria_Event(name, color, category)                                                                          \
    {                                                                                                                 \
        auto e = bactria::ranges::Event(name, color, category);                                                       \
        e.fire(__FILE__, __LINE__, __func__);                                                                         \
    }

/**
 * \brief A macro that fires an event with an action.
 * \ingroup bactria_ranges_user
 *
 * A macro that internally creates an event, assigns it an action, fires it and destroys it afterwards. If you want to
 * customize the event's behaviour you will have to manage the event's lifetime and fire operation on your own by
 * instantiating the Event class.
 *
 * \param[in] action   The action generating the event name as it should later appear on the visualizer.
 * \param[in] color    The color of the event as it should later appear on the visualizer.
 * \param[in] category The Category of the event.
 */
#define bactria_ActionEvent(action, color, category)                                                                  \
    {                                                                                                                 \
        auto e = bactria::ranges::Event("BACTRIA_ACTION_EVENT", color, category);                                     \
        e.set_action(action);                                                                                         \
        e.fire(__FILE__, __LINE__, __func__);                                                                         \
    }
