#include <vomitblood.hpp>
#include <new>

sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "VomitBlood", sf::Style::Titlebar | sf::Style::Close);

void Application::load()
{
	//PartOfMapLoader* _partOfMapLoader;
	ObstacleLoader* _obstacleLoader;
	try
	{
		_obstacleLoader = new ObstacleLoader(); // Загружаются препятствия
		//_partOfMapLoader = new PartOfMapLoader(); // Загружаются части карты
		delete _obstacleLoader;
		//delete _partOfMapLoader;
	}	
	/*ПЕРЕМЕСТИТЬ В init(), КОГДА БУДУТ ПРАВИЛЬНО ЗАГРУЖАТЬСЯ КАРТЫ*/
	catch (std::bad_alloc &ex) 
	{
		cerr << "Bad allocation of Loaders!" << endl;
		cerr << ex.what() << endl;
		return;
	}
	catch(LoaderException &ex)
	{
		cerr << ex.what() << endl;
		return;
	}
	return;
}

int Application::init()
{
	// В дальнейшем вынести обработку исключений из load() сюда!
	load(); // Загрузка препятствий, карт, тесктур и т.д.
	try 
	{
		_menu = new MenuController();
	} 
	catch (std::bad_alloc &ex) 
	{
		clog << ex.what() << endl;
		return -1;
	}

	window.setPosition(sf::Vector2i(0,0));
	window.setVerticalSyncEnabled(true);
	
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
