/*Реализация загрузчика текстур*/

#include <vomitblood.hpp>
  
using namespace std;

TextureLoader::TextureLoader()
{
	// Исключения при ошибке загрузки текстуры вызываться не будут
	// Потому как отсутсвие текстуры - проблема не критическая для игры
	_path = config.getTexturePath(); 
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
			textures.insert(make_pair(textureName, (Texture *) NULL));
			cerr << "TextureLoader: Failed to load texture " << textureName
				<< " from " << texturePath << endl;
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
