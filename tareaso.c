#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>

#include "creacionJugadores.h"
#include "creacionMazo.h"
#include "procesarCartas.h"

#define READ 0
#define WRITE 1 


static char baraja[20];
static int cantidadCartasASacar = 0;
static int salto = 0;
static int reversa = 0;
static char color[10];



//------------------CREACION MAZO-----------------

//------------------CREACION JUGADORES------------

//------------------------------------------------

//------------------PROCESAR CARTAS---------------

//------------------------------------------------


void actualizacionDatos(char* buffer){
    int i, cont=0;
    int tamanio=0,*tamanios;
    tamanios = (int*)malloc(sizeof(int)*5);
    for (i=0 ; i<strlen(buffer) ; i++){
        if(buffer[i]==','){
            tamanios[cont] = tamanio;
            tamanio = 0;
            cont++;
        }
        else tamanio++;
    }
    tamanios[cont] = tamanio;
    char *baraja_aux = (char*)malloc(sizeof(char)*tamanios[0]);
    char *cantidadCartasASacar_aux = (char*)malloc(sizeof(char)*tamanios[1]);
    char *salto_aux = (char*)malloc(sizeof(char)*tamanios[2]);
    char *reversa_aux = (char*)malloc(sizeof(char)*tamanios[3]);
    char *color_aux = (char*)malloc(sizeof(char)*tamanios[4]);
    cont=0;
    int resta=0;
    for (i=0 ; i<strlen(buffer) ; i++){

        if(buffer[i]==','){
            cont++;
            resta = i+1;
        }
        else {
            if(cont == 0){
                baraja_aux[i]=buffer[i];
            }
            else if(cont == 1){
                cantidadCartasASacar_aux[i-resta]=buffer[i];
            }
            else if(cont == 2){
                salto_aux[i-resta]=buffer[i];
            }
            else if(cont == 3){
                reversa_aux[i-resta]=buffer[i];
            }
            else if(cont == 4){
                color_aux[i-resta]=buffer[i];
            }
        }
    }
    strcpy(baraja,baraja_aux);
    sscanf(cantidadCartasASacar_aux, "%d", &cantidadCartasASacar); 
    sscanf(salto_aux, "%d", &salto); 
    sscanf(reversa_aux, "%d", &reversa); 
    strcpy(color,color_aux);
}

//Valida si el jugador puede jugar (si hay saltos o reversa no puede)
int puedeJugar() {
    if (salto == 0 /*|| reversa == 0*/) return 1;
    if (salto == 1) {
        printf("Hay un salto en la baraja, se ha saltado tu turno!\n");
        salto = 0;
        return 0;
    }
    else return 0;
}

//Obtenemos la cantidad de cartas en el mazo
int cantidadMazo() {
    DIR *dir;
    struct dirent *sd;
    int cantidadMazo = 0;
    if ((dir = opendir("mazo")) != NULL) {
            sd = readdir(dir);
            sd = readdir(dir);
            while ((sd = readdir(dir)) != NULL) {
                cantidadMazo++;
            }
        }
    closedir(dir);
    return cantidadMazo;
}

//Entrega el numero de jugador (jugador 1, 2, 3 o 4)
int numeroJugador(char* jugador){
    int i = 0;
    while(jugador[i] != '_'){
        i++;
    }
    return ((int)jugador[i+1])-48;
}

//Busca la carta a jugar en la mano y la retorna
char* buscarEnMano(char* jugador, int lugar){
    //printf("JUGADOR : %s\n",jugador);
    //printf("LUGAR : %d\n",lugar);
    DIR *dir;
    char *carta = (char*)malloc(sizeof(char)*20);
    struct dirent *sd;
    if ((dir = opendir (jugador)) != NULL) {
        sd = readdir(dir);
        sd = readdir(dir);
        int i = 1; 
        while ((sd = readdir (dir)) != NULL) {
            if(i == lugar){
                strcpy(carta,"");
                strcpy(carta,sd->d_name);
                break;
            }
            i++;
        }
    }
    closedir (dir);
    return carta;
}

//Muestra la ultima carta jugada
void mostrarBaraja(){
    DIR *dir;
    struct dirent *sd;
    //char* str[20];
    dir = opendir("baraja");
    sd = readdir(dir);
    sd = readdir(dir);
    sd = readdir(dir);
    printf ("Baraja = %s\n",sd->d_name);
    closedir(dir);
    strcpy(baraja,sd->d_name);
}

