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
 * \file Context.hpp
 * \brief bactria's Context include file.
 *
 * This file defines the Context interface. The user should not include this directly.
 */

#pragma once

#include <bactria/core/Activation.hpp>
#include <bactria/core/Plugin.hpp>
#include <bactria/metrics/Plugin.hpp>
#include <bactria/ranges/Plugin.hpp>
#include <bactria/reports/Plugin.hpp>

#include <utility>

namespace bactria
{
    /**
     * \brief The bactria context.
     *
     * The bactria context. As long as at least one instance of this object exists in the process the user can use
     * bactria's functionality. However, frequent Context creations and destructions should be avoided as they might
     * result in significant overhead.
     */
    class Context final
    {
    public:
        // The plugin handles are reference counted. Copying them around doesn't hurt.

        /**
         * \brief The constructor.
         *
         * Loads the plugins and maintains the plugins' internal states. It is allowed to have multiple Context objects
         * because the plugins are reference counted. They will only be unloaded once the last Context in a process
         * reaches the end of its lifetime.
         *
         * \sa ~Context
         */
        Context() = default;

        /**
         * \brief The copy constructor.
         *
         * Copies a context. Internally, both Context objects will point to the same plugins.
         *
         * \param[in] other The context to copy from.
         */
        Context(Context const& other) noexcept = default;

        /**
         * \brief The copy assignment operator.
         *
         * Copies a context. Internally, both Context objects will point to the same plugins.
         *
         * \param[in] rhs The context to copy from.
         */
        auto operator=(Context const& rhs) noexcept -> Context& = default;

        /**
         * \brief The move constructor.
         *
         * Moves another context into \a this. The state of the original context is undefined afterwards, while \a
         * this will maintain the original state.
         *
         * \param[in,out] other The context to move into \a this.
         * \sa ~Context
         */
        Context(Context&& other) noexcept
            : m_metricsHandle{std::exchange(other.m_metricsHandle, plugin_handle_t{})}
            , m_rangesHandle{std::exchange(other.m_rangesHandle, plugin_handle_t{})}
            , m_reportsHandle{std::exchange(other.m_reportsHandle, plugin_handle_t{})}
        {
        }

        /**
         * \brief The move assignment operator.
         *
         * Moves another context into \a this. The state of the original context is undefined afterwards, while \a
         * this will maintain the original state.
         *
         * \param[in,out] rhs The context to move into \a this.
         */
        auto operator=(Context&& rhs) noexcept -> Context&
        {
            m_metricsHandle = std::exchange(rhs.m_metricsHandle, plugin_handle_t{});
            m_rangesHandle = std::exchange(rhs.m_rangesHandle, plugin_handle_t{});
            m_reportsHandle = std::exchange(rhs.m_reportsHandle, plugin_handle_t{});
            return *this;
        }

        /**
         * \brief The destructor.
         *
         * Destructs the context. If there are multiple Context objects in the process, this will decrement the
         * plugins' reference counters. Otherwise, the plugins are unloaded. In this case, bactria's functionality can
         * no longer be safely used.
         *
         * \sa Context()
         */
        ~Context()
        {
            /* At first glance, this seems wrong. However, on all supported platforms the plugin handle is reference
             * counted (per process), so having multiple contexts loading / unloading the library is not a problem. */
            if(reports::plugin::activated())
                unload_plugin(m_reportsHandle);

            if(ranges::plugin::activated())
                unload_plugin(m_rangesHandle);

            if(metrics::plugin::activated())
                unload_plugin(m_metricsHandle);
        }

    private:
        plugin_handle_t m_metricsHandle{metrics::plugin::activated() ? metrics::plugin::load() : plugin_handle_t{}};
        plugin_handle_t m_rangesHandle{ranges::plugin::activated() ? ranges::plugin::load() : plugin_handle_t{}};
        plugin_handle_t m_reportsHandle{reports::plugin::activated() ? reports::plugin::load() : plugin_handle_t{}};
    };
} // namespace bactria
