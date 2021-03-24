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
 * \file Sector.hpp
 * \brief bactria's Sector include file.
 *
 * This file defines the interface for the Sector class. It should not be included directly by the user.
 */

#ifndef BACTRIA_SECTOR_HPP
#   define BACTRIA_SECTOR_HPP

#   include <bactria/detail/Activation.hpp>
#   include <bactria/Plugin.hpp>
#   include <bactria/Tags.hpp>

#   include <functional>
#   include <iostream>
#   include <string>
#   include <type_traits>
#   include <utility>

namespace bactria
{
    /**
     * \defgroup Instrumentation Instrumentation classes
     *
     * These classes enable user-defined instrumentation of code segments.
     * \{
     */

    /**
     * \brief The sector class.
     *
     * This class can be instantiated to instrument portions of the application code.
     * The concrete metrics collected by this class are backend-specific.
     *
     * \sa Phase
     */
    template <typename TTag = Generic>
    class Sector final
    {
    public:
        /**
         * \brief The default constructor.
         *
         * The default constructor will generate a sector with the name \a BACTRIA_GENERIC_SECTOR. This sector will
         * not be entered; this still needs to be done with a (correctly nested) pair of #bactria_Enter() and
         * #bactria_Leave() or ~Sector().
         *
         * \sa bactria_Enter, bactria_Leave, ~Sector
         */
        Sector() = default;

        /**
         * \brief The non-entering constructor.
         *
         * The non-entering constructor will generate a sector with the name \a name. This sector will not be
         * entered; this still needs to be done with a (correctly nested) pair of #bactria_Enter() and
         * #bactria_Leave() or ~Sector().
         *
         * \param sector_name The sector name as it should appear on the output file or visualizer.
         * \sa bactria_Enter, bactria_Leave, ~Sector
         */
        Sector(std::string sector_name)
        : m_name{std::move(sector_name)}
        {
        }

        /**
         * \brief The entering constructor.
         *
         * The entering constructor will generate a sector with the name \a name. This sector will be
         * entered immediately. To leave it, the user can call #bactria_Leave() or wait for ~Sector() to be
         * triggered.
         *
         * \param sector_name The sector name as it should appear on the output file or visualizer.
         * \param source The source file this sector should be assigned to. This should be `__FILE__`.
         * \param lineno The line number of the source file. This should be `__LINE__`.
         * \param caller The surrounding function this sector is constructed in. This should be `__func__`.
         * \sa bactria_Enter, bactria_Leave, ~Sector()
         */
        Sector(std::string sector_name, std::string source, std::uint32_t lineno, std::string caller)
        : m_name{std::move(sector_name)}
        {
            if(detail::is_activated())
            {
                plugin::enter_sector(m_handle, source.c_str(), lineno, caller.c_str());
                m_entered = true;
            }
        }

        /**
         * \brief The copy constructor (deleted).
         *
         * Sectors are not intended to be copied. Thus, the copy constructor is deleted.
         */
        Sector(Sector const&) = delete;

        /**
         * \brief The copy assignment operator (deleted).
         *
         * Sectors are not intended to be copied. Thus, the copy assignment operator is deleted.
         */
        auto operator=(Sector const&) -> Sector& = delete;

        /**
         * \brief The move constructor.
         *
         * Moves the \a other sector into \a this sector. Using \a other after the move results in undefined
         * behaviour.
         *
         * \param other The sector to be moved.
         */
        Sector(Sector&& other)
        : m_name{std::move(other.m_name)}, m_entered{other.m_entered}, m_summary{other.m_summary}
        , m_on_enter{std::move(other.m_on_enter)}, m_on_leave{other.m_on_leave}
        {
            std::swap(m_handle, other.m_handle);
        }

        /**
         * \brief The move assignment operator.
         *
         * Moves the \a rhs sector into \a this sector. Using \a rhs after the move results in undefined behaviour.
         *
         * \param rhs The sector to be moved.
         */
        auto operator=(Sector&& rhs) -> Sector&
        {
            m_name = std::move(rhs.m_name);
            std::swap(m_handle, rhs.m_handle);
            m_entered = rhs.m_entered;
            m_summary = rhs.m_summary;
            m_on_enter = std::move(rhs.m_on_enter);
            m_on_leave = std::move(rhs.m_on_leave);

            return *this;
        }

