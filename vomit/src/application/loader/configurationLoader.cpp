/*Реализация загрузчика настроек*/

#include <vomitblood.hpp>
#include <set>
#include "tags.hpp"
  
using namespace std;

ConfigurationLoader::ConfigurationLoader()
{
	_tagValueM.clear();
	ex = ConfigurationLoaderException(); // Указываем, что будут вызываться исключения для загрузки настроек
	_path = CONFIGURATION_PATH;
	// Обработка исключения будет производиться без завершения работы программы
	try
	{
		_tagValueM = getTagValueM();		
	}
	catch(LoaderException &ex)
	{
		clog << ex.what() << endl;
		clog << "Default configuration has been loaded!" << endl;
		_tagValueM.clear(); 
	} 
	load();
}

void ConfigurationLoader::load()
{
	//Если конфигурационный файл загружен, то выполняем следующий код, иначе - настройки по умолчанию
	if (!_tagValueM.empty())
	{
		// По сути в этом векторе будет только одна строка, 
		//но для map<vector,vector> приходится использовать такой костыль
		vector<string> tagVector; // ключ
		vector<string> valueVector; // значение

	/*Настройка начальной скорости*/
		tagVector.push_back(TAG_START_VELOCITY);
		if (_tagValueM.count(tagVector))
		{
			valueVector = _tagValueM[tagVector];
			config.setStartVelocity(atoi(valueVector[0].c_str()));
		}
		else
		{
			clog << "Default start velocity has been loaded!" << endl;
		}

		// Очищаем ключ и значение
		tagVector.pop_back();
		if(!valueVector.empty())
			valueVector.pop_back();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	/*Настройка начального уровня*/
		tagVector.push_back(TAG_START_LEVEL);
		if (_tagValueM.count(tagVector))
		{
			valueVector = _tagValueM[tagVector];
			config.setStartLevel(atoi(valueVector[0].c_str()));
		}
		else
		{
			clog << "Default start level has been loaded!" << endl;
		}

		// Очищаем ключ и значение
		tagVector.pop_back();
		if(!valueVector.empty())
			valueVector.pop_back();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	/*Настройка жёсткости привязки мыши*/
		tagVector.push_back(TAG_RIGIDITY);
		if (_tagValueM.count(tagVector))
		{
			valueVector = _tagValueM[tagVector];
			config.setRigidity(atoi(valueVector[0].c_str()));
		}
		else
		{
			clog << "Default rigidity has been loaded!" << endl;
		}

		// Очищаем ключ и значение
		tagVector.pop_back();
		if(!valueVector.empty())
			valueVector.pop_back();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	/*Настройка пути до конфигурационного файла препятствий*/
		tagVector.push_back(TAG_OBSTACLE_PATH);
		if (_tagValueM.count(tagVector))
		{
			valueVector = _tagValueM[tagVector];
			config.setObstaclePath(valueVector[0]);
		}
		else
		{
			clog << "Default obstacle configuration path has been loaded!" << endl;
		}

		// Очищаем ключ и значение
		tagVector.pop_back();
		if(!valueVector.empty())
			valueVector.pop_back();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	/*Настройка пути до конфигурационного файла частей карты*/
		tagVector.push_back(TAG_POM_PATH);
		if (_tagValueM.count(tagVector))
		{
			valueVector = _tagValueM[tagVector];
			config.setPartOfMapPath(valueVector[0]);
		}
		else
		{
			clog << "Default part of map configuration path has been loaded!" << endl;
		}

		// Очищаем ключ и значение
		tagVector.pop_back();
		if(!valueVector.empty())
			valueVector.pop_back();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	/*Настройка пути до конфигурационного файла текстур*/
		tagVector.push_back(TAG_TEXTURE_PATH);
		if (_tagValueM.count(tagVector))
		{
			valueVector = _tagValueM[tagVector];
			config.setTexturePath(valueVector[0]);
		}
		else
		{
			clog << "Default texture configuration path has been loaded!" << endl;
		}

		// Очищаем ключ и значение
		tagVector.pop_back();
		if(!valueVector.empty())
			valueVector.pop_back();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	}

	return;
}

ConfigurationLoader::~ConfigurationLoader()
{}