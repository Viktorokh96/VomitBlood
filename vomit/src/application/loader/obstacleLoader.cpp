/*Реализация загрузчика препятствий*/

#include <vomitblood.hpp>
  
using namespace std;

ObstacleLoader::ObstacleLoader()
{
	ex = ObstacleLoaderException(); // Указываем, что будут вызываться исключения для загрузки препятствий
	_path = CONFIG_PATH_OBSTACLE; // изменить на _path = Configuration.getObstaclePath(); !!!
	_tagValueM = getTagValueM();
	load();
}

void ObstacleLoader::load()
{
// Метод для создания объектов препятствий
//	map<string, Obstacle*>* _obstacles; // список препятствий
}

ObstacleLoader::~ObstacleLoader()
{}