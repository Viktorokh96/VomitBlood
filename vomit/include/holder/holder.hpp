#ifndef _HOLDER_HPP
#define _HOLDER_HPP

#include "../vomitblood.hpp"

class Holder {
	vector<PartOfMap*> _partOfMaps; // Хранимый список карт
	map<std::string, Obstacle*> _obstacles; // хранимый список препятствий
public:
	Holder();
	~Holder();

	void setObstacles(map<std::string, Obstacle*> obstacles);
	void setPartOfMaps(vector<PartOfMap *> partOfMaps);
	
	map<std::string, Obstacle*> getObstacles();
	PartOfMap &getRandomPartOfMap(unsigned int level); // вызывается классом Map
};

// Глобальный объект Holder
extern Holder resourceHolder;

#endif
