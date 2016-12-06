#include <controller/gamecontroller.hpp>
#include <model/gamemodel.hpp>
#include <iostream>
using namespace std;

////////////////////// GameController //////////////////////

GameController::GameController( GameModelFacade *model)
: _model(model)
{
}
