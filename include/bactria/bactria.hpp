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

#ifndef BACTRIA_BACTRIA_HPP
#   define BACTRIA_BACTRIA_HPP

#   include <bactria/Event.hpp>
#   include <bactria/Plugin.hpp>
#   include <bactria/Range.hpp>
#   include <bactria/Phase.hpp>
#   include <bactria/Sector.hpp>

#   include <memory>

namespace bactria
{
    struct Context
    {
        Context(plugin::plugin_handle_t h) noexcept : handle{h}
        {}

        Context(Context const&) noexcept = default;
        auto operator=(Context const&) noexcept -> Context& = default;
        Context(Context&&) noexcept = default;
        auto operator=(Context&&) noexcept -> Context& = default;
        ~Context() = default;

        plugin::plugin_handle_t handle;
    };

    auto initialize() -> std::unique_ptr<Context>
    {
        return std::make_unique<Context>(plugin::load_plugin());
    }

    auto finalize(std::unique_ptr<Context> ctx) noexcept -> void
    {
        plugin::unload_plugin(ctx->handle);
    }
}


#   define bactria_Phase(name) ::bactria::Phase{name, __FILE__, __LINE__, __func__}
#   define bactria_Sector(name, tag) ::bactria::Sector<tag>{name, __FILE__, __LINE__, __func__}
#   define bactria_Enter(sec) sec.enter(__FILE__, __LINE__, __func__)
#   define bactria_Leave(sec) sec.leave(__FILE__, __LINE__, __func__)

#endif
