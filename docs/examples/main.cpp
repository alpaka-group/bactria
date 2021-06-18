#include <bactria/bactria.hpp>

auto main() -> int
{
    try
    {
        auto ctx = bactria::Context{};
        auto ctx2 = ctx; // This is okay; Context's internals are reference-counted

        foo();

        // End of scope: ctx is destroyed and automatically shuts down bactria.
    }
    catch(std::runtime_error const& err)
    {
        std::cerr << err.what() << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}