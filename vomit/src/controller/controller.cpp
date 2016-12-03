#include <controller/vomitcontroller.hpp>
#include <model/vomitmodel.hpp>
#include <iostream>
using namespace std;

////////////////////// GameController //////////////////////

GameController::GameController( GameModelFacade *model)
: _model(model)
{
}

void GameController::manage()
{
	for (event_t i = 0; i < 5; ++i) {
		_model->update(i);
	}
}
