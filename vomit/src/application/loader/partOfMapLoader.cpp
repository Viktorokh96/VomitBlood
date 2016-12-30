/*Реализация загрузчика частей карты*/
#include <vomitblood.hpp>
#include <set>
  
using namespace std;

PartOfMapLoader::PartOfMapLoader()
{
	ex = PartOfMapLoaderException(); // Указываем, что будут вызываться исключения для загрузки частей карты
	_path = CONFIG_PATH_POM; // изменить на _path = Configuration.getPartOfMapPath(); !!!
	_tagValueM = getTagValueM();
	load();
}

typedef vector<PartOfMap>::iterator partIter;

void PartOfMapLoader::load()
{
	// Будет передан в resourceHolder
	vector<PartOfMap> parts;
	parts.clear();

	// Получаем список всех имеющихся препятстви
	map<string, Obstacle*> obstacles = resourceHolder.getObstacles();

	// Подготавливаем ключ для поиска значений отображения _tagValueM
	vector<string> tags;
	tags.clear();

	// Будут переданы в конструктор partOfMap
	vector<Obstacle> inPartObstacles;
	inPartObstacles.clear();

	set<string> partNames;
	// Определяем какие вообще есть блоки карт в файле
	tagValueIter itmap = _tagValueM.begin();
	for(; itmap != _tagValueM.end(); itmap++)
	{
		tags = itmap->first;
		partNames.insert(tags.front());
	}

	// Уровень сложности части карты
	unsigned partLevel;

	// Итератор поиска
	tagValueConstIter findIter;

	// После того как определили - уточняем их параметры
	set<string>::const_iterator partName = partNames.begin();
	for(; partName != partNames.end(); partName++)
	{
		set<string> obsId;
		obsId.clear();
		
		tags.clear();
		tags.push_back(*partName);

		// Определяем уровень сложности блока карты ( если описан )
		// По умолчанию - 1
		tags.push_back("level");
		findIter = _tagValueM.find(tags);
		if (findIter != _tagValueM.end())
		{
			partLevel = atoi(findIter->second[0].c_str());
		}
		else
		{	
			partLevel = 1; 		// Значение уровня по умолчанию
		}

		tags.pop_back();


		// Определяем какие вообще препятствия в в блоке ( их идентификаторы )
		tagValueIter itmap = _tagValueM.begin();
		for(; itmap != _tagValueM.end(); itmap++)
		{
			if(((itmap->first).front() == *partName) 
					&& itmap->first[1] != "level")
			{
				obsId.insert(itmap->first[1]);
			}
		}		
		
		inPartObstacles.clear();

		// После того как определили - уточняем их параметры
		set<string>::const_iterator id = obsId.begin();
		for(;id != obsId.end(); id++)
		{
			tags.clear();
			tags.push_back(*partName);
			tags.push_back(*id);


			// Заготовка препятствия, которая будет пропущена через конвейер построения
			Obstacle tmpObstacle;

			// Производим поиск имени препятствия
			tags.push_back("name");
			findIter = _tagValueM.find(tags);
			if (findIter != _tagValueM.end())
			{
				tmpObstacle = *obstacles[findIter->second[0]];
			}
			else
			{
				string msg = "Obstacle with id "; msg += *id;
				msg += " in "; msg += *partName; msg += " has no name!";
				ex.message(msg.c_str());
				throw ex;
			}

			tags.pop_back();

			// Производим поиск позиции препятствия
			tags.push_back("position");
			findIter = _tagValueM.find(tags);
			if (findIter != _tagValueM.end())
			{
				string strPos = findIter->second[0];
				string xS, yS;

				const char *q = strPos.c_str();
				for (; *q != ',' && *q != '\0'; q++)
					xS += *q;
				q++;
				for (; *q != '\0'; q++)
					yS += *q;

				sf::Vector2f pos(atof(xS.c_str()), atof(yS.c_str()));
				tmpObstacle.setInMapPosition(pos);
			}
			else
			{
				string msg = "Obstacle with id "; msg += *id;
				msg += " in "; msg += *partName; msg += " has no position!";
				ex.message(msg.c_str());
				throw ex;
			}

			tags.pop_back();

			// Производим поиск значения поворота препятствия
			// Если оно не найдено то по умолчанию - 0 градусов
			tags.push_back("rotation");
			findIter = _tagValueM.find(tags);
			if (findIter != _tagValueM.end())
			{
				string strRotate = findIter->second[0];
				tmpObstacle.rotate(atof(strRotate.c_str()));
			}
			else
			{
				tmpObstacle.rotate(0);
			}

			tags.pop_back();

			// Производим поиск значения масштабирования препятствия
			// Если оно не найдено то по умолчанию - 1,1 по x и y
			tags.push_back("scale");
			findIter = _tagValueM.find(tags);
			if (findIter != _tagValueM.end())
			{
				string strScale = findIter->second[0];
				string xS, yS;
				xS.clear(); yS.clear();
				const char *q = strScale.c_str();
				for (; *q != ',' && *q != '\0'; q++)
					xS += *q;
				q++;
				for (; *q != '\0'; q++)
					yS += *q;

				tmpObstacle.setScale(atof(xS.c_str()), atof(yS.c_str()));
			}
			else
			{
				tmpObstacle.setScale(1,1);
			}

			inPartObstacles.push_back(tmpObstacle);
		}

		// Создаём и добавляем новый блок карты в вектор parts
		PartOfMap newPart = PartOfMap(inPartObstacles, partLevel);	

		if(*partName == "start")
			resourceHolder.setStartPartOfMap(newPart);
		else
			parts.push_back(newPart);
	}

	resourceHolder.setPartOfMaps(parts);
}

PartOfMapLoader::~PartOfMapLoader()
{
	
}
