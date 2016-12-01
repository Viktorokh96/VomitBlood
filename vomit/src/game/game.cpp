#include <vomitgame.hpp>

enum builderName { game, menu, rating, setting };

int VomitGame::init()
{
	_builder[game] = new GameBuilder;
	_builder[menu] = new MenuBuilder;
	_builder[rating] = new RatingBuilder;
	_builder[setting] = new SettingBuilder;

	for (int i = 0; i < _buildQuantity; ++i)
		if ( ! _builder[i] )
			return -1;
	
	return 0;
}

void VomitGame::start()
{
	_builder[menu]->build();
}

void VomitGame::dispose()
{
	for (int i = 0; i < _buildQuantity; ++i)
		if ( _builder[i] )
			delete _builder[i];
}