//Cuando el jugador no tiene cartas para jugar, tendra que sacar del mazo
//Si hay +2 o +4 acumulados, tendra que sacar tantas cartas como se hayan acumulado
void sacarCartasMazo(char* jugador, char* carta){
    DIR *dir;
    struct dirent *sd;
    int random, cantidadCartasMazo = cantidadMazo(), i = 0, k;
    char str1[266];
    int file;
    //Obtenemos una carta del mazo al no tener cartas para jugar
    //O sacamos tantas cartas como se hayan acumulado por los +2 y +4
    if (strcmp(carta, "+1") == 0) {
        if (cantidadCartasASacar > 0) {
            printf("Tendrás que sacar %d cartas del mazo\n", cantidadCartasASacar);
            while (cantidadCartasASacar > 0) {
                k = 0;
                random = rand() % cantidadCartasMazo--;
                if ((dir = opendir("mazo")) != NULL) {
                    sd = readdir(dir);
                    sd = readdir(dir);
                    while ((sd = readdir(dir)) != NULL) {
                        if (k == random) {
                            strcpy(str1, "");
                            sprintf(str1, "%s/%s",jugador, sd->d_name);
                            file = open(str1,O_CREAT);
                            strcpy(str1, "");
                            sprintf(str1, "mazo/%s", sd->d_name);
                            remove(str1);
                            close(file);
                        }
                        k++;
                    }
                }
                cantidadCartasASacar--;
                closedir(dir);
            }
            cantidadCartasASacar = 0;
        }
        else {
            printf("Has sacado una carta del mazo\n");
            random = rand() % cantidadCartasMazo;
            if ((dir = opendir("mazo")) != NULL) {
                sd = readdir(dir);
                sd = readdir(dir);
                while ((sd = readdir(dir)) != NULL) {
                    if (i == random) {
                        strcpy(str1, "");
                        sprintf(str1, "%s/%s",jugador, sd->d_name);
                        file = open(str1,O_CREAT);
                        strcpy(str1, "");
                        sprintf(str1, "mazo/%s", sd->d_name);
                        remove(str1);
                        close(file);
                    }
                    i++;
                }
                closedir(dir);
            }
        }
    }
}

//Deja la carta usada por el jugador en la baraja y la elimina de su mano
void lanzarCarta(char* jugador, char* carta){
    DIR *dir;
    //struct dirent *sd;
    int file;
    char nombre[263];
    char opcion = ' ';
    if (preprocesarCarta(carta) == 1) cantidadCartasASacar += 2;
    if (preprocesarCarta(carta) == 2) {
        printf("Que color quieres escoger?\n");
        printf("1: Rojo\n");
        printf("2: Azul\n");
        printf("3: Amarillo\n");
        printf("4: Verde\n");
        scanf(" %c", color);
        if ((int)opcion-48 == 1) strcpy(color, "rojo");
        else if ((int)opcion-48 == 2) strcpy(color, "azul");
        else if ((int)opcion-48 == 3) strcpy(color, "amarillo");
        else strcpy(color, "verde");
        cantidadCartasASacar += 4;
    }

    if (preprocesarCarta(carta) == 3) {
        if (salto == 1) salto = 0;
        else salto = 1;
    }
    if (preprocesarCarta(carta) == 4) salto = 1;

    //Dejamos la carta jugada en la baraja
    if ((dir = opendir ("baraja")) != NULL) {
        strcpy(nombre, "");
        sprintf(nombre, "baraja/%s",carta);
        file = open(nombre, O_CREAT);
        //La carta jugada pasa a ser la que está en baraja
        strcpy(nombre, "");
        sprintf(nombre, "baraja/%s",baraja);
        //Eliminamos la carta que estaba antes en la baraja
        remove(nombre);
        strcpy(baraja,carta);
        closedir(dir);
        close(file);
    }
    //Eliminamos la carta jugada del jugador que la uso
    if ((dir = opendir (jugador)) != NULL) {
        strcpy(nombre, "");
        sprintf(nombre, "%s/%s", jugador, carta);
        remove(nombre);
        closedir(dir);
    }
}

