#ifndef _VOMITGAME
#define _VOMITGAME 1

#include "controller/vomitcontroller.hpp"
#include "model/vomitmodel.hpp"
#include "build/vomitbuilder.hpp"

/*
 * VomitGame - главный класс игры
 * Его задача заключается в полном обслуживании 
 * процесса игры, а именно:
 * 	init() - Подготовка системного окружения к началу игры
 * 	start() - Передача управления построителям (Builder) игры
 * 	dispose() - Окончательное освобождение всех игровых ресурсов
 *
 * Следует создавать лишь один экземпляр этого класса для работы игры
 * Типичное применение:
 * 	int main() 
 * 	{
 * 		VomitGame game;
 *		
 *		game.init();
 *		game.start();
 *		game.dispose();
 *
 * 		return 0;
 * 	}
*/
class VomitGame {
	static const int _buildQuantity = 4;
	AbstractBuilder *_builder[_buildQuantity];
public:
	int init();
	void start();
	void dispose();
};

#endif
