#include "creacionJugadores.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

void jugador(){
    mkdir("jugador_1", 0777);
    mkdir("jugador_2", 0777);
    mkdir("jugador_3", 0777);
    mkdir("jugador_4", 0777);
}