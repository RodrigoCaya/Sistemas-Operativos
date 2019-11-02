#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include "procesarCartas.h"


int compararTipoCarta(char* cartaMano, char* cartaBaraja) {
    int i = 0, largoTipo = 0;
    while (cartaMano[i] != '_') {
        largoTipo++;
        i++;
    }
    char tipoMano[largoTipo];
    i = 0;
    while (cartaMano[i] != '_') {
        tipoMano[i] = cartaMano[i];
        i++;
    }
    i = 0;
    largoTipo = 0;
    while (cartaBaraja[i] != '_') {
        largoTipo++;
        i++;
    }
    char tipoBaraja[largoTipo];
    i = 0;
    while (cartaBaraja[i] != '_') {
        tipoMano[i] = cartaBaraja[i];
        i++;
    }
    if (strcmp(tipoMano, tipoBaraja) == 0) return 1;
    else return 0;
}

int compararColores(char* cartaMano, char* cartaBaraja) {
    int i = 0, largoColor = 0;

    //Se busca donde parte la primera letra del color 
    while (i < strlen(cartaMano)) {
        if(cartaMano[i] == '_') {
            break;
        }
        i++;
    }

    //Se obtiene la cantidad de letras del color
    int comienzo = i + 1;
    for (i; i < strlen(cartaMano); i++) {
        if (cartaMano[i] == '.') break;
        largoColor++;
    }

    char colorCartaMano[largoColor];
    //Se crea un arreglo con el color dentro
    i = 0;
    for (comienzo; comienzo < strlen(cartaMano); comienzo++) {
        if (cartaMano[comienzo] == '.') break;
        colorCartaMano[i] = cartaMano[comienzo];
        i++;
    }
    largoColor = 0;
    i = 0;
    while (i < strlen(cartaBaraja)) {
        if(cartaBaraja[i] == '_') {
            break;
        }
        i++;
    }
    i++;
    comienzo = i;
    for (i; i < strlen(cartaBaraja); i++) {
        if (cartaBaraja[i] == '_') break;
        largoColor++;
    }
    char colorCartaBaraja[largoColor];
    i=0;
    for (comienzo; comienzo < strlen(cartaBaraja); comienzo++) {
        if (cartaBaraja[comienzo] == '_') break;
        colorCartaBaraja[i] = cartaBaraja[comienzo];
        i++;
    }

    //Una vez obtenidos ambos colores, se comparan y se retorna
    if(colorCartaBaraja[0] == colorCartaMano[0] && colorCartaBaraja[1] == colorCartaMano[1]) return 1;
    else return 0;
}

int preprocesarCarta(char* carta) {
    if (carta[0] == '1' || carta[0] == '2' || carta[0] == '3' || carta[0] == '4' || carta[0] == '5' || carta[0] == '6' || carta[0] == '7' || carta[0] == '8' || carta[0] == '9' || carta[0] == '0') {
        return 0;
    }
    else if (carta[0] == '+') {
        if (carta[1] == '2') return 1;
        else return 2;
    }
    else {
        int i = 0, largoTipo = 0;
        while (carta[i] != '_') {
            largoTipo++;
            i++;
        }
        char tipoMano[largoTipo];
        i = 0;
        while (carta[i] != '_') {
            tipoMano[i] = carta[i];
            i++;
        }

        tipoMano[i] = '\0';
        if (strcmp(tipoMano, "reversa") == 0) return 3;
        else if (strcmp(tipoMano, "salto") == 0) return 4;
        else return 5;
    }
}

int validar(char* cartaMano, char* cartaBaraja, int cantidadCartasASacar) {
    //Revisa si puede tirar la cartaMano
    //Modo 0: Prueba con una carta normal
    //Modo 1: Prueba con un +2
    //Modo 2: Prueba con un +4
    //Modo 3: Prueba con un reverse
    //Modo 4: Prueba con un salto
    //Modo 5: Prueba con una negra
    int modo = preprocesarCarta(cartaMano);
    //printf("Logro preprocesar la carta\n");
    //Para comparar carta normal
    if (modo == 0) {
        if (compararColores(cartaMano, cartaBaraja) == 1) return 1;
        else {
            if (cartaMano[0] == cartaBaraja[0]) return 1;
            else return 0;
        }
    }
    //Para comparar si tengo un +2
    else if (modo == 1) {
        if (compararColores(cartaMano, cartaBaraja) == 1) return 1;
        else {
            if ((cartaMano[0] == cartaBaraja[0]) && (cartaMano[1] == cartaBaraja[1])) return 1;
            else return 0;
        }
    }
    //Para comparar si tengo un +4
    else if (modo == 2) return 1;
    //Para comparar si tengo un reversa
    else if (modo == 3) {
        if (compararColores(cartaMano, cartaBaraja) == 1) return 1;
        else {
            if (compararTipoCarta(cartaMano, cartaBaraja) == 1) return 1;
            else return 0;
        }
    }
    //Para comparar si tengo un salto
    else if (modo == 4) {
        if (compararColores(cartaMano, cartaBaraja) == 1) return 1;
        else {
            if (compararTipoCarta(cartaMano, cartaBaraja) == 1) return 1;
            else return 0;
        }
    }
    //Para la carta negra (siempre se podra jugar)
    else {
        if (cantidadCartasASacar != 0) return 0;
        else return 1;
    }
}