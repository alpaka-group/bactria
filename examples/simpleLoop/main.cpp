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

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <utility>

auto main() -> int
{
    try
    {
        /* Initialize bactria. This is required once per process and before any other bactria functionality is used. */
        auto ctx = bactria::Context{};

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
             * ranges does not require any special ordering. By default, ranges are started on construction. This
             * can be switched off by setting the constructor's autostart parameter to false. */
            auto r1 = bactria::Range{"HOW EXPENSIVE IS SECTOR CONSTRUCTION / DESTRUCTION"};
            {
                auto s = bactria_Sector("CONSTRUCTION / DESTRUCTION", bactria::Generic);
            }

            /* Ranges can be stopped manually. If a range goes out of scope before being stopped, the destructor
             * will stop the range. */
            r1.stop();


            /* Instrument a generic sector of the code. */
            auto s = bactria::Sector<bactria::Generic>{"ENTER / LEAVE"};

            /* Ranges take an optional second parameter for the color. This has to be supplied in ARGB format, e.g.
             * 0xFF000000 for the color black. A number of colors are predefined in <bactria/Colors.hpp>. */
            auto r2 = bactria::Range{"HOW EXPENSIVE IS SECTOR ENTER / LEAVE", bactria::color::bactria_green};
            {
                bactria_Enter(s);
                bactria_Leave(s);
            }
            r2.stop();

            /* Leave the phase p1. */
            bactria_Leave(p1);

            auto p2 = bactria::Phase{"LOOP PHASE"};
            bactria_Enter(p2);

            /* Create a loop sector. This will instrument the whole loop but not any individual iterations. */
            auto l = bactria::Sector<bactria::Loop>{"LOOP SECTOR"};
            auto r3 = bactria::Range{"LOOP"};
            bactria_Enter(l);
            for(auto i = 0; i < 20; ++i)
            {
                std::cout << "Hello, World! " << i << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            bactria_Leave(l);
            r3.stop();


            /* Instrument the loop body. Each iteration will be instrumented separately. */
            auto b = bactria::Sector<bactria::Body>{"LOOP BODY"};
            auto r4 = bactria::Range{"LOOP BODY"};

            /* Sectors can be configured to execute user-defined code after entering and/or before leaving
             * a sector. */
            b.on_leave([]() { std::cout << "Synchronizing..." << std::endl; });
            for(auto i = 0; i < 20; ++i)
            {
                bactria_Enter(b);
                std::cout << "Hello, Body! " << i << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                bactria_Leave(b);
            }
            r4.stop();

            /* Evaluate the loop iterations. If summary() is not called at at this point the iterations will
             * be evaluated once the destructor of the Sector is triggered. */
            b.summary();

            bactria_Leave(p2);

            /* Events are another type of marker that denote a single point in time. They can be freely
             * combined with Ranges. */
            bactria_Event("EVENT IN MAIN", bactria::color::bactria_orange, bactria::Category{});

            /* You can also define an action event with an action that generates the name. The action will only be
             * executed if bactria is activated. */
            bactria_ActionEvent(
                []() { return "GENERATED EVENT"; },
                bactria::color::bactria_turquoise,
                bactria::Category{});

            auto avgLoopTime = 0.0;

            /* Another loop example: How to define and pass user-defined data */
            using clock = std::chrono::high_resolution_clock;

            /* Set up the recorder. We need to define all intermediate types used by our recorder. */
            using Recorder = bactria::IncidentRecorder<
                typename clock::time_point,
                typename std::chrono::nanoseconds::rep,
                bactria::Incident<double>,
                bactria::Incident<int>,
                bactria::Incident<int>>;
            auto ir = Recorder{};

            /* Extract record type from recorder. Our functors can use this to access the recorded values. */
            using Record = typename Recorder::record_t;

            for(auto i = 0; i < 20; ++i)
            {
                // Start timer
                ir.record_step([](Record& r) {
                    // Store the clock::time_point in the recorder. The index corresponds to the element order defined
                    // in the using Recorder = ... directive above.
                    r.store<0>(clock::now());
                });

                // Stop timer
                ir.record_step([](Record& r) {
                    // Load the clock::time_point from the recorder.
                    auto const start = r.load<0>();
                    auto const end = clock::now();
                    auto const dur = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

                    // Store the nanoseconds
                    r.store<1>(dur.count());
                });

                // Do something else with no storage requirements
                ir.record_step([]() { std::cout << "Something else..." << std::endl; });

                // Calculate average
                ir.record_step([&](Record& r) {
                    // Load the nanoseconds
                    auto const dur = r.load<1>();
                    avgLoopTime += dur;

                    std::cout << "Hello, Incident!" << std::endl;

                    if(i > 2 && (i + 1) % 5 == 0)
                    {
                        auto const avg = avgLoopTime / 5.0;
                        avgLoopTime = 0.0;

                        // Save three different incidents we are interested in
                        r.store<2>(bactria::make_incident("Average", avg));
                        r.store<3>(bactria::make_incident("Step begin", i - 5 + 1));
                        r.store<4>(bactria::make_incident("Step end", i + 1));

                        // Generate a report. The string (without any extensions) may be used to generate a filename
                        // Make sure you include all incident indices you are interested in.
                        // Repeated calls to this function with the same name string will append to the already
                        // existing file (if any).
                        r.submit_report<2, 3, 4>("loop_average");
                    }
                });
            }
        }

        /* Let bactria clean up its internals. This is done automatically once a Context reaches the end of its
         * lifetime. */
    }
    catch(std::runtime_error const& err)
    {
        /* bactria will throw a std::runtime_error in case of any internal error. */
        std::cerr << err.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
