#include <vomitblood.hpp>
#include <new>

sf::RenderWindow window(sf::VideoMode(800, 800), "VomitBlood", sf::Style::Titlebar | sf::Style::Close);

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
