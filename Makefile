# Имя компилятора
CC = g++ 
# Указание компилятору на поиск заголовочных файлов
INCLUDE = -I./vomit/include  

# перечень подключаемых библиотек (например -lncurses)
LIBS = 

# Направление поиска исходных файлов для make
vpath %.cpp ./vomit/src/ ./vomit/src/game/ ./vomit/src/model/ ./vomit/src/controller/ 
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

MAINOBJ = vomitblood.o
VGAMEOBJ = game.o
VMODELOBJ = model.o
VCONTROBJ = controller.o

ALLOBJ	= $(MAINOBJ) $(VGAMEOBJ) $(VMODELOBJ) $(VCONTROBJ)

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

# Очистка директории от объектных файлов
.PHONY: clean
clean :
		rm -rf $(ALLOBJ) && rm $(EXE)
