#include <vomitblood.hpp>
#include <tags.hpp>
#include <fstream>
#include <cstdlib>

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

map<string, string> Configuration::getParameters()
{
	map<string, string> params;
	char valueArray[10];
	string startVelocity;
	string startLevel;
	string rigidity;

	snprintf(valueArray, 10, "%d", _startVelocity);
	startVelocity.append(valueArray, 10);
	memset(valueArray, 0, sizeof(char)*10); // обнуление массива

	snprintf(valueArray, 10, "%d", _startLevel);
	startLevel.append(valueArray, 10);
	memset(valueArray, 0, sizeof(char)*10); // обнуление массива

	snprintf(valueArray, 10, "%d", _rigidity);
	rigidity.append(valueArray, 10);
	memset(valueArray, 0, sizeof(char)*10); // обнуление массива	

	params.insert(make_pair(TAG_START_VELOCITY, startVelocity));
	params.insert(make_pair(TAG_START_LEVEL, startLevel));
	params.insert(make_pair(TAG_RIGIDITY, rigidity));
	params.insert(make_pair(TAG_OBSTACLE_PATH,_obstaclePath));
	params.insert(make_pair(TAG_POM_PATH,_partOfMapPath));
	params.insert(make_pair(TAG_TEXTURE_PATH,_texturePath));
	return params;
}

void Configuration::save()
{
	map<string, string> params;
	ofstream cfgFile(CONFIGURATION_PATH);

	params = getParameters(); // Получение настроек (тэг, значение)
	map<string, string>::iterator it = params.begin();
	while(it != params.end())
	{
		cfgFile << TAG_OPEN_BRACKET << it->first.c_str() << TAG_CLOSE_BRACKET;
		cfgFile << " " << it->second.c_str() << " ";
		cfgFile << TAG_OPEN_BRACKET << "/" << it->first.c_str() << TAG_CLOSE_BRACKET << endl;		
		++it;
	}

	cfgFile.close();

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