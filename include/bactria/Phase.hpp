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
 * \file Phase.hpp
 * \brief bactria's Phase include file.
 *
 * This file contains the Phase definition. It should not be included directly by the user.
 */

#pragma once

#include <bactria/Plugin.hpp>
#include <bactria/detail/Activation.hpp>

#include <string>
#include <utility>

namespace bactria
{
    /**
     * \ingroup Instrumentation
     * \brief The phase class.
     *
     * Phases are used for structuring the program into logical segments. Sectors
     * can be added to any phase in the program. Like Sectors, Phases have to be
     * correctly nested.
     */
    class Phase
    {
    public:
        /**
         * \brief The default constructor.
         *
         * The default constructor will generate a phase with the name \a BACTRIA_GENERIC_PHASE. This phase will
         * not be entered; this still needs to be done with a (correctly nested) pair of #bactria_Enter() and
         * #bactria_Leave() or ~Phase().
         *
         * \sa bactria_Enter, bactria_Leave, ~Phase
         */
        Phase() = default;

        /**
         * \brief The non-entering constructor.
         *
         * The non-entering constructor will generate a phase with the name \a name. This phase will not be
         * entered; this still needs to be done with a (correctly nested) pair of #bactria_Enter() and
         * #bactria_Leave() or ~Phase().
         *
         * \param name The phase name as it should appear on the output file or visualizer.
         * \sa bactria_Enter, bactria_Leave, ~Phase
         */
        explicit Phase(std::string name) : m_name{std::move(name)}
        {
        }

        /**
         * \brief The entering constructor.
         *
         * The entering constructor will generate a phase with the name \a name. This phase will be
         * entered immediately. To leave it, the user can call #bactria_Leave() or wait for ~Phase() to be
         * triggered.
         *
         * \param name The phase name as it should appear on the output file or visualizer.
         * \param source The source file this phase should be assigned to. This should be `__FILE__`.
         * \param lineno The line number of the source file. This should be `__LINE__`.
         * \param caller The surrounding function this phase is constructed in. This should be `__func__`.
         * \sa bactria_Enter, bactria_Leave, ~Phase()
         */
        Phase(std::string name, std::string source, std::uint32_t lineno, std::string caller) : m_name{std::move(name)}
        {
            if(detail::is_activated())
                enter(std::move(source), lineno, std::move(caller));
        }

        /**
         * \brief The copy constructor (deleted).
         *
         * Phases are not intended to be copied. Thus, the copy constructor is deleted.
         */
        Phase(const Phase&) = delete;

        /**
         * \brief The copy assignment operator (deleted).
         *
         * Phases are not intended to be copied. Thus, the copy assignment operator is deleted.
         */
        auto operator=(const Phase&) -> Phase& = delete;

        /**
         * \brief The move constructor.
         *
         * Moves the \a other phase into \a this phase. Using \a other after the move results in undefined
         * behaviour.
         *
         * \param other The phase to be moved.
         */
        Phase(Phase&& other) : m_name{std::move(other.m_name)}, m_entered{other.m_entered}
        {
            std::swap(m_handle, other.m_handle);
        }

        /**
         * \brief The move assignment operator.
         *
         * Moves the \a rhs phase into \a this phase. Using \a rhs after the move results in undefined behaviour.
         *
         * \param rhs The phase to be moved.
         */
        auto operator=(Phase&& rhs) -> Phase&
        {
            m_name = std::move(rhs.m_name);
            std::swap(m_handle, rhs.m_handle);
            m_entered = rhs.m_entered;

            return *this;
        }

        /**
         * \brief The destructor.
         *
         * Destructs the phase. If the phase was entered and there was no preceeding call to #bactria_Leave() or
         * leave() the destructor will trigger this functionality before the contents of \a this are deleted. Using
         * \a this after the destructor was triggered results in undefined behaviour.
         *
         * \sa Phase, bactria_Enter, bactria_Leave, enter, leave
         */
        ~Phase()
        {
            if(detail::is_activated())
            {
                if(m_entered)
                    leave(__FILE__, __LINE__, __func__);

                plugin::destroy_phase(m_handle);
            }
        }

        /**
         * \brief Enter the phase.
         *
         * Enters the phase. It is allowed to enter a phase multiple times (for example in multiple code locations)
         * as long as there is an equal amount of correctly nested calls to leave(), #bactria_Leave() or ~Phase().
         *
         * \param source The source file where the phase is entered. This should be `__FILE__`.
         * \param lineno The source line where the phase is entered. This should be `__LINE__`.
         * \param caller The function where the phase is entered. This should be `__func__`.
         * \sa bactria_Enter, bactria_Leave, leave, ~Phase
         */
        auto enter(std::string source, std::uint32_t lineno, std::string caller) -> void
        {
            if(detail::is_activated())
            {
                plugin::enter_phase(m_handle, source.c_str(), lineno, caller.c_str());
                m_entered = true;
            }
        }

        /**
         * \brief Leave the phase.
         *
         * Leaves the phase. It is allowed to leave a phase multiple times (for example in multiple code locations)
         * as long as there is an equal amount of correctly nested calls to enter(), #bactria_Enter() or Phase().
         *
         * \param source The source file where the phase is left. This should be `__FILE__`.
         * \param lineno The source line where the phase is left. This should be `__LINE__`.
         * \param caller The function where the phase is left. This should be `__func__`.
         * \sa bactria_Enter, enter, bactria_Leave, Phase()
         */
        auto leave(std::string source, std::uint32_t lineno, std::string caller) -> void
        {
            if(detail::is_activated())
            {
                plugin::leave_phase(m_handle, source.c_str(), lineno, caller.c_str());
                m_entered = false;
            }
        }

    private:
        std::string m_name{"BACTRIA_GENERIC_PHASE"};
        void* m_handle{detail::is_activated() ? plugin::create_phase(m_name.c_str()) : nullptr};
        bool m_entered{false};
    };
} // namespace bactria
