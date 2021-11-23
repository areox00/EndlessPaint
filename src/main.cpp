#include "app.hpp"

#include <sstream>
#include <iostream>

#ifdef __linux__ 

#include <signal.h>
#include <execinfo.h>
#include <unistd.h>

void signalHandler(int sig) 
{
	// todo: simple message boxes like SDL_ShowSimpleMessageBox();
    std::stringstream ss;
    ss << "PROGRAM CRASH, signal " << sig << "\nSee stderr for more info.";
	std::cout << ss.str() << "\n";
    void *array[15];
    size_t size;
    size = backtrace(array, 15);
    backtrace_symbols_fd(array, size, STDERR_FILENO);
    
    exit(-1);
}

#endif

int main(int argc, char *args[])
{
	#ifdef __linux__ 
	signal(SIGSEGV, signalHandler);
	#endif

	App app;
	app.run();

	return 0;
}