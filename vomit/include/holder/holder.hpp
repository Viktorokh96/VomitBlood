#ifndef _HOLDER_HPP
#define _HOLDER_HPP

#include "../vomitblood.hpp"

using namespace std;

class VisualizeHolder;

class Holder {
	PartOfMap _startPartOfMap;
	map<string, Obstacle*> _obstacles; // хранимый список препятствий
	map<string, Texture*> _textures;
	vector<PartOfMap> _partOfMaps; // Хранимый список карт
public:
	Holder();
	~Holder();

	void setTextures(map<string, Texture*> textures);
	void setObstacles(map<string, Obstacle*> obstacles);
	void setPartOfMaps(vector<PartOfMap> partOfMaps);
	void setStartPartOfMap(PartOfMap part);

	Texture *getTexture(string textureName);
	map<string, Obstacle*> getObstacles();
	PartOfMap getRandomPartOfMap(unsigned int level); // вызывается классом Map
	PartOfMap getStartPartOfMap(); // вызывается классом Map

	friend VisualizeHolder;
};

class VisualizeHolder {
	Holder &_holder;
	unsigned int _current;
public:
	VisualizeHolder(Holder &h) : _holder(h), _current(0) {}
	~VisualizeHolder() {}

	PartOfMap getCurrentPartOfMap() { return _holder._partOfMaps[_current]; }
	void choiceNextPartOfMap() {
		_current++;
		_current %= _holder._partOfMaps.size();
	}
	void choicePastPartOfMap() {
		if (_current == 0)
			_current = static_cast<unsigned int>(_holder._partOfMaps.size() - 1);
		else
			_current--;
	}
};

#endif
