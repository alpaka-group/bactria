auto foo()
{
    using namespace bactria::ranges;

    // After construction func_range is immediately started.
    auto func_range = Range{"Function foo()", color::orange};

    // Construct an event belonging to a category.
    auto cat_func_call = Category{/* id = */ 42, /* name = */ "function call"};
    auto call_event = Event{"Called bar()", color::green, cat_func_call};
    
    // Call bar once
    bar();
    call_event.fire(__FILE__, __LINE__, __func__);

    // Call bar again -- will show up as separate event on profiler
    bar();
    call_event.fire(__FILE__, __LINE__, __func__);

    // For one-time events there is a convenience macro that removes the __FILE__ __LINE__ __func__ boilerplate
    baz();    
    bactria_Event("Called baz()", color::blue, cat_func_call);

    // Ranges can overlap
    auto r1 = Range{"Some range", color::red};
    auto r2 = Range{"Another range", color::cyan};

    // Depending on condition one range is stopped now, the other when it leaves the scope.
    if(condition)
        r1.stop();
    else
        r2.stop();

    // End of scope: func_range and r1 or r2 are automatically stopped.
}