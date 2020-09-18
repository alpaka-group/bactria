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
             * The region constructor.
             *
             * \param region_name The name of the region as it should appear in
             *                    the output file or visualizer.
             *
             * \param region_type The type of the region. Must be one of
             *                    generic_tag, function_tag or loop_tag
             *
             * \param auto_recording Indicates if the profiling should start
             *                       immediately after construction or not.
             *                       true by default.
             *
             * \param p The phase this region is assigned to. If a nullptr is
             *          passed the region will not belong to any phase. Note
             *          that p is a non-owning pointer; it is expected that
             *          p's lifetime exceeds the region's lifetime.
             */
            region(std::string region_name,
                   region_type region_t = generic_region_type{}, 
                   bool auto_recording = true,
                   const phase* p = nullptr)
            : name{std::move(region_name)}
            , type{region_t}
            , recording{auto_recording}
            , handle{plugin::handle::make_handle(name)}
            , phase_ptr{p}
            {
                if(p != nullptr)
                {
                    // TODO
                }
                
                if(recording)
                    start_recording();
            }

            /**
             * The region destructor. Unless stop_recording() has been
             * called previously it will automatically stop the recording
             * when the region is destroyed.
             */
            ~region() noexcept
            {
                if(recording)
                    stop_recording();
            }

            /**
             * Start the recording. Unless the region is already recording
             * events will be logged from this point forward.
             */
            auto start_recording() -> void
            {
                handle->start_recording();
                recording = true;
            }

            /**
             * Stop the recording. No events will be logged after this method
             * has been called.
             */
            auto stop_recording() -> void
            {
                handle->stop_recording();
                recording = false;
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
            auto record_event(event e) -> void
            {
                handle->record_event(e);
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
            std::string name;
            region_type type;
            bool recording;
            std::unique_ptr<plugin::handle> handle;
            const phase* phase_ptr;
    };
}

#endif
