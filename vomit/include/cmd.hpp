#ifndef _CMD_HPP
#define _CMD_HPP 1
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


	void clear()
	{
		tadpoleCollide = 0;
		tadpoleStep = 0;
		gameOver = 0;
		exitGame = 0;
		addVelocity = 0;
		addLevel = 0;
		restart = 0;
		resume = 0;
	}
} cmd_t;


enum gameStatus { gamePause , gameOver };


#endif
