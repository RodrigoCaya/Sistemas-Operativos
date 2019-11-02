run: main.o creacionJugadores.o creacionMazo.o procesarCartas.o
		gcc -g -Wall -o tarea tareaso.o creacionJugadores.o creacionMazo.o procesarCartas.o

main.o: tareaso.c
		gcc -c tareaso.c -Wall

creacionJugadores.o: creacionJugadores.h creacionJugadores.c
		gcc -Wall -g -c creacionJugadores.h creacionJugadores.c

creacionMazo.o: creacionMazo.h creacionMazo.c
		gcc -Wall -g -c creacionMazo.h creacionMazo.c

procesarCartas.o: procesarCartas.h procesarCartas.c
		gcc -Wall -g -c procesarCartas.h procesarCartas.c

clean:
		rm main.o creacionMazo.o creacionJugadores.o tarea
