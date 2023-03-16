all: test_alsa

pipe2shm: test_alsa.c
	@echo "Compiling ALSA test"
	gcc -Wall test_alsa.c -o test_alsa -lasound -lm -ldl

clean : 
	rm test_alsa
