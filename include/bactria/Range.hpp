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
 * \file Range.hpp
 * \brief bactria's Range include file.
 *
 * This file contains the definition of the Range class. It should not be included directly by the user.
 */

#pragma once

#include <bactria/Colors.hpp>
#include <bactria/Marker.hpp>
#include <bactria/Plugin.hpp>
#include <bactria/detail/Activation.hpp>

#include <cstdint>
#include <string>
#include <utility>

namespace bactria
{
    /**
     * \ingroup Markers
     * \brief The range class.
     *
     * The range class is intended for improving the user's visualization experience. By using a range the user can
     * define time spans that will be highlighted in the visualizer (if supported by the corresponding back-end).
     * Back-ends which do not support user-defined visualization will silently ignore any user-defined ranges.
     *
     * Unlike sectors, ranges can freely overlap and do not need to be correctly nested.
     *
     * This class can be inherited from to create ranged objects. The objects' lifetimes will then be highlighted in
     * the visualizer.
     *
     * \sa Event
     */
    class Range : public Marker
    {
    public:
        /**
         * \brief The default constructor.
         *
         * Constructs a Range with the name \a BACTRIA_GENERIC_RANGE, the color \a bactria::color::blue and the
         * default Category. It will not be started automatically.
         *
         * \sa ~Range, start, stop, Category
         */
        Range() : Marker("BACTRIA_GENERIC_RANGE", bactria::color::bactria_cyan, Category{})
        {
        }

        /**
         * \brief The constructor.
         *
         * Constructs a Range with the name \a name, the color \a color and the Category \a category.
         *
         * \param name The name of the range as it should be shown on the visualizer.
         * \param color The range's color in ARGB format as it should be shown on the visualizer.
         *              Default: bactria::color::bactria_cyan.
         * \param category The range's category. Default: bactria's default category.
         * \param autostart If \a true start the range on construction. Default: \a true.
         *
         * \sa ~Range, start, stop, Category
         */
        Range(
            std::string name,
            std::uint32_t color = bactria::color::cyan,
            Category category = Category{},
            bool autostart = true)
            : Marker(std::move(name), color, std::move(category))
        {
            if(autostart && detail::is_activated())
                start();
        }

        /**
         * \brief The copy constructor.
         *
         * Constructs a Range with the properties of the \a other Range. If \a other is already started \a this will
         * be started on construction. Otherwise, \a this will not be started on construction.
         *
         * \param other The Range to copy from.
         *
         * \sa ~Range, start, stop
         */
        Range(Range const& other)
        : Marker(other), m_handle{detail::is_activated() ? plugin::create_range(m_name.c_str(), m_color, m_category.get_c_name(), m_category.get_id()) : nullptr}
        , m_started{other.m_started}
        {
            if(m_started && detail::is_activated())
                plugin::start_range(m_handle);
        }

        /**
         * \brief The copy assignment operator.
         *
         * Copies the properties of the \a rhs Range. If \a rhs is already started \a this will be started by the
         * assignment. Otherwise, \a this will not be started by the assignment.
         *
         * \param rhs The Range to copy from.
         *
         * \sa start, stop
         */
        auto operator=(Range const& rhs) -> Range&
        {
            Marker::operator=(rhs);
            if(detail::is_activated())
            {
                m_handle = plugin::create_range(m_name.c_str(), m_color, m_category.get_c_name(), m_category.get_id());
                m_started = rhs.m_started;

                if(m_started)
                    plugin::start_range(m_handle);
            }

            return *this;
        }

        /**
         * \brief The move constructor.
         *
         * Constructs a Range by moving the properties of the \a other Range into \a this. If \a other is already
         * started \a this will keep running. Otherwise, \a this will not be started on construction.
         *
         * After construction \a other will be in an undefined state.
         *
         * \sa ~Range, start, stop
         */
        Range(Range&& other) noexcept : Marker(std::forward<Range>(other))
        {
            std::swap(m_handle, other.m_handle);
            std::swap(m_started, other.m_started);
        }

        /**
         * \brief The move assignment operator.
         *
         * Moves the properties of the \a other Range into \a this. If \a other is already started \a this will keep
         * running. Otherwise, \a this will not be started by the assignment.
         *
         * After the assignment \a other will be in an undefined state.
         *
         * \sa ~Range, start, stop
         */
        auto operator=(Range&& rhs) noexcept -> Range&
        {
            Marker::operator=(std::forward<Range>(rhs));
            std::swap(m_handle, rhs.m_handle);
            std::swap(m_started, rhs.m_started);

            return *this;
        }

        /**
         * \brief The destructor.
         *
         * Destructs the Range. If the Range was running until this point the destructor will end it automatically.
         * After destruction \a this will be in an undefined state and needs to be reinitialized before being used
         * again.
         */
        ~Range() override
        {
            if(detail::is_activated())
            {
                stop();
                plugin::destroy_range(m_handle);
            }
        }

        /**
         * \brief Manual start.
         *
         * Manually starts the Range. If \a this was already started before the method will do nothing.
         */
        auto start() noexcept -> void
        {
            if(!m_started && detail::is_activated())
            {
                plugin::start_range(m_handle);
                m_started = true;
            }
        }

        /**
         * \brief Manual stop.
         *
         * Manually stops the range. If \a this was not running before the method will do nothing.
         */
        auto stop() noexcept -> void
        {
            if(m_started && detail::is_activated())
            {
                plugin::stop_range(m_handle);
                m_started = false;
            }
        }

        /**
         * \brief Query status.
         *
         * \return If \a true then \a this has been started and can be stopped.
         */
        auto is_running() const noexcept -> bool
        {
            return m_started;
        }

    private:
        void* m_handle{
            detail::is_activated()
                ? plugin::create_range(m_name.c_str(), m_color, m_category.get_c_name(), m_category.get_id())
                : nullptr};
        bool m_started{false};
    };
} // namespace bactria
