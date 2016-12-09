#include <iostream>
#include <vomitblood.hpp>
using namespace std;

int main()
{
	Application game;

	if( game.init() < 0 )
		cerr << "Ошибка инициализации!\n";

	game.start();
	game.dispose();

	return 0;
}
