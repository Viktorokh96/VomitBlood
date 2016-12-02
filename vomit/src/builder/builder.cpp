#include <build/vomitbuilder.hpp>

////////////////// Game Builder /////////////////////////

GameBuilder::GameBuilder()
{
}

void GameBuilder::build()
{
	buildObjects();

	// flow control to controller
	
	disposeObjects();
}	

void GameBuilder::buildObjects()
{
}

void GameBuilder::disposeObjects()
{
}

/////////////////// Rating Builder //////////////////////

void RatingBuilder::build()
{
}

void RatingBuilder::buildObjects()
{
}

void RatingBuilder::disposeObjects()
{
}

/////////////////// Setting Builder //////////////////////

void SettingBuilder::build()
{
}
	
void SettingBuilder::buildObjects()
{
}

void SettingBuilder::disposeObjects()
{
}

/////////////////// Menu Builder //////////////////////

void MenuBuilder::build()
{
}

void MenuBuilder::buildObjects()
{
}

void MenuBuilder::disposeObjects()
{
}
