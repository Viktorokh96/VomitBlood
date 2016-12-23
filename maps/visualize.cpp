/*
 * Визуализатор частей карты PartOfMap
 * Автор: Охотников Виктор <viktorokh96@mail.ru>
 * Дата: 19 декабря 2016 г. 19:08
 */

#include <vomitblood.hpp>
#include <fstream>
#include <set>
#include <iostream>

#define SEGMENTS_PER_CURVE 25

using namespace std;

ObstacleLoader *obstLoader;

typedef map<vector<string>, vector<string> >::iterator tagIter;
typedef vector<sf::Vector2f> vertices_t;
enum state { NONE, MOVE_ABS, CURVE_ABS, MOVE_TO, CURVE_TO, LINE_ABS, LINE_TO };

ObstacleLoader::ObstacleLoader()
{
	ex = ObstacleLoaderException();
	_path = "./obstacles.cfg";
	try {
		_tagValueM = getTagValueM();
	} catch (LoaderException &ex) {
		cerr << ex.what() << endl;
	}
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
					if(st == LINE_ABS)
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
							lastPos = sf::Vector2f(lastPos.x + atof(xS.c_str()), lastPos.y + atof(xS.c_str()));
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
	map<string, Obstacle*> obstacles;
	set<string> obstaclesNames;
	vector<string> tags;

	tagIter itmap;
	for(itmap = _tagValueM.begin(); itmap != _tagValueM.end(); itmap++)
	{
		tags = itmap->first;
		obstaclesNames.insert(tags.front());
	}

	set<string>::const_iterator it = obstaclesNames.begin();
	while (it != obstaclesNames.end())
	{
		Obstacle *tmpObst;

		tags.clear();
		tags.push_back(*it);
		tags.push_back("path");

		vertices_t vert = getObtacleVertices(_tagValueM[tags]);
		tmpObst = new Obstacle(vert);

		tags.pop_back();
		tags.push_back("texture");
		// Берём текстуру здесь
		
		// Загружаем в obstacles
		obstacles.insert(make_pair(*it, tmpObst));
		it++;
	}

	resourceHolder.setObstacles(obstacles);
}

ObstacleLoader::~ObstacleLoader()
{
}

///////////////////////////////////глобальные данные////////////////////////////////////

PartOfMap *part;

sf::View view;

bool _isMovingUp = false;
bool _isMovingDown = false;
int delta = 0;

int initMap()
{
	obstLoader = new ObstacleLoader();
	
	delete obstLoader;
	/*vector<Obstacle *> ob;	
	ob.clear();

	Obstacle *o;
	Obstacle *o1;
	vector<sf::Vector2f> vertices;
	vertices.clear();

	ifstream obsFile("obstacle.obs");
	if(!obsFile)
       	{
		cout << "Can't open file with obstacles!";
		return -1;
	}

	vertices_t obsVertices = getObtacleVertices(obsFile);

	o = new Obstacle(obsVertices);
	o1 = new Obstacle(obsVertices);

	o->setInMapPosition(0, PART_HEIGHT/2);
	o1->rotate(180);
	o1->setInMapPosition(WINDOW_WIDTH, PART_HEIGHT/2);
	ob.push_back(o);
	ob.push_back(o1);

	part = new PartOfMap(ob);
	part->setPosition(WINDOW_HEIGHT - PART_HEIGHT);
	*/

	return 0;
}

void updatePart()
{
	delete part;

	initMap();

	clog << "Part is updated!" << endl;
}

void handleInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
		_isMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		_isMovingDown = isPressed;
	else if (key == sf::Keyboard::U && (!isPressed))
		updatePart();
}

void update()
{
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	float scrollSpeed = 30.f;

	view = window.getView();

	if(((view.getCenter().y > WINDOW_HEIGHT) && _isMovingDown)
	|| ((view.getCenter().y < -WINDOW_HEIGHT) && _isMovingUp))
		return;

	if(_isMovingUp)
	{
		view.move(0.f, -scrollSpeed * timePerFrame.asSeconds());
	}
	else if(_isMovingDown)
	{
		view.move(0.f, scrollSpeed * timePerFrame.asSeconds());
	}
	
	window.setView(view);
}

sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "VomitBlood", sf::Style::Titlebar | sf::Style::Close);

int main(int argc, char *argv[])
{
	if(initMap() < 0) {
		cerr << "Ошибка инициализации карты! Сворачиваюсь!" << endl;
		return -2;
	}
/*
	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::KeyPressed)
			{
				handleInput(event.key.code, true);
			}
			else if(event.type == sf::Event::KeyReleased)
			{
				handleInput(event.key.code, false);
			}
			else if(event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		update();

		window.clear();
		part->draw();
		window.display();	
	}
*/
	return 0;
}
