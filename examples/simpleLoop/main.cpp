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

#include <bactria/bactria.hpp>

#include <cstdlib>
#include <chrono>
#include <iostream>
#include <thread>
#include <utility>

auto main() -> int
{
    try
    {
        /* Initialize bactria. This is required once per process and before any other bactria functionality is used. */
        auto ctx = bactria::initialize();

        {
            /* Instrument the main function. Using the bactria_Sector macro will create a sector and immediately start
             * instrumentation. Instrumentation will stop once the sector is no longer in scope. Note that any sectors
             * or phases that were created afterwards must be correctly nested, i.e. stop instrumentation before m's
             * destructor is triggered.
             *
             * The alternative to the bactria_Sector macro is to use manual enter & leave; see below. */
            auto m = bactria_Sector("MAIN FUNCTION", bactria::Function);

            /* Create a logical phase. This is used to assign sectors to logical sections of the program. Certain
             * backends will use this information to collect metrics in another way. */
            auto p1 = bactria::Phase("SECTOR PHASE");

            /* The bactria_Enter macro will start instrumentation inside a phase or sector. Ideally it is accompanied
             * by a corresponding bactria_Leave macro, but leaving the scope works as well. Note that all pairs of
             * bactria_Enter / bactria_Leave have to be correctly nested. */
            bactria_Enter(p1);

            /* Create a range. Ranges are markers that improve visualization and are completely independent of sectors
             * and phases. Ranges can be used to visualize a time span inside the program. Starting and stopping
             * ranges does not require any special ordering. */
            auto r1 = bactria::Range{"HOW EXPENSIVE IS SECTOR CONSTRUCTION / DESTRUCTION"};
            r1.start();
            {
                auto s = bactria_Sector("CONSTRUCTION / DESTRUCTION", bactria::Generic);
            }
            r1.stop();

            /* Ranges take an optional second parameter for the color. This has to be supplied in ARGB format, e.g.
             * 0xFF000000 for the color black. A number of colors are predefined in <bactria/Colors.hpp>. */
            auto r2 = bactria::Range{"HOW EXPENSIVE IS SECTOR ENTER / LEAVE", bactria::color::green };

            /* Instrument a generic sector of the code. */
            auto s = bactria::Sector<bactria::Generic>{"ENTER / LEAVE"};
            r2.start();
            {
                bactria_Enter(s);
                bactria_Leave(s);
            }
            r2.stop();

            /* Leave the phase p1. */
            bactria_Leave(p1);

            auto p2 = bactria::Phase{"LOOP PHASE"};
            bactria_Enter(p2);

            auto r3 = bactria::Range{"LOOP"};

            /* Create a loop sector. This will instrument the whole loop but not any individual iterations. */
            auto l = bactria::Sector<bactria::Loop>{"LOOP SECTOR"};
            r3.start();
            bactria_Enter(l);
            for(auto i = 0; i < 20; ++i)
            {
                std::cout << "Hello, World! " << i << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            bactria_Leave(l);
            r3.stop();

            auto r4 = bactria::Range{"LOOP BODY"};

            /* Instrument the loop body. Each iteration will be instrumented separately. */
            auto b = bactria::Sector<bactria::Body>{"LOOP BODY"};
            r4.start();
            for(auto i = 0; i < 20; ++i)
            {
                bactria_Enter(b);
                std::cout << "Hello, Body! " << i << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                bactria_Leave(b);
            }
            r4.stop();
            b.summary();

            bactria_Leave(p2);

            /* Events are another type of marker that denote a single point in time. They can be freely
             * combined with Ranges. */
            auto e = bactria::Event{"LAST EVENT IN MAIN"};
            e.fire();
        }

        /* Let bactria clean up its internals. This is required once per process. */
        bactria::finalize(std::move(ctx));
    }
    catch(std::runtime_error const& err)
    {
        /* bactria will throw a std::runtime_error in case of any internal error. */
        std::cerr << err.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
