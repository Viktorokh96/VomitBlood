# Имя компилятора
CC = g++ 
# Указание компилятору на поиск заголовочных файлов
INCLUDE = -I./include  

LIBS = 

# Направление поиска исходных файлов для make
vpath %.cpp 
# Направление поиска заголовочных файлов для make
vpath %.h 
# Установка флагов для компиляции объектных файлов
FLAGS = -Wall -c -g -std=c++98 $(INCLUDE)
# Установка флагов для линковщика
LDFLAGS = $(LIBS)
# Исходные файлы проекта и их зависимости от заголовочных файлов
# Пример:  MAINSRC = framework.cpp isca.h


# Объектные файлы
# Пример: MAINOBJ = framework.o

ALLOBJ	= $(MAINOBJ) 

EXE := vomitblood

all: $(EXE)

$(EXE) : $(ALLOBJ)
		$(CC) $^ $(LDFLAGS) -o $@

# $< - переменная хранящая первый параметр строки пререквизита
# Пример: $(MAINOBJ) : $(MAINSRC)
#		$(CC) $< $(FLAGS) -o $@

# Очистка директории от объектных файлов
.PHONY: clean
clean :
		rm -rf $(ALLOBJ) && rm $(EXE)
