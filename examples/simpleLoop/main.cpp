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
        auto ctx = bactria::initialize();

        {
            auto m = bactria_Sector("MAIN FUNCTION", bactria::Function);

            auto p1 = bactria::Phase("SECTOR PHASE");
            bactria_Enter(p1);

            auto r1 = bactria::Range{"HOW EXPENSIVE IS SECTOR CONSTRUCTION / DESTRUCTION"};
            r1.start();
            {
                auto s = bactria_Sector("CONSTRUCTION / DESTRUCTION", bactria::Generic);
            }
            r1.stop();

            auto r2 = bactria::Range{"HOW EXPENSIVE IS SECTOR ENTER / LEAVE"};
            auto s = bactria::Sector<bactria::Generic>{"ENTER / LEAVE"};
            r2.start();
            {
                bactria_Enter(s);
                bactria_Leave(s);
            }
            r2.stop();
            bactria_Leave(p1);

            auto p2 = bactria::Phase{"LOOP PHASE"};
            bactria_Enter(p2);

            auto r3 = bactria::Range{"LOOP"};
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

            auto e = bactria::Event{"LAST EVENT IN MAIN"};
            e.fire();
        }

        bactria::finalize(std::move(ctx));
    }
    catch(std::runtime_error const& err)
    {
        std::cerr << err.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
