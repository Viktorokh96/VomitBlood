#include <vomitblood.hpp>

Holder resourceHolder;

Holder::Holder()
{
	_partOfMaps.clear();
	_obstacles.clear();
	_textures.clear();
}

void Holder::setObstacles(map<std::string, Obstacle*> obstacles)
{
	map<string, Obstacle*>::iterator 
		ObstIt = _obstacles.begin();
	for(;ObstIt != _obstacles.end(); ObstIt++)
		delete ObstIt->second;

	_obstacles = obstacles;
}

void Holder::setPartOfMaps(vector<PartOfMap> partOfMaps)
{
	_partOfMaps = partOfMaps;
}

void Holder::setTextures(map<std::string, Texture*> textures)
{
	map<string, Texture*>::iterator texIter;
		texIter = _textures.begin();

	_textures = textures;
}

void Holder::setStartPartOfMap(PartOfMap part)
{
	_startPartOfMap = part;
}

Texture *Holder::getTexture(string textureName)
{
	if (_textures.count(textureName))
		return _textures[textureName];
	else
		return NULL;
}

map<std::string, Obstacle *> Holder::getObstacles()
{
	return _obstacles;
}


PartOfMap Holder::getStartPartOfMap()
{
	return _startPartOfMap;
}

PartOfMap Holder::getRandomPartOfMap(unsigned int level)
{
	unsigned randomPart;

	do
	{
		randomPart = rand() % _partOfMaps.size();
	} while(_partOfMaps[randomPart].getLevel() > level);

	return _partOfMaps[randomPart];
}

Holder::~Holder()
{

	map<string, Obstacle*>::iterator 
		ObstIt = _obstacles.begin();
	map<string, Texture*>::iterator texIter;
		texIter = _textures.begin();
	for(;texIter != _textures.end(); texIter++)
		delete texIter->second;
	for(;ObstIt != _obstacles.end(); ObstIt++)
		delete ObstIt->second;

	_partOfMaps.clear();
	_obstacles.clear();
	_textures.clear();
}
