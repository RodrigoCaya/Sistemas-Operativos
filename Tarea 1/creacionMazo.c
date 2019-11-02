#include "creacionMazo.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

void creacionCartas(){
    int file;
    file = open("mazo/0_rojo.txt", O_CREAT);
    close(file);
    file = open("mazo/+2_rojo_1.txt", O_CREAT);
    close(file);
    file = open("mazo/+2_rojo_2.txt", O_CREAT);
    close(file);
    file = open("mazo/reversa_rojo_1.txt", O_CREAT);
    close(file);
    file = open("mazo/reversa_rojo_2.txt", O_CREAT);
    close(file);
    file = open("mazo/salto_rojo_1.txt", O_CREAT);
    close(file);
    file = open("mazo/salto_rojo_2.txt", O_CREAT);
    close(file);

    file = open("mazo/0_amarillo.txt", O_CREAT);
    close(file);
    file = open("mazo/+2_amarillo_1.txt", O_CREAT);
    close(file);
    file = open("mazo/+2_amarillo_2.txt", O_CREAT);
    close(file);
    file = open("mazo/reversa_amarillo_1.txt", O_CREAT);
    close(file);
    file = open("mazo/reversa_amarillo_2.txt", O_CREAT);
    close(file);
    file = open("mazo/salto_amarillo_1.txt", O_CREAT);
    close(file);
    file = open("mazo/salto_amarillo_2.txt", O_CREAT);
    close(file);

    file = open("mazo/0_verde.txt", O_CREAT);
    close(file);
    file = open("mazo/+2_verde_1.txt", O_CREAT);
    close(file);
    file = open("mazo/+2_verde_2.txt", O_CREAT);
    close(file);
    file = open("mazo/reversa_verde_1.txt", O_CREAT);
    close(file);
    file = open("mazo/reversa_verde_2.txt", O_CREAT);
    close(file);
    file = open("mazo/salto_verde_1.txt", O_CREAT);
    close(file);
    file = open("mazo/salto_verde_2.txt", O_CREAT);
    close(file);

    file = open("mazo/0_azul.txt", O_CREAT);
    close(file);
    file = open("mazo/+2_azul_1.txt", O_CREAT);
    close(file);
    file = open("mazo/+2_azul_2.txt", O_CREAT);
    close(file);
    file = open("mazo/reversa_azul_1.txt", O_CREAT);
    close(file);
    file = open("mazo/reversa_azul_2.txt", O_CREAT);
    close(file);
    file = open("mazo/salto_azul_1.txt", O_CREAT);
    close(file);
    file = open("mazo/salto_azul_2.txt", O_CREAT);
    close(file);

    char str1[30];
    char str2[30];
    int i;
    for (i = 1; i < 10; i++) {
        strcpy(str1, "");
        sprintf(str1, "mazo/%d_rojo_1.txt",i);
        strcpy(str2, "");
        sprintf(str2, "mazo/%d_rojo_2.txt", i);
        file = open(str1,O_CREAT);
        close(file);
        file = open(str2,O_CREAT);
        close(file);

        strcpy(str1, "");
        sprintf(str1, "mazo/%d_amarillo_1.txt",i);
        strcpy(str2, "");
        sprintf(str2, "mazo/%d_amarillo_2.txt", i);
        file = open(str1,O_CREAT);
        close(file);
        file = open(str2,O_CREAT);
        close(file);

        strcpy(str1, "");
        sprintf(str1, "mazo/%d_verde_1.txt",i);
        strcpy(str2, "");
        sprintf(str2, "mazo/%d_verde_2.txt", i);
        file = open(str1,O_CREAT);
        close(file);
        file = open(str2,O_CREAT);
        close(file);

        strcpy(str1, "");
        sprintf(str1, "mazo/%d_azul_1.txt",i);
        strcpy(str2, "");
        sprintf(str2, "mazo/%d_azul_2.txt", i);
        file = open(str1,O_CREAT);
        close(file);
        file = open(str2,O_CREAT);
        close(file);
    }
    if(file < 0){
        printf("error al crear archivo\n");
    }
    else{
        printf("se creo el archivo\n");
    }
}
void mazo(){
    mkdir("mazo", 0777);
    char str1[30];
    char str2[30];
    int i, file;
    for (i = 1; i < 5; i++) {
        strcpy(str1, "");
        sprintf(str1, "mazo/colores_negra_%d.txt",i);
        strcpy(str2, "");
        sprintf(str2, "mazo/+4_negra_%d.txt", i);
        file = open(str1,O_CREAT);
        close(file);
        file = open(str2,O_CREAT);
        close(file);
    }
}
void repartir(){
    DIR *archivo;
    struct dirent *sd;
    int arreglo_rndms[28] ,arreglo_j1[7], arreglo_j2[7], arreglo_j3[7], arreglo_j4[7];
    int random, i = 0, j, cont, file;
    char str1[266];

    archivo = opendir("mazo");    
    int flag = 1;
    while (flag){
        random = rand() % 109;
        cont = 0;
        for (j=0 ; j<i ; j++){
            if(arreglo_rndms[j] == random) cont++;
        }
        if (cont == 0){
            arreglo_rndms[i] = random;
            i++;
        }
        if (i == 28) flag = 0;
    }
    for (i=0 ; i<7 ; i++){
        arreglo_j1[i] = arreglo_rndms[i];
        arreglo_j2[i] = arreglo_rndms[i+7];
        arreglo_j3[i] = arreglo_rndms[i+14];
        arreglo_j4[i] = arreglo_rndms[i+21];
    }
    sd = readdir(archivo);
    sd = readdir(archivo);
    for (i=0 ; i<108 ; i++ ){
        sd = readdir(archivo);
        for(j=0 ; j<7 ; j++){
            if (arreglo_j1[j] == i){
                strcpy(str1, "");
                sprintf(str1, "jugador_1/%s",sd->d_name);
                file = open(str1,O_CREAT);
                close(file);
                chdir("mazo");
                remove(sd->d_name);
                chdir("..");
            }
            if (arreglo_j2[j] == i){
                strcpy(str1, "");
                sprintf(str1, "jugador_2/%s",sd->d_name);
                file = open(str1,O_CREAT);
                close(file);
                chdir("mazo");
                remove(sd->d_name);
                chdir("..");
            }
            if (arreglo_j3[j] == i){
                strcpy(str1, "");
                sprintf(str1, "jugador_3/%s",sd->d_name);
                file = open(str1,O_CREAT);
                close(file);
                chdir("mazo");
                remove(sd->d_name);
                chdir("..");
            }
            if (arreglo_j4[j] == i){
                strcpy(str1, "");
                sprintf(str1, "jugador_4/%s",sd->d_name);
                file = open(str1,O_CREAT);
                close(file);
                chdir("mazo");
                remove(sd->d_name);
                chdir("..");
            }
        }
    }
    closedir(archivo);
}
char* empezar(){
    DIR *archivo;
    char nombre[263];
    char *carta = (char *)malloc(sizeof(char)*20);
    int file,i,rndm;
    mkdir("baraja", 0777);
    struct dirent *sd;
    archivo = opendir("mazo");
    sd = readdir(archivo);
    sd = readdir(archivo);
    rndm = rand() % 80;
    for (i = 0; i < 80; i++) {
        sd = readdir(archivo);
        if (i == rndm) {
            strcpy(nombre, "");
            sprintf(nombre, "baraja/%s",sd->d_name);
            chdir("mazo");
            remove(sd->d_name);
            chdir("..");
            file = open(nombre,O_CREAT);
            close(file);
            break;
        }
    }
    strcpy(carta,sd->d_name);
    closedir(archivo);
    return carta;
}