# Имя компилятора
CC = g++ 
# Указание компилятору на поиск заголовочных файлов
INCLUDE = -I./vomit/include  

# перечень подключаемых библиотек (например -lncurses)
LIBS = -lsfml-window -lsfml-graphics -lsfml-system

# Направление поиска исходных файлов для make
vpath %.cpp ./vomit/src/ ./vomit/src/game/ ./vomit/src/application/ ./vomit/src/menu/ ./vomit/src/application/loader/
# Направление поиска заголовочных файлов для make
vpath %.hpp ./vomit/include/
# Установка флагов для компиляции объектных файлов
FLAGS = -Wall -c -g -std=c++98 $(INCLUDE)
# Установка флагов для линковщика
LDFLAGS = $(LIBS)
# Исходные файлы проекта и их зависимости от заголовочных файлов
# Пример:  MAINSRC = framework.cpp isca.h


# Объектные файлы
# Пример: MAINOBJ = framework.o

MAINOBJ = main.o
VGAMEOBJ = application.o
VMODELOBJ = gamemodel.o
VCONTROBJ = gamecontroller.o
VVIEW = gameview.o
VMAP = gamemap.o
VTADPOLE = gametadpole.o
VACONTR = acontroller.o
VMENUVIEW = menuview.o
VMENUCONTR = menucontroller.o
VHOLDER = holder.o
VLOADER = loader.o
VOBSLOADER = obstacleLoader.o # OBS - Obsacle
VPOMLOADER = partOfMapLoader.o # POM - Part of map
VLOADEREXCEPTION = loaderException.o
VTXTLOADER = textureLoader.o # TXT - Texture

ALLOBJ	= $(MAINOBJ) $(VGAMEOBJ) $(VMODELOBJ) $(VCONTROBJ) $(VVIEW) $(VMAP) $(VTADPOLE) $(VACONTR) $(VMENUVIEW) $(VMENUCONTR) $(VHOLDER) $(VLOADER) $(VOBSLOADER) $(VPOMLOADER) $(VLOADEREXCEPTION)  $(VTXTLOADER)

EXE := vomitblood

all: $(EXE)

$(EXE) : $(ALLOBJ) 
		$(CC) $^ $(LDFLAGS) -o $@

# $< - переменная хранящая первый параметр строки пререквизита
# Пример: $(MAINOBJ) : $(MAINSRC)
#		$(CC) $< $(FLAGS) -o $@

$(MAINOBJ) : %.o : %.cpp
		$(CC) $< $(FLAGS) -o $@

$(VGAMEOBJ) : %.o : %.cpp
		$(CC) $< $(FLAGS) -o $@

$(VMODELOBJ) : %.o : %.cpp
		$(CC) $< $(FLAGS) -o $@

$(VCONTROBJ) : %.o : %.cpp
		$(CC) $< $(FLAGS) -o $@

$(VVIEW) : %.o : %.cpp
		$(CC) $< $(FLAGS) -o $@

$(VMAP) : %.o : %.cpp
		$(CC) $< $(FLAGS) -o $@

$(VTADPOLE) : %.o : %.cpp
		$(CC) $< $(FLAGS) -o $@

$(VACONTR) : %.o : %.cpp
		$(CC) $< $(FLAGS) -o $@

$(VMENUVIEW) : %.o : %.cpp
		$(CC) $< $(FLAGS) -o $@

$(VMENUCONTR) : %.o : %.cpp
		$(CC) $< $(FLAGS) -o $@

$(VHOLDER) : %.o : %.cpp
		$(CC) $< $(FLAGS) -o $@

$(VLOADER) : %.o : %.cpp
		$(CC) $< $(FLAGS) -o $@

$(VOBSLOADER) : %.o : %.cpp
		$(CC) $< $(FLAGS) -o $@

$(VPOMLOADER) : %.o : %.cpp
		$(CC) $< $(FLAGS) -o $@

$(VLOADEREXCEPTION) : %.o : %.cpp
		$(CC) $< $(FLAGS) -o $@

$(VTXTLOADER) : %.o : %.cpp
		$(CC) $< $(FLAGS) -o $@
		
# Очистка директории от объектных файлов
.PHONY: clean
clean :
		rm -rf $(ALLOBJ) && rm $(EXE)
