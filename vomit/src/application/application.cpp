#include <vomitblood.hpp>
#include <new>

sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "VomitBlood", sf::Style::Titlebar | sf::Style::Close);

int Application::init()
{
	try {
		_game = new GameController();
	} catch (std::bad_alloc bad) {
		return -1;
	}
	
	return 0;
}

void Application::start()
{
	_game->startGame();
}

void Application::dispose()
{
	delete _game;
}
