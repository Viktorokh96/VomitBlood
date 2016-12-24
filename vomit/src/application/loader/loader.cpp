/*Классы-загрузчики*/

// Абстрактный класс 
// с одним методом для всех загрузчиков - getTagValueM(), 
// который возвращает список цепочек тэгов и связанные с ними значения 
// Например, 1) tags: tag1->tag2->tag3 values: 15
//			 2) tags: tag1->tag2->tag4 values: 100.33 12.6
//			 3) tags: tag1->tag5 values: Vitya Artyom Andrei
// Метод load() у каждого загрузчика свой! 

#include <vomitblood.hpp>
  
using namespace std;

/*Абстрактный класс-загрузчик*/
Loader::Loader()
{}

void Loader::load()
{}

map<vector<string>, vector<string> > Loader::getTagValueM()
{
	map<vector<string>, vector<string> > tagValueM; // ассоциативный массив (цепочка тэгов - значения)
	vector<string> tagVector;
	vector<string> valueVector;
	string tag;
	string value;
	bool tagIsOpen = false; // флаг, указывающий на то, какие тэги участвуют в формировании вектора
					// открытые - увеличивают его, закрытые - уменьшают. 
	char tagOpenBracket = TAG_OPEN_BRACKET; // открывающая скобка
	char tagCloseBracket = TAG_CLOSE_BRACKET; // закрывающая скобка
	char c; // для временного хранения символов
	bool isMadePair; // Пара в ассоциативный массив должна заходить один раз при закрытии тэгов 
					//(точнее сразу же после закрытия первого тэга)

	ifstream cfgFile(_path.c_str());
	if(!cfgFile.is_open())
	{
		ex.message("Сonfiguraton file can't be open!");
		throw ex;
	}

	try // для того, чтобы можно было корректно закрыть поток
	{
		if(!cfgFile.eof()) // Вынесено для правильного функционирования цикла
			cfgFile >> c;
			
		if (c != tagOpenBracket)
			{
				ex.message("Can't find first opening tag's bracket in configuration file!");
				throw ex;
			}
		else
			tagIsOpen = true;

		if(!cfgFile.eof()) // Вынесено для правильного функционирования цикла
			cfgFile >> c;

		if(cfgFile.eof()) // Вынесено для правильного функционирования цикла
		{
			ex.message("Unexpected end of file!");	
			throw ex;					
		}

		while(!cfgFile.eof())
		{
			/*Заполнение стека (вектора) открывающими тэгами*/
			while (tagIsOpen) 
			{
				while(c != tagCloseBracket)
				{
					tag += c; // считываем имя тэга
					cfgFile >> c;
					if(cfgFile.eof())
					{
						ex.message("Unexpected end of file! Incompleted opening tag!");	
						throw ex;					
					}
				}
				if (tag.empty())
				{
					ex.message("Tag is empty!");	
					throw ex;
				}
				tagVector.push_back(tag); // добавляем тэг в конец вектора		
				tag.clear(); // очищаем место для названия нового тэга
				cfgFile >> c; // считываем следующий символ
				if(cfgFile.eof())
					{
						ex.message("Unexpected end of file (1)! There is no closing tag!");	
						throw ex;					
					}
				if(c != tagOpenBracket)
					tagIsOpen = false;
				else
				{
					cfgFile >> c;
					if(cfgFile.eof())
					{
						ex.message("Unexpected end of file (2)! There is no closing tag!");	
						throw ex;					
					}
				}
			}
			//Читаем список значений
			while (c != tagOpenBracket)
			{
				// считываем значение, пока не появился разделительный пробел
				while((!isspace(c)) && (c != tagOpenBracket))
				{
					value += c;
					cfgFile.get(c); // Читает с пробелами, в отличие от >>
					if(cfgFile.eof())
					{
						ex.message("Unexpected end of file! There is no closing tag!");	
						throw ex;					
					}
				}
				if (value.empty()) {
					ex.message("There's no value!");	
					throw ex;
				}
				valueVector.push_back(value); // добавляем значение в конец вектора
				value.clear();
				cfgFile >> c;
				if(cfgFile.eof())
					{
						ex.message("Unexpected end of file! There is no closing tag!");	
						throw ex;					
					}
			}

			//Проверяем, что тэг действительно закрывающий
			cfgFile >> c;
			if(c != '/')
			{
				ex.message("Can't find '/' near closing tag! Missed closing tag!");
				throw ex;				
			}

			// Убираем тэги из стека (вектора в данном случае) до тех пор, 
			//пока не появился новый открывающий тэг
			//tagIsOpen = false; - было установлено после конца открывающих тэгов
			// пошли закрывающие тэги...

			while(!tagIsOpen)
			{
				if(tagVector.empty())
					{
						ex.message("Too much closing tags!");	
						throw ex;					
					}
				//Читаем закрывающий тэг
				cfgFile >> c;
				if(cfgFile.eof())
						{
							ex.message("Unexpected end of file! Incompleted closing tag!");	
							throw ex;					
						}			
				while(c != tagCloseBracket)
				{
					tag += c; // считываем имя тэга
					cfgFile >> c;
					if(cfgFile.eof())
						{
							ex.message("Unexpected end of file! Incompleted closing tag!");	
							throw ex;					
						}
				}
				//Проверяем закрывающий тэг на корректность
				if(tag != tagVector.back())
				{

					ex.message("Wrong name of closing tag!");
					cerr << tagVector.back();
					throw ex;				
				}

				tag.clear();

				// Если всё совпало, то записываем список тэгов и значений для 
				// этого списка в ассоциативный массив
				if (isMadePair == false)
				{
					tagValueM.insert(make_pair(tagVector,valueVector));
					isMadePair = true;
				}				
				valueVector.clear();	
				tagVector.pop_back();
				cfgFile >> c;
				if((c != tagOpenBracket) && (!cfgFile.eof()))
					{
						ex.message("There is garbage after closing tag!");	
						throw ex;					
					}
				cfgFile >> c;
				if(c != '/')
				{
					tagIsOpen = true;
				}
			}
			isMadePair = false;
		}
		
		if (!tagVector.empty())
		{
				ex.message("Too little closing tags!");	
				throw ex;	
		}
	}

	catch(LoaderException &ex)
	{
		cfgFile.close();
		throw ex; 
	}

	return tagValueM;	
}

Loader::~Loader()
{
}
