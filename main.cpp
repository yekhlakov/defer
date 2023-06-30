#include <iostream>
#include "defer.h"

int main()
{
    // defer the first function
    auto defer = maxy::control::Defer([] () { std::cout << "Defer 1\n"; });

    // defer another function
    defer([] () { std::cout << "Defer 2\n"; });

    // A variable to capture
    int x = 666;

    // Defer a function with capture by value
    defer([x] () { std::cout << "Defer 3, capture by value = " << x << "\n"; });

    // Defer a function with capture by reference
    defer([&x] () { std::cout << "Defer 4, capture by reference = " << x << "\n"; });

    // Change the captured value
    x = 999;

    // Defer a function with capture by value
    defer([=] () { std::cout << "Defer 5, capture all by value = " << x << "\n"; });

    // Defer a function with capture by reference
    defer([&] () { std::cout << "Defer 6, capture all by reference = " << x << "\n"; });

    // Change the value once more
    x = 0;

    // Done
    // The deferred functions should now be invoked in reverse order.
}
