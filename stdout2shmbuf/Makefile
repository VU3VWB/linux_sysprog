all: stdout2shmbuf

stdout2shmbuf: stdout2shmbuf.c
	@echo "Compiling pipe to shm tools"
	gcc -Wall stdout2shmbuf.c -o stdout2shmbuf -lm -lrt -lpthread

clean : 
	rm stdout2shmbuf
