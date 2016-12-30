#ifndef _CONFIGURATION_HPP
#define _CONFIGURATION_HPP

using namespace std;

#include "vomitblood.hpp"

class Configuration
{
private:
	int _startVelocity;
	int _startLevel;
	int _rigidity;
	string _obstaclePath;
	string _partOfMapPath;
	string _texturePath;

public:
	Configuration();
	~Configuration();
	/*Сохранение будет производиться классом Application*/
	void save();
	/*Начальная скорость*/
	void setStartVelocity(int startVelocity);
	int getStartVelocity();
	/*Начальный уровень*/
	void setStartLevel(int startLevel);
	int getStartLevel();
	/*Жёсткость привязки мыши*/
	void setRigidity(int rigidity);
	int getRigidity();
	/*Путь до настроек препятствий*/
	void setObstaclePath(string obstaclePath);
	string& getObstaclePath();
	/*Путь до настроек частей карты*/
	void setPartOfMapPath(string partOfMapPath);
	string& getPartOfMapPath();
	/*Путь до настроек текстур*/
	void setTexturePath(string texturePath);
	string& getTexturePath();
};

// Глобальный объект Configuration
extern Configuration config;

#endif