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

#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

#include <dlfcn.h>

#include <bactria/event.hpp>

namespace bactria::plugin
{
    class handle
    {
        public:
            static auto make_handle(const std::string&) -> std::unique_ptr<handle>;
            virtual ~handle() noexcept = 0;

            virtual auto start_recording() -> void = 0;
            virtual auto stop_recording() -> void = 0;
            virtual auto record_event(event) -> void = 0;
        protected:
            handle()
            : library_handle{nullptr}
            {}

        private:
            void* library_handle; // The corresponding library file
    };

    handle::~handle() noexcept
    {
        std::cout << "Destructor reached" << std::endl;
        if(library_handle != nullptr)
        {
            std::cout << "Closing library handle." << std::endl;
            if(auto err = dlclose(library_handle); err != 0)
            {
                std::cerr << "FATAL ERROR: dlclose() failed. " << dlerror() << std::endl;
                std::cerr << "Shutting down." << std::endl;
                std::exit(EXIT_FAILURE);
            }
            std::cout << "Library handle closed." << std::endl;
        }
    }

    auto handle::make_handle(const std::string& name) -> std::unique_ptr<handle>
    {
        if(const auto path = std::getenv("BACTRIA_PLUGIN"); path != nullptr)
        {
            if(auto library_handle = dlopen(path, RTLD_NOW); library_handle != nullptr)
            {
                using make_signature = handle* (const std::string&);

                auto plugin_handle = std::unique_ptr<handle>(nullptr);

                if(auto make = reinterpret_cast<make_signature*>(
                                dlsym(library_handle, "plugin_make_handle"));
                    make != nullptr)
                {
                    plugin_handle.reset(make(name));
                    plugin_handle->library_handle = library_handle;
                }
                else
                {
                    std::cerr << "WARNING: Error while loading symbol for "
                              << " make_plugin_handle(): " << dlerror()
                              << std::endl;

                    std::cerr << "bactria will be disabled." << std::endl;

                    return nullptr;
                }

                return plugin_handle;
            }
            else
            {
                std::cerr << "WARNING: Error while loading bactria plugin: "
                          << dlerror()
                          << std::endl;
                std::cerr << "Bactria will be deactivated." << std::endl;
                
                return nullptr;
            }
        }
        else
        {
            std::cerr << "WARNING: No bactria plugin specified. "
                      << "Bactria will be deactivated." << std::endl;
            return nullptr;
        }
    }
}

extern "C" auto plugin_make_handle(const std::string& name) -> bactria::plugin::handle*;
