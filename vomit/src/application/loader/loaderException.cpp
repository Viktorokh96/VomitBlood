/*Классы для обработки исключений*/
/*НЕ ИЗМЕНЯТЬ НИ В КОЕМ СЛУЧАЕ!!!!!*/
/*Чтобы добавить новый класс, скопируйте код класса-потомка (например, ObstacleLoader)
  Измените только название самого класса и соответствующих методов
  (например, ObstacleLoader -> TextureLoader) и начало выдаваемого сообщения
  (например, "ObstacleLoader exception:" - на "TextureLoader exception").
  Не забыть прописать интерфейс в include/loader/loaderException.hpp!
*/
#include <vomitblood.hpp>
  
using namespace std;
/*Абстрактный класс*/
LoaderException::LoaderException(){ _errorMessage = NULL; _message = NULL; }

LoaderException::LoaderException(const LoaderException &obj)
{ 
	_errorMessage = NULL; _message = NULL;

	if(obj._errorMessage)
	{
		const int ERRSTR_SIZE = strlen( obj._errorMessage );
		_errorMessage = new char[ ERRSTR_SIZE + 1 ];
		
		strncpy ( _errorMessage, obj._errorMessage, ERRSTR_SIZE);
		_errorMessage[ ERRSTR_SIZE ] = '\0';	
	}

	if(obj._message)
	{
		const int ERRSTR_SIZE = strlen( obj._message );
		_message = new char[ ERRSTR_SIZE + 1 ];
		
		strncpy ( _message, obj._message, ERRSTR_SIZE);
		_message[ ERRSTR_SIZE ] = '\0';	
	}
}

LoaderException::~LoaderException() throw()
{
	if ( _errorMessage )
	{
		delete [] _errorMessage;	    
		_errorMessage = NULL; // Дальше будем принудительно заNULLять все указатели после delete
	}
	if (_message)
	{
		delete [] _message;
		_message = NULL;
	}
}

void LoaderException::message(const char* errStr)
{
	if ( errStr != NULL )
	{
	  const int ERRSTR_SIZE = strlen( errStr );
	  _errorMessage = new char[ ERRSTR_SIZE + 1 ];

	  strncpy( _errorMessage, errStr, ERRSTR_SIZE );
	  _errorMessage[ ERRSTR_SIZE ] = '\0';
	}
	else
	{
	  _errorMessage = NULL;
	}
}

const char* LoaderException::what()
{
	if (_errorMessage)
	{
		const int msgLen = strlen(_message);
		const int errLen = strlen(_errorMessage);
		const int ERRSTR_SIZE = msgLen + errLen;
		char *errMsg = new char[ ERRSTR_SIZE + 1];
		strncpy ( errMsg, _message, msgLen);
		strncpy ( errMsg+msgLen, _errorMessage, errLen);
		errMsg [ ERRSTR_SIZE ] = '\0';
	
		return errMsg;	
	}     		
		else
		return _message;
}

LoaderException & LoaderException::operator=(LoaderException ex)
{
	if(this == &ex) return *this;
	if(ex._errorMessage)
	{
		const int ERRSTR_SIZE = strlen( ex._errorMessage );
		_errorMessage = new char[ ERRSTR_SIZE + 1];
		
		strncpy ( _errorMessage, ex._errorMessage, ERRSTR_SIZE);
		_errorMessage[ ERRSTR_SIZE ] = '\0';	
	}

	if(ex._message)
	{
		const int ERRSTR_SIZE = strlen( ex._message );
		_message = new char[ ERRSTR_SIZE + 1];
		
		strncpy ( _message, ex._message, ERRSTR_SIZE);
		_message[ ERRSTR_SIZE ] = '\0';	
	}

	return *this;
}

/*Классы-обработчики исключений при загрузке*/

/*Обработчик исключений при загрузке препятствий*/


ObstacleLoaderException::ObstacleLoaderException()
{	
	const int messageLength = strlen("ObstacleLoader exception: ");
	_message = new char[messageLength + 1];
	strncpy(_message, "ObstacleLoader exception: ", messageLength);
	_message[messageLength] = '\0';
}

ObstacleLoaderException::ObstacleLoaderException(const ObstacleLoaderException &obj) : LoaderException(obj) {}

ObstacleLoaderException::~ObstacleLoaderException() throw()
{
	if ( _errorMessage )
	{
		delete [] _errorMessage;	    
		_errorMessage = NULL;
	}
	if (_message)
	{
		delete [] _message;
		_message = NULL;
	}	
}

ObstacleLoaderException & ObstacleLoaderException::operator=(ObstacleLoaderException ex)
{
	if(this == &ex) return *this;
	if(ex._errorMessage)
	{
		const int ERRSTR_SIZE = strlen( ex._errorMessage );
		_errorMessage = new char[ ERRSTR_SIZE + 1];
		
		strncpy ( _errorMessage, ex._errorMessage, ERRSTR_SIZE);
		_errorMessage[ ERRSTR_SIZE ] = '\0';	
	}

	if(ex._message)
	{
		const int ERRSTR_SIZE = strlen( ex._message );
		_message = new char[ ERRSTR_SIZE + 1];
		
		strncpy ( _message, ex._message, ERRSTR_SIZE);
		_message[ ERRSTR_SIZE ] = '\0';	
	}

	return *this;

}
/*Обработчик исключений при загрузке препятствий частей карты */

PartOfMapLoaderException::PartOfMapLoaderException()
{	
	const int messageLength = strlen("PartOfMapLoader exception: ");
	_message = new char[messageLength + 1];
	strncpy(_message, "PartOfMapLoader exception: ", messageLength);
	_message[messageLength] = '\0';
}

PartOfMapLoaderException::PartOfMapLoaderException(const PartOfMapLoaderException &obj) : LoaderException(obj) {}

PartOfMapLoaderException::~PartOfMapLoaderException() throw()
{
	if ( _errorMessage )
	{
		delete [] _errorMessage;	    
		_errorMessage = NULL;
	}
	if (_message)
	{
		delete [] _message;
		_message = NULL;
	}	
}

PartOfMapLoaderException & PartOfMapLoaderException::operator=(PartOfMapLoaderException ex)
{
	if(this == &ex) return *this;
	if(ex._errorMessage)
	{
		const int ERRSTR_SIZE = strlen( ex._errorMessage );
		_errorMessage = new char[ ERRSTR_SIZE + 1];
		
		strncpy ( _errorMessage, ex._errorMessage, ERRSTR_SIZE);
		_errorMessage[ ERRSTR_SIZE ] = '\0';	
	}

	if(ex._message)
	{
		const int ERRSTR_SIZE = strlen( ex._message );
		_message = new char[ ERRSTR_SIZE + 1];
		
		strncpy ( _message, ex._message, ERRSTR_SIZE);
		_message[ ERRSTR_SIZE ] = '\0';	
	}

	return *this;

}