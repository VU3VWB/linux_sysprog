all: pipedspec

pipedspec: pipedspec.c
	@echo "Compiling piped plotting tools"
	gcc -Wall pipedspec.c -o pipedspec -lcpgplot -lpgplot -lX11 -lfftw3 -lm -lrt -lpthread

clean : 
	rm pipedspec