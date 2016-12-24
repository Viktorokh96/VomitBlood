/*Интерфейс классов для обработки исключений*/

#ifndef _LOADER_EXCEPTION
#define _LOADER_EXCEPTION 1

#include <exception>
#include <cstring>


class LoaderException : public exception
{
protected:
	char* _message; // Уточнение сообщения от класса
	char* _errorMessage; // Выводимое собщение, если есть, а оно уж будет :) 	
public:
	LoaderException();
	LoaderException(const LoaderException &obj);
	~LoaderException() throw();
	void message(const char* errStr);
	virtual const char* what();
	LoaderException &operator=(LoaderException ex);
};

/*Классы-обработчики исключений при загрузке*/

/*Обработчик исключений при загрузке текстур*/

class TextureLoaderException : public LoaderException
{
public:
	TextureLoaderException();
	TextureLoaderException(const TextureLoaderException &obj);
	~TextureLoaderException() throw();	
	TextureLoaderException &operator=(TextureLoaderException ex);
};

/*Обработчик исключений при загрузке препятствий*/

class ObstacleLoaderException : public LoaderException
{
public:
	ObstacleLoaderException();
	ObstacleLoaderException(const ObstacleLoaderException &obj);
	~ObstacleLoaderException() throw();	
	ObstacleLoaderException &operator=(ObstacleLoaderException ex);
};

/*Обработчик исключений при загрузке препятствий частей карты */

class PartOfMapLoaderException : public LoaderException
{
public:
	PartOfMapLoaderException();
	PartOfMapLoaderException(const PartOfMapLoaderException &obj);
	~PartOfMapLoaderException() throw();
	PartOfMapLoaderException &operator=(PartOfMapLoaderException ex);
};

#endif