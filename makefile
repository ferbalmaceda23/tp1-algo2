CFLAGS=-g -O0 -std=c99 -Wall -Werror -Wconversion -lm

evento_pesca: evento_pesca.c main.c
	gcc evento_pesca.c main.c $(FLAGS) -o evento_pesca

ejecutar: evento_pesca
	clear
	./evento_pesca arrecife.txt acuario.txt

debug: evento_pesca
	gdb ./evento_pesca

prueba: evento_pesca
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./evento_pesca arrecife.txt acuario.txt
