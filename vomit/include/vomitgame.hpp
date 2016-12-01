#ifndef _VOMITGAME
#define _VOMITGAME 1

/*
 * VomitGame - главный класс игры
 * Его задача заключается в полном обслуживании 
 * процесса игры, а именно:
 * 	- Подготовка системного окружения к началу игры
 * 	- Передача управления контроллерам игры
 * 	- Окончательное освобождение всех игровых ресурсов
*/

class VomitGame {
public:
	void init();
	void startGame();
	void dispose();
};

#endif
