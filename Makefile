build: src/main.c
	gcc --static  -o build/main src/main.c

run: build
	./build/main

default: build
