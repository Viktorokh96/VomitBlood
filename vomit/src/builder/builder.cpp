#include <build/vomitbuilder.hpp>
#include <new>

////////////////// Game Builder /////////////////////////

GameBuilder::GameBuilder()
{
}

void GameBuilder::build()
{
	buildObjects();

	_controller->manage();		// Передача управления контроллеру
	
	disposeObjects();
}	

void GameBuilder::buildObjects()
{
	try {
		_map = new MapModel();
		_tadpole = new TadpoleModel(_map);

		// Определение связей между Фасадом и объектами моделей
		_modelFacade = new GameModelFacade(_map, _tadpole);
		
		// Определение связей между контроллером и фасадом моделей
		_controller = new GameController(_modelFacade);

	} 
	catch (std::bad_alloc bad) {
		// err log system
	}
}

void GameBuilder::disposeObjects()
{
	delete _map;
	delete _tadpole;
	delete _modelFacade;
	delete _controller;
}

/////////////////// Rating Builder //////////////////////

void RatingBuilder::build()
{
}

void RatingBuilder::buildObjects()
{
}

void RatingBuilder::disposeObjects()
{
}

/////////////////// Setting Builder //////////////////////

void SettingBuilder::build()
{
}
	
void SettingBuilder::buildObjects()
{
}

void SettingBuilder::disposeObjects()
{
}

/////////////////// Menu Builder //////////////////////

void MenuBuilder::build()
{
}

void MenuBuilder::buildObjects()
{
}

void MenuBuilder::disposeObjects()
{
}
