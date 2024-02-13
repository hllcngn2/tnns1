1:
	gcc src/main.c src/gen.c src/draw.c src/logic.c -lSDL2 -Isrc -I. -L. -otnns
hello:
	gcc src/hello/hello.c -lSDL2 -L. -I. -oHello
clean:
	rm tnns.exe tnns.exe.stackdump Hello.exe
