no_dep_objects = ./obj/Imager.o ./obj/Material.o ./obj/Sphere.o ./obj/Vector3.o

main: ./obj/Renderer.o ./src/main.cpp $(no_dep_objects)
	g++ ./src/main.cpp ./obj/Renderer.o $(no_dep_objects) -o ./build/open_window \
		`sdl2-config --libs --cflags` -ggdb3 -O0 -Wall \
		-I/Users/zacharya/Library/Frameworks/SDL2.framework/Headers -F/Users/zacharya/Library/Frameworks -framework SDL2

./obj/Renderer.o: ./src/Renderer.cpp
	g++ -c src/Renderer.cpp -o obj/Renderer.o \
		`sdl2-config --libs --cflags` -ggdb3 -O0 -Wall \
		-I/Users/zacharya/Library/Frameworks/SDL2.framework/Headers -F/Users/zacharya/Library/Frameworks -framework SDL2

$(no_dep_objects): ./obj/%.o: src/%.cpp
	g++ -c -o $@ $<

.PHONY:
test: ./test/test.o
	./test/test.o

./test/test.o: ./obj/Vector3.o
	g++ ./test/test.cpp ./obj/Vector3.o -o ./test/test.o
