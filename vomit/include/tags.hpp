/* :::::::::::::::::::::::::::::
 * 		  СЛОВАРЬ ТЭГОВ
 * :::::::::::::::::::::::::::::
 * Все названия глобальных (т.е. неизменных) тэгов, 
 * которые используются в игре VomitBlood,
 * прописаны здесь.
 * TAG_ - название тэга в конфигурационных файлах
 * Комментарий (перевод) к каждому тэгу обязателен!!!
 */
#ifndef _TAGS
#define _TAGS 1

//Открывающий и закрывающий тэги
#define TAG_OPEN_BRACKET '['
#define TAG_CLOSE_BRACKET ']'
#define COMMENT_OPEN_BRACKET '<'
#define COMMENT_CLOSE_BRACKET '>'

// Начальная скорость
#define TAG_START_VELOCITY "startVelocity" 	
// Начальный уровень
#define TAG_START_LEVEL "startLevel" 		
// Жёсткость привязки мыши
#define TAG_RIGIDITY "rigidity"				
// Путь до настроек препятствий
#define TAG_OBSTACLE_PATH "obstaclePath"	
// Путь до настроек частей карты
#define TAG_POM_PATH "partOfMapPath"		
// Путь до настроек текстур
#define TAG_TEXTURE_PATH "texturePath"		

#endif