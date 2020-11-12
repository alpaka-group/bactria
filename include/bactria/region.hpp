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

#ifndef BACTRIA_REGION_HPP
#define BACTRIA_REGION_HPP

#include <memory>
#include <string>
#include <utility>

#include <bactria/event.hpp>
#include <bactria/phase.hpp>
#include <bactria/plugin.hpp>

/**
 * \namespace bactria
 *
 * The bactria user API
 */
namespace bactria
{
    /**
     * Base region type. Not intended for direct usage; use one of the derived
     * types instead.
     */
    struct region_type
    {};

    /**
     * Generic region type. Use this if no other tags fit your purpose.
     */
    struct generic_region_type : public region_type {};

    /**
     * Type indicating that the recorded region is a critical code path.
     */
    struct critical_region_type : public region_type {};

    /**
     * Type indicating that the recorded region is a function.
     */
    struct function_region_type : public region_type {};
    
    /**
     * Type indicating that the recorded region is a loop.
     */
    struct loop_region_type : public region_type {};
    
    /**
     * A region
     */
    class region final
    {
        public:
            /**
             * \brief The default constructor.
             *
             * The default constructor is intended to be used by containers or
             * similar use cases. However, it can also be used directly. It
             * has the following behaviour:
             *
             * - The name passed to the plugin will be
             *   `BACTRIA_GENERIC_REGION`.
             * - The region will be assigned a `generic_region_type`.
             * - If the plugin was not loaded before it will be loaded by
             *   calling this constructor.
             */
            region() = default;

            /**
             * \brief The string constructor.
             *
             * This constructor is intended for use cases where the region type
             * does not matter. It will default to `generic_region_type`. If the
             * plugin was not loaded before it will be loaded by calling this
             * constructor.
             *
             * \param region_name The name of the region as it should appear in
             *                    the output file or visualizer.
             */
            explicit region(std::string region_name)
            : name{std::move(region_name)}
            {}

            /**
             * \brief The string and type constructor.
             *
             * Use this constructor if you need a specialized region type. If
             * the plugin was not loaded before it will be loaded by the call
             * to this constructor.
             *
             * \param region_name The name of the region as it should appear in
             *                    the output file or visualizer.
             *
             * \param region_type The type of the region. Must be one of
             *                    generic_tag, function_tag or loop_tag
             */
            region(std::string region_name, region_type region_t)
            : name{std::move(region_name)}
            , type{std::move(region_t)}
            {}

            /**
             * \brief The copy constructor.
             *
             * Copying regions is prohibited; regions are intended to be
             * unique.
             */
            region(const region&) = delete;

            /**
             * \brief The copy assignment operator.
             *
             * Copying regions is prohibited; regions are intended to be
             * unique.
             */
            auto operator=(const region&) -> region& = delete;

            /**
             * \brief The move constructor.
             *
             * Regions are intended to be unique. This means that moving
             * regions is allowed. Moving a region will invalidate it since
             * the internal state is transferred to the new region.
             *
             * \param other The region from which this region is constructed.
             */
            region(region&& other) = default;

            /**
             * \brief The move assignment operator.
             *
             * Regions are intended to be unique. This means that moving
             * regions is allowed. Moving a region will invalidate it since
             * the internal state is transferred to the new region.
             *
             * \param rhs The region moved to this region.
             */
            auto operator=(region&& rhs) -> region& = default;

            /**
             * The region destructor. Unless stop_recording() has been
             * called previously it will automatically stop the recording
             * when the region is destroyed.
             */
            ~region() noexcept
            {
                if(recording)
                    stop_recording();

                plugin::destroy_region(region_handle);
                plugin::unload_plugin(plugin_handle);
            }

            /**
             * Start the recording. Unless the region is already recording
             * events will be logged from this point forward.
             */
            auto start_recording() -> void
            {
                if(!recording)
                {
                    plugin::start_recording(region_handle);
                    recording = true;
                }
            }

            /**
             * Stop the recording. No events will be logged after this method
             * has been called.
             */
            auto stop_recording() -> void
            {
                if(recording)
                {
                    plugin::stop_recording(region_handle);
                    recording = false;
                }
            }

            /**
             * Record a specific scope, for example a loop. All events inside
             * the provided scope will be recorded.
             *
             * \param s    The scope that will be recorded. Must be an
             *             executable object, for example a lambda function or
             *             a functor.
             * 
             * \param args The scope's parameters.
             */
            template <typename Scope, typename ... Args>
            auto record_scope(Scope s, Args ... args) -> void
            {
                start_recording();
                s(args...);
                stop_recording();
            }

            /**
             * Record a user-defined event.
             */
            auto record_event(event& e) -> void
            {
                plugin::record_event(region_handle, e.event_handle);
            }

            /**
             * Returns the region name.
             */
            auto get_name() const noexcept -> const std::string&
            {
                return name;
            }

            /**
             * Returns the region type.
             */
            auto get_type() const noexcept -> region_type
            {
                return type;
            }

            /**
             * Returns if events are currently being recorded.
             */
            auto is_recording() const noexcept -> bool
            {
                return recording;
            }

            /**
             * Assigns the region to a phase.
             *
             * \param p The phase the region is assigned to.
             */
            auto set_phase(const phase* p) noexcept -> void
            {
                phase_ptr = p;
            }

            /**
             * Returns the phase the region is assigned to.
             */
            auto get_phase() const noexcept -> const phase*
            {
                return phase_ptr;
            }
        
        private:
            std::string name {"BACTRIA_GENERIC_REGION"};
            region_type type {generic_region_type{}};
            bool recording {false};

            plugin::plugin_handle_t plugin_handle{plugin::load_plugin()};

            void* region_handle{plugin::create_region(name.c_str())};
            const phase* phase_ptr {nullptr};
    };
}

#endif
