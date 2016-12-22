#include <vomitblood.hpp>

Holder resourceHolder;

Holder::Holder()
{
	_partOfMaps.clear();
	_obstacles.clear();
}

void Holder::setObstacles(map<std::string, Obstacle*> obstacles)
{
	_obstacles = obstacles;
}

void Holder::setPartOfMaps(vector<PartOfMap *> partOfMaps)
{
	_partOfMaps = partOfMaps;
}

map<std::string, Obstacle *> Holder::getObstacles()
{
	return _obstacles;
}

PartOfMap & Holder::getRandomPartOfMap(unsigned int level)
{
	//TEMPORARY!!!!!
	PartOfMap *part = new PartOfMap();

	return *part;
}

Holder::~Holder()
{
	_partOfMaps.clear();
	_obstacles.clear();
}
