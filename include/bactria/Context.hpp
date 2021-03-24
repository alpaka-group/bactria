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

#ifndef BACTRIA_CONTEXT_HPP
#   define BACTRIA_CONTEXT_HPP

#   include <bactria/detail/Activation.hpp>
#   include <bactria/Plugin.hpp>

namespace bactria
{
    namespace detail
    {
        bool bactria_activated = false;
    }

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
        Context() = default;
        Context(Context const&) noexcept = default;
        auto operator=(Context const&) noexcept -> Context& = default;
        Context(Context&&) noexcept = default;
        auto operator=(Context&&) noexcept -> Context& = default;
        
        ~Context()
        {
            if(detail::is_activated())
                plugin::unload_plugin(m_handle);
        }

    private:
        plugin::plugin_handle_t m_handle{detail::is_activated() ? plugin::load_plugin() : plugin::plugin_handle_t{}};
    };
}

#endif
