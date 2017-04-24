CC = g++
CFLAGS = -std=gnu++14
LDFLAGS= -lglew32 -lglfw3 -lSOIL -lopengl32 -lgdi32 -lopengl32 -lgdi32
EXEC = MainlyBomber

SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)

all: $(EXEC)

MainlyBomber: $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper exe

clean:
	@del /Q *.o

mrproper: clean
	@del /Q $(EXEC).exe

exe: all
	@$(EXEC).exe
