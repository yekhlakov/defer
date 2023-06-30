#pragma once

#ifndef _MAXY_CONTROL_DEFER_
#define _MAXY_CONTROL_DEFER_

#include <vector>
#include <functional>

namespace maxy
{
namespace control
{

/*
 * Go-like defer mechanism.
 * The deferred functions are invoked when this Defer object leaves scope and is destroyed.
 * May be useful for automatic cleanup of OS objects that require explicit cleanup calls (fclose, DeleteObject etc)
 */
class Defer
{
public:
    // Type of deferred functions
    using Func_type = std::function<void()>;

private:
    // The functions queued for deferred invocation are kept here
    std::vector<Func_type> fs;

public:
    // The very default constructor
    Defer () = default;

    // Also we may defer a function right at the construction
    Defer (Func_type _f)
    {
	fs.push_back (_f);
    }

    // Defer a function
    Defer & operator() (Func_type _f)
    {
	fs.push_back (_f);

	return *this;
    }

    // At the destruction, invoke all deferred functions in reverse order
    ~Defer ()
    {
	for (auto p = fs.rbegin (); p != fs.rend (); p++)
	{
	    (*p)();
	}
    }
};

} // end namespace control

} // end namespace maxy

#endif // _MAXY_CONTROL_DEFER_
