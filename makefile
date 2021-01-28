all: 
	gcc -Wall -Werror -o testlist main.c list.c

clean:
	rm testlist