auto baz()
{
    using namespace bactria::reports;

    using clock = std::high_resolution_clock;

    // Define all types which are stored between recording steps. The last type must be an Incident
    using Recorder = bactria::reports::IncidentRecorder<
        typename clock::time_point,
        typename std::chrono::nanoseconds::rep,
        bactria::reports::Incident<double>,
        bactria::reports::Incident<int>,
        bactria::reports::Incident<int>>;
    auto ir = Recorder{};

    // Extract record type from recorder. Our functors can use this to access the recorded values.
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
                r.store<2>(bactria::reports::make_incident("Average", avg));
                r.store<3>(bactria::reports::make_incident("Step begin", i - 5 + 1));
                r.store<4>(bactria::reports::make_incident("Step end", i + 1));

                // Generate a report. The string (without any extensions) may be used to generate a filename
                // Make sure you include all incident indices you are interested in.
                // Repeated calls to this function with the same name string will append to the already
                // existing file (if any).
                r.submit_report<2, 3, 4>("loop_average");
            }
        });
    }
}