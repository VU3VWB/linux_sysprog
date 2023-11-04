all: get-version

get-version: get-version.c
	@echo "Compiling get-version"
	gcc -o get-version.out get-version.c -lft4222 -Wl,-rpath,/usr/local/lib

clean : 
	rm get-version.out