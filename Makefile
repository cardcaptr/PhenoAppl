CC = g++
CFLAGS = -std=c++11 -O2 -fstrict-aliasing -Wall -W -Wno-uninitialized 
EXEC_NAME = dem
INCLUDES = 
LIBS = libtinyxml2.a
OBJ_FILES = dem.o parser.o tinyxml2.o particlesbase.o particlesdem.o particlesspring.o solutionExporterLagrangian.o eulerintegrator.o velocityverletintegrator.o tests.o

all : staticlib $(EXEC_NAME)

staticlib: $(LIBS)

libtinyxml2.a: tinyxml2.o
	$(AR) $(ARFLAGS)s $@ $^

clean :
	rm $(EXEC_NAME) $(OBJ_FILES) 

flush :
	rm output/*

run :
	./dem.exe

$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

install :
	make