        /**
         * \brief The destructor.
         *
         * Destructs the sector. If the sector was entered and there was no preceeding call to #bactria_Leave() or
         * leave() the destructor will trigger this functionality before the contents of \a this are deleted. Using
         * \a this after the destructor was triggered results in undefined behaviour.
         * 
         * \sa Sector(), bactria_Enter, bactria_Leave, enter, leave
         */
        ~Sector()
        {
            if(detail::is_activated())
            {
                if(m_entered)
                    leave(__FILE__, __LINE__, __func__);

                if(!m_summary)
                    summary();

                plugin::destroy_sector(m_handle);
            }
        }

        /**
         * \brief Enter the sector.
         *
         * Enters the sector. It is not allowed to enter a sector multiple times without a prior call to leave().
         * Each call to enter() has to be correctly nested with a corresponding call to leave() or ~Sector().
         *
         * \param source The source file where the sector is entered. This should be `__FILE__`.
         * \param lineno The source line where the sector is entered. This should be `__LINE__`.
         * \param caller The function where the sector is entered. This should be `__func__`.
         * \sa bactria_Enter, bactria_Leave, leave, ~Sector
         */
        auto enter(std::string source, std::uint32_t lineno, std::string caller) -> void
        {
            if(detail::is_activated())
            {
                plugin::enter_sector(m_handle, source.c_str(), lineno, caller.c_str());
                m_on_enter();
                m_entered = true;
            }
        }

        /**
         * \brief Leave the sector.
         *
         * Leaves the sector.
         *
         * \param source The source file where the sector is left. This should be `__FILE__`.
         * \param lineno The source line where the sector is left. This should be `__LINE__`.
         * \param caller The function where the sector is left. This should be `__func__`.
         * \sa bactria_Enter, enter, bactria_Leave, Sector()
         */
        auto leave(std::string source, std::uint32_t lineno, std::string caller) -> void
        {
            if(detail::is_activated())
            {
                m_on_leave();
                plugin::leave_sector(m_handle, source.c_str(), lineno, caller.c_str());
                m_entered = false;
            }
        }

        /**
         * \brief Summarize the Sector.
         *
         * Summarizes the Sector's metrics. The exact metrics depend on the back-end. This function is mostly
         * useful for Sectors with the Body tag which allows the back-end to evaluate the individual iterations
         * and generate statistics for the overall loop. If this method has not been called before destruction,
         * the destructor will call this internally.
         */
        auto summary() -> void
        {
            if(detail::is_activated())
            {
                plugin::sector_summary(m_handle);
                m_summary = true;
            }
        }

        /**
         * \brief Define an enter action.
         *
         * Defines an action which is executed **after** the Sector is entered. This allows for injecting user-defined
         * actions that alter program behaviour, such as issuing asynchronous functions. Actions will not
         * be executed if bactria has been deactivated by setting the environment variable `BACTRIA_DEACTIVATE`.
         *
         * \param[in] f The action to be executed **after** entering the Sector.
         * \sa enter, on_leave
         */
        auto on_enter(std::function<void(void)> f) -> void
        {
            if(detail::is_activated())
                m_on_enter = f;
        }

        /**
         * \brief Define a leave action.
         *
         * Defines an action which is executed **before** the Sector is left. This allows for injecting user-defined
         * actions that alter program behaviour, such as synchronization of asynchronous functions. Actions will not
         * be executed if bactria has been deactivated by setting the environment variable `BACTRIA_DEACTIVATE`.
         *
         * \param[in] f The action to be executed **before** leaving the Sector.
         * \sa leave, on_enter
         */
        auto on_leave(std::function<void(void)> f) -> void
        {
            if(detail::is_activated())
                m_on_leave = f;
        }

    private:
        std::string m_name{"BACTRIA_GENERIC_SECTOR"};
        void* m_handle{detail::is_activated() ? plugin::create_sector(m_name.c_str(), TTag::id) : nullptr};
        bool m_entered{false};
        bool m_summary{false};
        std::function<void(void)> m_on_enter = [](){};
        std::function<void(void)> m_on_leave = [](){};
    };

    /**
     * \}
     */
}


#endif
