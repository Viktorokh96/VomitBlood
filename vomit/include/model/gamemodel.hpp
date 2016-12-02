#ifndef _GAME_MODEL
#define _GAME_MODEL 1

typedef int speed_t;

class GameModelFacade {
};

class MapModel : public AbstractModel {
	speed_t speed;
};

class TadpoleModel : public AbstractModel {
};

#endif
