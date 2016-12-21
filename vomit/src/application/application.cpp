#include <vomitblood.hpp>
#include <new>

sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "VomitBlood", sf::Style::Titlebar | sf::Style::Close);

int Application::init()
{
	try {
		_menu = new MenuController();
	} catch (std::bad_alloc bad) {
		return -1;
	}

	window.setPosition(sf::Vector2i(0,0));
	
	return 0;
}

void Application::start()
{
	_menu->startMenu();
}

void Application::dispose()
{
	delete _menu;
}
