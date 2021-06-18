auto bar()
{
    using namespace bactria::metrics;

    // Define logical phase and enter it immediately.
    auto p1 = Phase{"first_bar_half", __FILE__, __LINE__, __func__};

    // Define logical phase, but do not enter it.
    auto p2 = Phase{"second_bar_half"};

    // Once successfully constructed this sector will start collecting metrics right away.
    auto s1 = Sector<Function>{"bar", __FILE__, __LINE__, __func__};

    // Non-entering constructor: This sector needs to be entered manually at a later point. It will not collect any
    // metrics right away.
    auto s2 = Sector<Loop>{"some_sector"};

    /*
     * Do some work
     */
    // s2.enter(__FILE__, __LINE__, __func__); // <-- This is very verbose. Fortunately there is a convenience macro:
    bactria_Enter(s2);
    for(auto i = 0; i < 20; ++i)
    {
        /* ... */
    }
    // s2.leave(__FILE__, __LINE__, __func__); // <-- Same as above
    bactria_Leave(s2);

    /* Wrong order! Wrongly nested.
    bactria_Enter(p2);
    bactria_Leave(p1);
    */

    // Right order: Leave first phase and enter second phase
    bactria_Leave(p1);
    bactria_Enter(p2);

    // Collect metrics for every iteration of a loop body
    auto s3 = Sector<Body>{"loop_body"};
    for(auto i = 0; i < 20; ++i)
    {
        bactria_Enter(s3);
        /* Do work */
        bactria_Leave(s3);
    }

    // End of scope: p2 is left automatically
}