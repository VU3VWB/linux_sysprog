all: ft_open ft_read

ft_open: ft_open.c
	@echo "Compiling ft_open"
	gcc -o ft_open.out ft_open.c -lft4222 -Wl,-rpath,/usr/local/lib

ft_read: ft_read.c
	@echo "Compiling ft_read"
	gcc -o ft_read.out ft_read.c -lft4222 -Wl,-rpath,/usr/local/lib

clean : 
	rm -f *.out