/*Реализация загрузчика частей карты*/
#include <vomitblood.hpp>
  
using namespace std;

PartOfMapLoader::PartOfMapLoader()
{
	ex = PartOfMapLoaderException(); // Указываем, что будут вызываться исключения для загрузки частей карты
	_path = CONFIG_PATH_POM; // изменить на _path = Configuration.getPartOfMapPath(); !!!
	_tagValueM = getTagValueM();
	load();
}

void PartOfMapLoader::load()
{
// Метод для создания объектов частей карты
}

PartOfMapLoader::~PartOfMapLoader()
{
	
}