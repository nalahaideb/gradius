exe:	main.cpp
	g++ *.cpp src/*.cpp src/*.c `sdl-config --cflags --libs` -lSDL_image -lSDL_mixer -lSDL_ttf -Iincludes -fsanitize=address

run:
	./a.out

r:
	./a.out
	ASAN_OPTIONS=detect_leaks=1 ./a.out
clean:
	rm a.out

c:
	rm a.out
