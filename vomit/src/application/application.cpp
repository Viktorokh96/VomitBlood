#include <vomitblood.hpp>
#include <new>

sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "VomitBlood", sf::Style::Titlebar | sf::Style::Close);

void Application::load()
{
	ConfigurationLoader _configLoader;	// Загрузка настроек
	TextureLoader _textureLoader;		// Загрузка текстур
	ObstacleLoader _obstacleLoader;		// Загрузка препятствий
	PartOfMapLoader _partOfMapLoader;	// Загрузка частей карты
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
	config.save();
	delete _menu;
}
