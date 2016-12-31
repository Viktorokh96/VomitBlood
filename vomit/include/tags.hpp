/* :::::::::::::::::::::::::::::
 * 		  СЛОВАРЬ ТЭГОВ
 * :::::::::::::::::::::::::::::
 * Все названия глобальных (т.е. неизменных) тэгов, 
 * которые используются в игре VomitBlood,
 * прописаны здесь.
 * TAG_ - название тэга в конфигурационных файлах
 * DEFAULT_ - стандартное значение. Используется, когда тэг не указан в конфигурационном файле 
 * Комментарий (перевод) к каждому тэгу обязателен!!!
 */
#ifndef _TAGS
#define _TAGS 1

//Открывающий и закрывающий тэги
#define TAG_OPEN_BRACKET '['
#define TAG_CLOSE_BRACKET ']'

// Начальная скорость
#define TAG_START_VELOCITY "startVelocity" 	
#define DEFAULT_START_VELOCITY 400
// Начальный уровень
#define TAG_START_LEVEL "startLevel" 		
#define DEFAULT_START_LEVEL 1
// Жёсткость привязки мыши
#define TAG_RIGIDITY "rigidity"				
#define DEFAULT_RIGIDITY 10
// Путь до настроек препятствий
#define TAG_OBSTACLE_PATH "obstaclePath"	
#define DEFAULT_OBSTACLE_PATH "./config/obstacle.cfg"
// Путь до настроек частей карты
#define TAG_POM_PATH "partOfMapPath"		
#define DEFAULT_POM_PATH "./config/partOfMap.cfg"
// Путь до настроек текстур
#define TAG_TEXTURE_PATH "texturePath"		
#define DEFAULT_TEXTURE_PATH "./config/texture.cfg"

#endif