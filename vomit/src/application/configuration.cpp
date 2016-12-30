#include <vomitblood.hpp>

using namespace std;

Configuration config;

Configuration::Configuration()
{
	_obstaclePath.clear();
	_partOfMapPath.clear();
	_texturePath.clear();
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