//Pide una carta y valida si se puede jugar y la juega
int turnoJugador(char* jugador){
    char opcion = ' ';
    char *carta;

    //Muestra la ultima carta jugada
    mostrarBaraja();

    printf("¿Qué carta desea lanzar?\n");
    scanf(" %c",&opcion);

    //El jugador no tiene una carta y debe sacar del mazo, termina su turno
    if(((int)opcion-48) == 0){
        sacarCartasMazo(jugador, "+1");
        return 0;
    }
    //Obtenemos el nombre de la carta a jugar
    carta = buscarEnMano(jugador,((int)opcion)-48);
    //Validamos si se puede jugar
    if (validar(carta,baraja, cantidadCartasASacar) == 0) {//No se puede usar esa carta
        printf("No puedes jugar esa carta.\n");
        return 1;
    }
    else {
        lanzarCarta(jugador,carta);
        return 0;
    }
}

//Muestra la mano del jugador por pantalla
void mostrarMano(char* jugador){
    DIR *dir;
    struct dirent *sd;
    int i = 0;
    printf("Tus cartas son:\n");
    if ((dir = opendir (jugador)) != NULL) {
        sd = readdir(dir);
        sd = readdir(dir);
        while ((sd = readdir (dir)) != NULL) {
            printf ("Carta %i = %s\n",i+1,sd->d_name);
            i++;
        }
        printf("Seleccione 0 si no tiene una carta valida para jugar.\n");
    }
    closedir (dir);
}

