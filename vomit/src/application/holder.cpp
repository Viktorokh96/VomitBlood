#include <vomitblood.hpp>

Holder resourceHolder;

Holder::Holder()
{
	_partOfMaps.clear();
	_obstacles.clear();
}

void Holder::setObstacles(map<std::string, Obstacle*> obstacles)
{
	map<string, Obstacle*>::iterator 
		ObstIt = _obstacles.begin();
	for(;ObstIt != _obstacles.end(); ObstIt++)
		delete ObstIt->second;

	_obstacles = obstacles;
}

void Holder::setPartOfMaps(vector<PartOfMap *> partOfMaps)
{
	vector<PartOfMap*>::iterator partIter; // Хранимый список карт
		partIter = _partOfMaps.begin();
	for(;partIter != _partOfMaps.end(); partIter++)
		delete *partIter;

	_partOfMaps = partOfMaps;
}

void Holder::setTextures(map<std::string, Texture*> textures)
{
	map<string, Texture*>::iterator texIter;
		texIter = _textures.begin();
	for(;texIter != _textures.end(); texIter++)
		delete texIter->second;

	_textures = textures;
}

Texture &Holder::getTexture(string textureName)
{
	return (*_textures[textureName]);
}

map<std::string, Obstacle *> Holder::getObstacles()
{
	return _obstacles;
}

PartOfMap & Holder::getRandomPartOfMap(unsigned int level)
{
	return *_partOfMaps[0];
}

Holder::~Holder()
{

	map<string, Obstacle*>::iterator 
		ObstIt = _obstacles.begin();
	map<string, Texture*>::iterator texIter;
		texIter = _textures.begin();
	vector<PartOfMap*>::iterator partIter; // Хранимый список карт
		partIter = _partOfMaps.begin();

	for(;ObstIt != _obstacles.end(); ObstIt++)
		delete ObstIt->second;
	for(;texIter != _textures.end(); texIter++)
		delete texIter->second;
	for(;partIter != _partOfMaps.end(); partIter++)
		delete *partIter;

	_partOfMaps.clear();
	_obstacles.clear();
	_textures.clear();
}
