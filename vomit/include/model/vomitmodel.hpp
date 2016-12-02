#ifndef _VOMIT_MODEL
#define _VOMIT_MODEL 1

class AbstractModel {
public:
	virtual ~AbstractModel() {};
	virtual void update() = 0;
};

#include "gamemodel.hpp"

#endif
