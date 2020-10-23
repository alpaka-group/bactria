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

#ifndef BACTRIA_EVENT_HPP
#define BACTRIA_EVENT_HPP

#include <string>
#include <utility>

/**
 * The bactria user API
 */
namespace bactria
{
    /**
     * Apart from the built-in events the user can record his own events
     * through the region interface. He can either use the generic event
     * class or use one of the derived types for special cases.
     */
    class event
    {
        public:
            event() = default;

            /**
             * The event constructor.
             *
             * \param event_name The event name as it should appear on the
             *                   output file or the visualizer.
             */
            explicit event(std::string event_name)
            : name{std::move(event_name)}
            {}

            event(const event& other) = default;
            auto operator=(const event& rhs) -> event& = default;
            event(event&& other) = default;
            auto operator=(event&& rhs) -> event& = default;

            virtual ~event() = default;

            /**
             * Returns the event name.
             */
            virtual auto get_name() const noexcept -> const std::string&
            {
                return name; 
            }

        protected:
            std::string name = "BACTRIA_GENERIC_EVENT";
    };

    /**
     * This event marks memory (de)allocations.
     */
    class alloc_event : public event {};
    
    /**
     * This event marks memory copies.
     */
    class copy_event : public event {};
    
    /**
     * This event marks communications.
     */
    class comm_event : public event {};
 
    /**
     * This event marks kernel executions.
     */
    class kernel_event : public event {};

    /**
     * This event marks loops.
     */
    class loop_event : public event {};

    /**
     * This event marks memsets.
     */
    class memset_event : public event {};

    /**
     * This event marks synchronization points.
     */
    class sync_event : public event {};
}

#endif
