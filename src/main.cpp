#include "app.hpp"

#if defined(__linux__) && defined(DEBUG)
#define BACKWARD_HAS_BFD 1
#include <backward.hpp>

backward::SignalHandling sh;
#endif

int main(int argc, char *args[])
{
	App app;
	app.run();

	return 0;
}