/* ::::::::::::::::::::::::::::::::::
 * 		  ЗНАЧЕНИЯ ПО УМОЛЧАНИЮ
 * ::::::::::::::::::::::::::::::::::
 * DEFAULT_ - стандартное значение. 
 * Используется, когда тэг не указан в конфигурационном файле. 
 * Комментарий (перевод) к каждому макросу обязятелен!!!
 */
#ifndef _DEFAULTS
#define _DEFAULTS 1

// Начальная скорость
#define DEFAULT_START_VELOCITY 400
// Начальный уровень		
#define DEFAULT_START_LEVEL 1
// Жёсткость привязки мыши				
#define DEFAULT_RIGIDITY 10
// Путь до настроек препятствий
#define DEFAULT_OBSTACLE_PATH "./config/obstacle.cfg"
// Путь до настроек частей карты		
#define DEFAULT_POM_PATH "./config/partOfMap.cfg"
// Путь до настроек текстур		
#define DEFAULT_TEXTURE_PATH "./config/texture.cfg"

#endif