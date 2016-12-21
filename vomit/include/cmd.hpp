#ifndef _CMD_HPP
#define _CMD_HPP 1

#include <cstring>

/*
 * Общий интерфейс команд
 * используемый для передачи сообщений
 * внутри объектов игры VomitBlood.
*/
typedef struct _cmd {
	unsigned tadpoleCollide:1;
	unsigned tadpoleStep:1;
	unsigned gameOver:1;
	unsigned exitGame:1;
	unsigned restart:1;
	unsigned resume:1;
	unsigned addVelocity:1;
	unsigned addLevel:1;

	unsigned startGame:1;

	void clear()
	{
		memset(this, 0, sizeof(_cmd));
	}
} cmd_t;


enum gameStatus { gamePause , gameOver };


#endif
