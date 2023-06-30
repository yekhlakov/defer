# defer - A Go-like deferred lambda invocation for c++

Golang has a very convenient `defer` operator allowing us to, obviously, defer execution of a lambda
until the scope termination.

This header-only library lets us use it in `c++` programs. Just include it and start deferring.

Why do we need it at all? Are destructors insufficient?

For example, when we interoperate with older libraries or OS features and obtain resource handles
that must be cleaned up manually and in unpredictable ways. Setting up a specific wrapper object 
to utilize RAII looks like unnecessary complication.

Consider Win32 call `CreateSolidBrush`. The HBRUSH handle it returns must be deleted with `DeleteObject`.


```
	// Initialize the deferrer
	maxy::control::Defer defer {};

	// Obtain the handle in question
	HBRUSH brush = CreateSolidBrush (RGB (255,128,0));

	// Schedule handle release to be performed at the return.
	defer ([=] () { DeleteObject (brush); });

	// A long chunk of code with multiple returns follows.
	// We don't bother deleting our handle explicitly at each return.

```

See `main.cpp` for more examples.

