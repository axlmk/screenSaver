#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/file.h"

char **clearPbm(char *str) {
        char magicNumber[10] = "\0";
		int width, lenght;
		stoarr(takeOffCarriage(takeOffSpace(getDataPbm(takeOffSharp(str), magicNumber, &width, &lenght))), width, lenght);
}

int main(int argc, char *arg[]) {
    system("clear");
    int i;for(i=0;i<10;i++) {
        char buffer [64]; memset(buffer, 0, 64);
        strcpy(buffer, "../pbm/");
        strcat(buffer, i);
        strcat(buffer, ".pbm");
        FILE *f = fopen(buffer, "r");
        clearPbm(createString(f, lenFile(f)));
    }
    // help : utiliser tableau de tableau pour afficher au fur et à mesure les lignes des chiffres
    //import all numbers
    //clear all and make arrays
    //make k-bigger arrays
    //while 1
    //while i < n
    //get size
    //get date
    //make an array of arrays which contain all numbers
    //print line by line this array
    //wait 1 second
    //print sentence
    //add a point for each i

    return 0;
}
