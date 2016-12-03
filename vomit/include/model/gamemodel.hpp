#ifndef _GAME_MODEL
#define _GAME_MODEL 1

#include "vomitmodel.hpp"

typedef int speed_t;
typedef int coord_t;
typedef int cmd_t;
typedef int event_t;

class MapModel : public AbstractModel {
	speed_t speed;
public:
	void update();
};

class ObstacleModel : public AbstractModel {
	coord_t coord;
	speed_t speed;
public:
	void update();
};

class TadpoleModel : public AbstractModel {
	MapModel * const _map;
public:
	TadpoleModel( MapModel *map );
	void update();
};

/*
 * Шаблон проетирования "Фасад"
 * реализует унифицированный интерфейс к подсистеме
 * модели игрового мира.
*/
class GameModelFacade {
	MapModel * const _map;
	TadpoleModel * const _tadpole;
public:
	GameModelFacade( MapModel *map, TadpoleModel *tadpole );
	
	cmd_t update ( event_t &ev );
};

#endif
