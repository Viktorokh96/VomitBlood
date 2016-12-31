/*Реализация загрузчика препятствий*/

#include <vomitblood.hpp>
#include <set>
  
using namespace std;

#define SEGMENTS_PER_CURVE 25

typedef map<vector<string>, vector<string> >::iterator tagIter;
typedef vector<sf::Vector2f> vertices_t;
enum state { NONE, MOVE_ABS, CURVE_ABS, MOVE_TO, CURVE_TO, LINE_ABS, LINE_TO };


ObstacleLoader::ObstacleLoader()
{
	ex = ObstacleLoaderException(); // Указываем, что будут вызываться исключения для загрузки препятствий
	_path = config.getObstaclePath(); 
	_tagValueM = getTagValueM();
	load();
}

state checkState(char ch, state current)
{
	switch(ch)
	{
		case 'M': return MOVE_ABS;
		case 'm': return MOVE_TO;
		case 'L': return LINE_ABS;
		case 'l': return LINE_TO;
		case 'C': return CURVE_ABS;
		case 'c': return CURVE_TO;
	}

	return current;
}

sf::Vector2f CalculateBezierPoint(float t, sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3)
{
	float u = 1 - t;
	float tt = t*t;
	float uu = u*u;
	float uuu = uu * u;
	float ttt = tt * t;

	sf::Vector2f p = uuu * p0;
	p += 3 * uu * t * p1;
	p += 3 * u * tt * p2;
	p += ttt * p3;

	return p;
}

vertices_t getObtacleVertices(vector<string> coord)
{
	vertices_t readed;
	readed.clear();

	state st = NONE;

	const char *p;
	string xS, yS;

	sf::Vector2f lastPos(0,0);

	vector<string>::iterator iter = coord.begin();

	while(iter != coord.end())
	{
		p = iter->c_str();	
		for(;*p;p++)
		{
			st = checkState(*p, st);
		}

		p = iter->c_str();	
		if(isdigit(*p) || *p == '-')
		{
			
			xS.clear(); yS.clear();

			switch(st)
			{
				case NONE: iter++; break;
				case MOVE_ABS:
				case MOVE_TO:
				case LINE_ABS:
				case LINE_TO:
					for(; *p != ',' && (!iscntrl(*p)); p++)
						xS += *p;
					p++;
					for(; (!isspace(*p)) && (!iscntrl(*p)); p++)
						yS += *p;
					if(st == LINE_ABS || st  == MOVE_ABS)
						lastPos = sf::Vector2f(atof(xS.c_str()), atof(yS.c_str()));
					else
						lastPos = sf::Vector2f(lastPos.x + atof(xS.c_str()), lastPos.y + atof(yS.c_str()));

					readed.push_back(lastPos);
					iter++;
				break;

				case CURVE_ABS:
				case CURVE_TO:
					sf::Vector2f points[4];
					points[0] = sf::Vector2f(lastPos);	

					for(int i = 1; i < 4; ++i, iter++)
					{
						xS.clear(); yS.clear();
						p = iter->c_str();

						for(; *p != ',' && (!iscntrl(*p)); p++)
							xS += *p;
						p++;
						for(; (!isspace(*p)) && (!iscntrl(*p)); p++)
							yS += *p;

						if(st == CURVE_ABS) {
							points[i] = sf::Vector2f(atof(xS.c_str()), atof(yS.c_str()));	
						} else {
							lastPos = sf::Vector2f(lastPos.x + atof(xS.c_str()), lastPos.y + atof(yS.c_str()));
							points[i] = lastPos;
						}
					}

					lastPos = points[3];
						
					for(int j = 1; j <= SEGMENTS_PER_CURVE; ++j)
					{
						float t = j/ (float) SEGMENTS_PER_CURVE;
						readed.push_back(CalculateBezierPoint(t, points[0], points[1], points[2], points[3]));
					}
					break;
			}
		} else {
			iter++;
		}
	}
				
	return readed;
}

void ObstacleLoader::load()
{
	// этот ассоциативный массив будет передан resourceHolder'у
	map<string, Obstacle*> obstacles;
	set<string> obstaclesNames;
	vector<string> tags;

	obstacles.clear();
	obstaclesNames.clear();

	// Определяем какие вообще есть препятствия в файле ( их названия )
	tagIter itmap;
	for(itmap = _tagValueM.begin(); itmap != _tagValueM.end(); itmap++)
	{
		tags = itmap->first;
		obstaclesNames.insert(tags.front());
	}

	// После того как определили - уточняем их параметры
	set<string>::const_iterator it = obstaclesNames.begin();
	while (it != obstaclesNames.end())
	{
		Obstacle *tmpObst;

		tags.clear();
		tags.push_back(*it);
		tags.push_back("path");

		// Получаем вектор вершин для данного препятствия
		vertices_t vert = getObtacleVertices(_tagValueM[tags]);	

		tags.pop_back();
		tags.push_back("texture");
		// Берём текстур
		tmpObst = new Obstacle(vert,_tagValueM[tags][0]);
		// Загружаем в obstacles
		obstacles.insert(make_pair(*it, tmpObst));
		it++;
	}

	// Передаём глобальному объекту для хранения
	resourceHolder.setObstacles(obstacles);
}

ObstacleLoader::~ObstacleLoader()
{}
