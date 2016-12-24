/*Классы-загрузчики*/

// Абстрактный класс 
// с одним методом для всех загрузчиков - getTagValueM(), 
// который возвращает список цепочек тэгов и связанные с ними значения 
// Например, 1) tags: tag1->tag2->tag3 values: 15
//			 2) tags: tag1->tag2->tag4 values: 100.33 12.6
//			 3) tags: tag1->tag5 values: Vitya Artyom Andrei 
// Метод load() у каждого загрузчика свой! 

#ifndef _LOADER
#define _LOADER 1

//#include <vomitblood.hpp> // Возможно придётся использовать
#include "loaderException.hpp"
#include <fstream>
#include <iostream>
#include <cctype>
#include <map>
#include <vector>

#define CONFIG_PATH_OBSTACLE "./config/obstacle.cfg" 
#define CONFIG_PATH_POM "./config/partOfMap.cfg"
#define CONFIG_PATH_TEXTURE "./config/texture.cfg"

// в дальнейшем пути к конфигам можно будет брать у класса Configuration 
#define TAG_OPEN_BRACKET '['
#define TAG_CLOSE_BRACKET ']'

class Loader
{
protected:
	LoaderException ex;
	string _path; // обязательно у всех наследников
	map<vector<string>, vector<string> > _tagValueM; // массив тэг-значение, обязательно у всех наследников
	virtual void load();
	map<vector<string>, vector<string> > getTagValueM();
public:
	Loader();
	~Loader();
};

/*Загрузчик текстур*/

class TextureLoader : public Loader
{
protected:
	virtual void load();
public:
	TextureLoader();
	virtual ~TextureLoader();
};

/*Загрузчик препятствий*/

class ObstacleLoader : public Loader
{
protected:
	virtual void load();
public:
	ObstacleLoader();
	virtual ~ObstacleLoader();
};

/*Загрузчик частей карты*/

class PartOfMapLoader : public Loader
{
protected:
	virtual void load();
public:
	PartOfMapLoader();
	virtual ~PartOfMapLoader();
};

#endif
