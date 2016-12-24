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
typedef map<vector<string>, vector<string> >::iterator tagIter;

void PartOfMapLoader::load()
{
	// Будет передан в resourceHolder
	vector<PartOfMap> parts;
	parts.clear();

	map<string, Obstacle*> obstacles = resourceHolder.getObstacles();

	vector<string> tags;
	tags.clear();

	// Будут переданы в конструктор partOfMap
	vector<Obstacle> inPartObstacles;
	inPartObstacles.clear();

	set<string> partNames;
	// Определяем какие вообще есть блоки карт в файле ( их идентификаторы )
	tagIter itmap = _tagValueM.begin();
	for(; itmap != _tagValueM.end(); itmap++)
	{
		tags = itmap->first;
		partNames.insert(tags.front());
	}

	// После того как определили - уточняем их параметры
	set<string>::const_iterator it = partNames.begin();
	for(; it != partNames.end(); it++)
	{
		// Определяем какие вообще есть блоки карт в файле ( их идентификаторы )
		set<string> obsId;
		obsId.clear();
		
		tags.clear();
		tags.push_back(*it);

		tagIter itmap = _tagValueM.begin();
		for(; itmap != _tagValueM.end(); itmap++)
		{
			if((itmap->first).front() == *it)
			{
				obsId.insert(itmap->first[1]);
			}
		}		
		
		inPartObstacles.clear();
		// После того как определили - уточняем их параметры
		// ЛЮДЯМ С РАСТРОЙСТВОМ НЕРВНОЙ ПСИХИКИ КАК У МЕНЯ ЛУЧШЕ
		// ЭТОТ ФРАГМЕНТ НЕ ЧИТАТЬ!!!
		set<string>::const_iterator id = obsId.begin();
		for(;id != obsId.end(); id++)
		{
			tags.clear();
			tags.push_back(*it);
			tags.push_back(*id);

			tags.push_back("name");
			Obstacle tmpObstacle = *obstacles[_tagValueM[tags][0]];
			
			tags.pop_back();
			tags.push_back("position");
			
			string strPos = _tagValueM[tags][0];
			string xS, yS;
			
			// Знакомьтесь - два наших товарища p и q!
			// И щепотка строковой магии!
			const char *q;
			q = strPos.c_str();
			for(; *q != ',' && *q != '\0'; q++)
				xS += *q;
			q++;
			for(; *q != '\0'; q++)
				yS += *q;

			sf::Vector2f pos(atof(xS.c_str()), atof(yS.c_str()));
			tmpObstacle.setInMapPosition(pos);

			tags.pop_back();
			tags.push_back("rotation");

			string strRotate = _tagValueM[tags][0];
			tmpObstacle.rotate(atof(strRotate.c_str()));

			tags.pop_back();
			tags.push_back("scale");

			string strScale = _tagValueM[tags][0];

			xS.clear(); yS.clear();
			q = strScale.c_str();
			for(; *q != ',' && *q != '\0'; q++)
				xS += *q;
			q++;
			for(; *q != '\0'; q++)
				yS += *q;

			tmpObstacle.setScale(atof(xS.c_str()),atof(yS.c_str()));

			inPartObstacles.push_back(tmpObstacle);
		}

		// Создаём и добавляем новый блок карты в вектор parts
		PartOfMap newPart = PartOfMap(inPartObstacles);	
		if(*it == "start")
			resourceHolder.setStartPartOfMap(newPart);
		else
			parts.push_back(newPart);
	}

	resourceHolder.setPartOfMaps(parts);
}

PartOfMapLoader::~PartOfMapLoader()
{
	
}
