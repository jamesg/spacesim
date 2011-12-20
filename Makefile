all:	src/*
	g++ -c -o objs/asteroid.o src/asteroid.cpp -std=c++0x -lm -lglut -lGL -lGLU
	g++ -c -o objs/entity.o src/entity.cpp -std=c++0x -lm -lglut -lGL -lGLU
	g++ -c -o objs/graphics.o src/graphics.cpp -std=c++0x -lm -lglut -lGL -lGLU
	g++ -c -o objs/main.o src/main.cpp -std=c++0x -lm -lglut -lGL -lGLU
	g++ -c -o objs/matrix.o src/matrix.cpp -std=c++0x -lm -lglut -lGL -lGLU
	g++ -c -o objs/model.o src/model.cpp -std=c++0x -lm -lglut -lGL -lGLU
	g++ -o sim objs/* -std=c++0x -lm -lglut -lGL -lGLU

clean:
	rm objs/*.o
	rm sim

