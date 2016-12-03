#include <model/vomitmodel.hpp>
#include <iostream>
using namespace std;

//////////////////// MapModel /////////////////////////

void MapModel::update()
{
}

//////////////////// ObstacleModel /////////////////////////

void ObstacleModel::update()
{
}

//////////////////// TadpoleModel //////////////////////////

TadpoleModel::TadpoleModel( MapModel *map ) : _map(map)
{
}

void TadpoleModel::update()
{
}

////////////////// GameModelFacade  ///////////////////////

GameModelFacade::GameModelFacade ( MapModel *map, TadpoleModel *tadpole )
: _map(map), _tadpole(tadpole) 
{
}

cmd_t GameModelFacade::update( event_t &ev ) 
{
	_map->update();
	_tadpole->update();

	cmd_t ret = 0;

	return ret;
}
