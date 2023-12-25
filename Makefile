1:
	gcc src/main.c src/gen.c src/draw.c src/more/*.c -lSDL2 -I. -L. -otnns
hello:
	gcc src/hello.c -lSDL2 -L. -I. -oHello
