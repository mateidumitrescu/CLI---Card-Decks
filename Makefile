build:
	gcc -g -Wall -Wextra -std=c99 main.c utils.c -o tema1

run:
	./tema1

clean:
	rm -f tema1