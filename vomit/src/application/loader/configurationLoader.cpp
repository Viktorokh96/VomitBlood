/*Реализация загрузчика настроек*/

#include <vomitblood.hpp>
  
using namespace std;

ConfigurationLoader::ConfigurationLoader()
{
	ex = ConfigurationLoaderException(); // Указываем, что будут вызываться исключения для загрузки настроек
	_path = CONFIGURATION_PATH; 
	_tagValueM = getTagValueM();
	load();
}

void ConfigurationLoader::load()
{
	config.setStartVelocity(START_MAP_VELOCITY);
	config.setStartLevel(START_MAP_LEVEL);
	config.setRigidity(RIGIDITY);
	config.setObstaclePath(CONFIG_PATH_OBSTACLE);
	config.setPartOfMapPath(CONFIG_PATH_POM);
	config.setTexturePath(CONFIG_PATH_TEXTURE);
	clog << "Configuration has been loaded!" << endl;
	return;
}

ConfigurationLoader::~ConfigurationLoader()
{}