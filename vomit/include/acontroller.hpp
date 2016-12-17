#ifndef _ACONTROLLER
#define _ACONTROLLER 1

#include "iview.hpp"
#include "cmd.hpp"

/*
 * Абстрактный класс контроллера
*/

class AController {
	bool _loopIsRunning;
protected:
	virtual ~AController() {}
	virtual void processCommands(cmd_t cmd) {}
	virtual void processEvents() {}
	void manage(IView &);
	void stopManage();
};

#endif
