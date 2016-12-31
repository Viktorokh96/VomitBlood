#include <vomitblood.hpp>
#include <tags.hpp>

using namespace std;

Configuration config;

Configuration::Configuration()
{
	_obstaclePath.clear();
	_partOfMapPath.clear();
	_texturePath.clear();
	// Настройки по умолчанию
	_startVelocity = DEFAULT_START_VELOCITY;
	_startLevel = DEFAULT_START_LEVEL;
	_rigidity = DEFAULT_RIGIDITY;
	_obstaclePath = DEFAULT_OBSTACLE_PATH;
	_partOfMapPath = DEFAULT_POM_PATH;
	_texturePath = DEFAULT_TEXTURE_PATH;
}

void Configuration::save()
{
	clog << "Configuration has been saved!" << endl;
}
	/*Начальная скорость*/
void Configuration::setStartVelocity(int startVelocity)
{
	_startVelocity = startVelocity;
}
int Configuration::getStartVelocity()
{
	return _startVelocity;
}
	/*Начальный уровень*/
void Configuration::setStartLevel(int startLevel)
{
	_startLevel = startLevel;
}
int Configuration::getStartLevel()
{
	return _startLevel;
}
	/*Жёсткость привязки мыши*/
void Configuration::setRigidity(int rigidity)
{
	_rigidity = rigidity;
}
int Configuration::getRigidity()
{
	return _rigidity;
}
	/*Путь до настроек препятствий*/
void Configuration::setObstaclePath(string obstaclePath)
{
	_obstaclePath = obstaclePath;
}
string& Configuration::getObstaclePath()
{
	return _obstaclePath;
}
	/*Путь до настроек частей карты*/
void Configuration::setPartOfMapPath(string partOfMapPath)
{
	_partOfMapPath = partOfMapPath;
}
string& Configuration::getPartOfMapPath()
{
	return _partOfMapPath;
}
	/*Путь до настроек текстур*/
void Configuration::setTexturePath(string texturePath)
{
	_texturePath = texturePath;
}
string& Configuration::getTexturePath()
{
	return _texturePath;
}

Configuration::~Configuration()
{
	_obstaclePath.clear();
	_partOfMapPath.clear();
	_texturePath.clear();
}