#include <vomitblood.hpp>
#include <new>

int Application::init()
{
	try {

	} catch (std::bad_alloc bad) {
		return -1;
	}
	
	return 0;
}

void Application::start()
{
}

void Application::dispose()
{
}
