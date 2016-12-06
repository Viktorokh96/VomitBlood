#ifndef _VOMIT_CONTROLLER
#define _VOMIT_CONTROLLER 1

/* 
 * Абстрактный контроллер игры
 * обеспечивает механику состояний игры,
 * а также непосредственно отвечает за переход
 * между состояниями.
 * За выделение памяти и целостности объектов не следит!
 * Отвечает за активную перерисовку кадра игры ( задаёт такт )
*/
class AbstractController {
public:
	virtual ~AbstractController() {}
	virtual void init() = 0;
	virtual void dispose() = 0;
};

#include "gamecontroller.hpp"

#endif
