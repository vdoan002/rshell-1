CC = g++

FLAGS = -Wall -Werror -ansi -pedantic

all:
		if [ ! -d bin ]; then mkdir bin; fi
		$(CC) $(FLAGS) src/ls.cpp -o bin/ls
		$(CC) $(FLAGS) src/cp.cpp -o bin/cp 
		$(CC) $(FLAGS) src/main.cpp -o bin/rshell
rshell:
		if [ ! -d bin ]; then mkdir bin; fi
		$(CC) $(FLAGS) src/main.cpp -o bin/rshell
ls:
		if [ ! -d bin ]; then mkdir bin; fi
		$(CC) $(FLAGS)	src/ls.cpp -o bin/ls
cp:
		if [ ! -d bin ]; then mkdir bin; fi
		$(CC) $(FLAGS) src/cp.cpp -o bin/cp



