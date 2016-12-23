# Имя компилятора
CC = g++ 
# Указание компилятору на поиск заголовочных файлов
INCLUDE = -I../vomit/include  

# перечень подключаемых библиотек (например -lncurses)
LIBS = -lsfml-window -lsfml-graphics -lsfml-system

# Направление поиска исходных файлов для make
vpath %.cpp ../vomit/src/ ../vomit/src/game/ ../vomit/src/application/ ../vomit/src/menu/ ../vomit/src/application/loader/
# Направление поиска заголовочных файлов для make
vpath %.hpp ../vomit/include/
# Установка флагов для компиляции объектных файлов
FLAGS = -Wall -c -g -std=c++98 $(INCLUDE)
# Установка флагов для линковщика
LDFLAGS = $(LIBS)
# Исходные файлы проекта и их зависимости от заголовочных файлов
# Пример:  MAINSRC = framework.cpp isca.h


# Объектные файлы
# Пример: MAINOBJ = framework.o

MAINOBJ = visualize.o
VHOLDER = holder.o
VLOADER = loader.o
VPOMLOADER = partOfMapLoader.o # POM - Part of map
VLOADEREXCEPTION = loaderException.o

ALLOBJ	= $(MAINOBJ) $(VLOADER) $(VPOMLOADER) $(VLOADEREXCEPTION)

EXE := visualize

all: $(EXE)

$(EXE) : $(ALLOBJ) 
		$(CC) $^ $(LDFLAGS) -o $@

# $< - переменная хранящая первый параметр строки пререквизита
# Пример: $(MAINOBJ) : $(MAINSRC)
#		$(CC) $< $(FLAGS) -o $@

$(MAINOBJ) : %.o : %.cpp
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
	
# Очистка директории от объектных файлов
.PHONY: clean
clean :
		rm -rf $(ALLOBJ) && rm $(EXE)
