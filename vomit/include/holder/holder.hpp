#ifndef _HOLDER_HPP
#define _HOLDER_HPP

#include "../vomitblood.hpp"

using namespace std;

class Holder {
	PartOfMap *_startPartOfMap;
	vector<PartOfMap*> _partOfMaps; // Хранимый список карт
	map<string, Obstacle*> _obstacles; // хранимый список препятствий
	map<string, Texture*> _textures;
public:
	Holder();
	~Holder();

	void setTextures(map<string, Texture*> textures);
	void setObstacles(map<string, Obstacle*> obstacles);
	void setPartOfMaps(vector<PartOfMap *> partOfMaps);
	void setStartPartOfMap(PartOfMap * part);
	
	Texture &getTexture(string textureName);
	map<string, Obstacle*> getObstacles();
	PartOfMap &getRandomPartOfMap(unsigned int level); // вызывается классом Map
	PartOfMap &getStartPartOfMap(); // вызывается классом Map
};

// Глобальный объект Holder
extern Holder resourceHolder;

#endif
