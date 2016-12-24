#include <vomitblood.hpp>
#include <new>

sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "VomitBlood", sf::Style::Titlebar | sf::Style::Close);

void Application::load()
{
	PartOfMapLoader* _partOfMapLoader;
	TextureLoader* _textureLoader;
	ObstacleLoader* _obstacleLoader;

	_textureLoader = new TextureLoader();
	_obstacleLoader = new ObstacleLoader(); // Загружаются препятствия
	_partOfMapLoader = new PartOfMapLoader(); // Загружаются части карты
	delete _textureLoader;
	delete _obstacleLoader;
	delete _partOfMapLoader;
	return;
}

int Application::init()
{
	try 
	{
		load(); // Загрузка препятствий, карт, тесктур и т.д.
		_menu = new MenuController();
	} 
	catch (std::bad_alloc &ex) 
	{
		cerr << "Bad allocation of Loaders!" << endl;
		cerr << ex.what() << endl;
		return -1;
	}
	catch(LoaderException &ex)
	{
		cerr << ex.what() << endl;
		return -1;
	}

	window.setPosition(sf::Vector2i(0,0));
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	
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
