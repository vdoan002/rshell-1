
CC = g++

FLAGS = -Wall -Werror -ansi -pedantic

all:	
		if [ ! -d "./bin" ];\
		then mkdir bin;\
		fi		
		$(CC) $(FLAGS) src/main.cpp -o bin/rshell

rshell:  
			$(CC) $(FLAGS) src/main.cpp -o bin/rshell
