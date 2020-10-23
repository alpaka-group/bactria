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

#include <iostream>
#include <string>

#include <bactria/plugin.hpp>

namespace bactria::plugin
{
    class printf_handle : public handle
    {
        public:
            printf_handle(std::string handle_name)
            : handle()
            , name{std::move(handle_name)}
            {
                std::cout << name << " initialized.\n";
            }

            [[gnu::destructor]]
            ~printf_handle() noexcept override
            {
                std::cout << "printf dtor reached\n";
            }

            auto start_recording() -> void override
            {
                std::cout << "Entering " << name << '\n';
            }

            auto stop_recording() -> void override
            {
                std::cout << "Leaving " << name << '\n';
            }

            auto record_event(event e) -> void override
            {
                std::cout << "Event " << e.get_name() << " reached\n";
            }

        private:
            std::string name;
    };
}

extern "C" auto plugin_make_handle(std::string name) -> bactria::plugin::handle*
{
    return new bactria::plugin::printf_handle(std::move(name));
}
