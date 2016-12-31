/*Реализация загрузчика текстур*/

#include <vomitblood.hpp>
  
using namespace std;

TextureLoader::TextureLoader()
{
	ex = TextureLoaderException(); // Указываем, что будут вызываться исключения для загрузки препятствий
	_path = config.getTexturePath(); // изменить на _path = Configuration.getObstaclePath(); !!!
	_tagValueM = getTagValueM();
	load();
}

void TextureLoader::load()
{
	sf::Texture* texture;
	map<string, Texture*> textures;
	map<vector<string>, vector<string> >::iterator itmap;
	string textureName;
	string texturePath;

	for(itmap = _tagValueM.begin(); itmap!=_tagValueM.end(); itmap++)
	{
		textureName = itmap->first[0];
		texturePath = itmap->second[0];
		texture = new Texture();
		if (!texture->loadFromFile(texturePath))
		{
			delete texture;
			ex.message("Unable to load texture!");
			throw ex;
		}
		else
		{
			textures.insert(make_pair(textureName, texture));
		} 
	}
	resourceHolder.setTextures(textures); // Передаём готовые текстуры в хранилище
}

TextureLoader::~TextureLoader()
{}