int main() {
    mazo();
    jugador();
    creacionCartas();
    repartir();

    char *cartaInicio = empezar();
    strcpy(baraja, cartaInicio);
    free((void *)cartaInicio);

    if (preprocesarCarta(baraja) == 1) cantidadCartasASacar += 2;
    if (preprocesarCarta(baraja) == 2) cantidadCartasASacar += 4;
    if (preprocesarCarta(baraja) == 3) reversa = 1;
    if (preprocesarCarta(baraja) == 4) salto = 1;
    int empiezo = 0;
    int ganador = 0;
    int turnoJ1 = 1, turnoJ2 = 1, turnoJ3 = 1, turnoJ4 = 1;

    int fd12[2];
    int fd21[2];
    int fd13[2];
    int fd31[2];
    int fd14[2];
    int fd41[2];
    pipe(fd12);
    pipe(fd21);
    pipe(fd13);
    pipe(fd31);
    pipe(fd14);
    pipe(fd41);

    char buf12[60];
    char buf21[60];
    char buf13[60];
    char buf31[60];
    char buf14[60];
    char buf41[60];

    int pid[4],pid1,pid2,pid3;
    pid[0]=getpid();
    pid1 = fork();
    if (pid1 > 0){
        pid2 = fork();
        if(pid2 > 0){
            pid3 = fork();
            if(pid3 == 0) getpid();
        }
        else pid[2] = getpid();
    }
    else pid[1] = getpid();

    while(ganador == 0){
        if (pid1 == 0) {//jugador 2

            close(fd21[READ]);

            while(read(fd12[READ], buf12, sizeof(buf12)) <= 0){;}
            actualizacionDatos(buf12);
            if (cantidadMazo() > 0) {
                while(turnoJ2 == 1){
                    printf("Es el turno de Jugador 2\n");
                    printf("*******2***********\n");
                    mostrarMano("jugador_2");
                    if (turnoJ2 == 1) {
                        if (puedeJugar() == 1) {
                            turnoJ2 = turnoJugador("jugador_2");
                        }
                        else turnoJ2 = 0;
                    }
                    if (turnoJ2 == -1) ganador = 2;
                }
                strcpy(buf21, "");
                sprintf(buf21, "%s,%d,%d,%d,%s", baraja, cantidadCartasASacar, salto, reversa, color);
                write(fd21[WRITE], buf21, sizeof(buf21));
                turnoJ2 = 1;
            }
            else {

                printf("Se han acabado las cartas del mazo.\n");
                printf("Fin del juego.\n");
                exit(1);
            }
        }
        
        else {
            if (pid2 == 0){//jugador 3

                close(fd31[READ]);

                while(read(fd13[READ], buf13, sizeof(buf13)) <= 0){;}
                actualizacionDatos(buf13);

                if (cantidadMazo() > 0) {
                    while(turnoJ3 == 1){
                        printf("Es el turno de Jugador 2\n");
                        mostrarMano("jugador_2");
                        if (turnoJ3 == 1) {
                            if (puedeJugar() == 1) {
                                turnoJ3 = turnoJugador("jugador_2");
                            }
                            else turnoJ3 = 0;
                        }
                        if (turnoJ3 == -1) ganador = 3;
                    }
                    strcpy(buf31, "");
                    sprintf(buf31, "%s,%d,%d,%d,%s", baraja, cantidadCartasASacar, salto, reversa, color);
                    write(fd31[WRITE], buf31, sizeof(buf31));
                    turnoJ3 = 1;
                }
                else {
                    printf("Se han acabado las cartas del mazo.\n");
                    printf("Fin del juego.\n");
                    exit(1);
                }
            }
            else{
                if (pid3 == 0){//jugador 4

                    close(fd41[READ]);

                    while(read(fd14[READ], buf14, sizeof(buf14)) <= 0){;}
                    actualizacionDatos(buf14);

                    if (cantidadMazo() > 0) {
                        while(turnoJ4 == 1){
                            printf("Es el turno de Jugador 2\n");
                            mostrarMano("jugador_2");
                            if (turnoJ4 == 1) {
                                if (puedeJugar() == 1) {
                                    turnoJ4 = turnoJugador("jugador_2");
                                }
                                else turnoJ4 = 0;
                            }
                            if (turnoJ4 == -1) ganador = 4;
                        }
                        strcpy(buf41, "");
                        sprintf(buf41, "%s,%d,%d,%d,%s", baraja, cantidadCartasASacar, salto, reversa, color);
                        write(fd41[WRITE], buf41, sizeof(buf41));
                        turnoJ4 = 1;
                    }
                    else {
                        printf("Se han acabado las cartas del mazo.\n");
                        printf("Fin del juego.\n");
                        exit(1);
                    }
                }
                else{//jugador 1 
                    if (empiezo == 1) {
                        while(cantidadMazo() > 0) {
                            while(read(fd41[READ], buf41, sizeof(buf41)) <= 0){;}
                            actualizacionDatos(buf41);
                            if (cantidadMazo() > 0) {
                                while(turnoJ1 == 1){
                                    printf("Es el turno de Jugador 1\n");
                                    mostrarMano("jugador_1");
                                    if (turnoJ1 == 1) {
                                        if (puedeJugar() == 1) {
                                            turnoJ1 = turnoJugador("jugador_1");
                                        }
                                        else turnoJ1 = 0;
                                    }
                                    if (turnoJ1 == -1) ganador = 1;
                                }
                                turnoJ1 = 1;
                                strcpy(buf14, "");
                                sprintf(buf14, "%s,%d,%d,%d,%s", baraja, cantidadCartasASacar, salto, reversa, color);
                                write(fd14[WRITE], buf14, sizeof(buf14));
                                
                                read(fd21[READ], buf21, sizeof(buf21));
                                actualizacionDatos(buf21);

                                strcpy(buf13, "");
                                sprintf(buf13, "%s,%d,%d,%d,%s", baraja, cantidadCartasASacar, salto, reversa, color);
                                write(fd13[WRITE], buf13, sizeof(buf13));

                                read(fd31[READ], buf31, sizeof(31));
                                actualizacionDatos(buf31);

                                strcpy(buf14, "");
                                sprintf(buf14, "%s,%d,%d,%d,%s", baraja, cantidadCartasASacar, salto, reversa, color);
                                write(fd14[WRITE], buf14, sizeof(buf14));
                            }
                            else {
                                printf("Se han acabado las cartas del mazo.\n");
                                printf("Fin del juego.\n");
                                exit(1);
                            }
                        }
                    }
                    else {
                        empiezo = 1;
                        if (cantidadMazo() > 0) {
                            while(turnoJ1 == 1){
                                printf("Es el turno de Jugador 1\n");
                                mostrarMano("jugador_1");
                                if (turnoJ1 == 1) {
                                    if (puedeJugar() == 1) {
                                        turnoJ1 = turnoJugador("jugador_1");
                                    }
                                    else turnoJ1 = 0;
                                }
                                if (turnoJ1 == -1) ganador = 1;
                            }
                            strcpy(buf14, "");
                            sprintf(buf14, "%s,%d,%d,%d,%s", baraja, cantidadCartasASacar, salto, reversa, color);
                            write(fd14[WRITE], buf14, sizeof(buf14));
                            turnoJ1 = 1;
                        }
                        else {
                            printf("Se han acabado las cartas del mazo.\n");
                            printf("Fin del juego.\n");
                            exit(1);
                        }
                    }
                }
            }
        }
    }
    printf("EL GANADOR ES EL JUGADOR %d\n",ganador);
    return 0;
}