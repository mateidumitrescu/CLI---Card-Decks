build:
	gcc -Wall -Wextra -std=c99 tema1.c utils.c -o tema1

run:
	./tema1

clean:
	rm -f tema1