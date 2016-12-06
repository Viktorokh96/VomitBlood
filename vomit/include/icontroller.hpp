#ifndef _VOMIT_CONTROLLER
#define _VOMIT_CONTROLLER 1

/* 
 * Интерфейс контроллера
 * обеспечивает механику состояний игры,
 * а также непосредственно отвечает за переход
 * между состояниями.
 * За выделение памяти и целостности объектов не следит!
 * Отвечает за активную перерисовку кадра игры ( задаёт такт )
*/
class IController {
public:
	virtual ~IController() = 0;
	virtual void init() = 0;
	virtual void dispose() = 0;
};

#include "game/controller.hpp"

#endif
