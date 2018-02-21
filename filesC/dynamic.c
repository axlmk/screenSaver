#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/file.h"

void printArray(char **array, int width, int lenght) {
	int i, j;
	for(i=0;i<lenght;i++) {
        for(j=0;j<width;j++)
            printf("%c", array[i][j]);
        printf("\n");
    }
}


char **makeKBigger(char **arr, int k) {
    int lenght, width, i;
    lenght = 5 + 2*k;
    width = 3 + k;
    char **array = malloc(sizeof(char*)*(lenght));
    for(i=0; i<lenght; i++) {
        array[i] = malloc(sizeof(char)*width);
        int j;for(j=0;j<width;j++)
            array[i][j] == '0';
    } i = 0;
    if(arr[0][1] == '1') {
        for(i=0;i<width;i++)
            array[0][i] = 'X';
    } else if (arr[1][0] == '1') {
        for(i=0;i<lenght/2;i++)
            array[i][0] = 'X';
    } else if (arr[1][2] == '1') {
        for(i=0;i<lenght/2;i++)
            array[i][2] = 'X';
    } else if (arr[2][1] == '1') {
        for(i=0;i<width;i++)
            array[2][i] = 'X';
    } else if (arr[3][0] == '1') {
        for(i=lenght/2;i<lenght;i++)
            array[i][0] = 'X';
    } else if (arr[3][2] == '1') {
        for(i=lenght/2;i<lenght;i++)
            array[i][2] = 'X';
    } else if (arr[4][1] == '1') {
        for(i=0;i<width;i++)
            array[4][i] = 'X';
    }
    return array;
}

char **clearPbm(char *str) {
        char magicNumber[10] = "\0";
		int width, lenght;
		char *string = takeOffCarriage(takeOffSpace(getDataPbm(takeOffSharp(str), magicNumber, &width, &lenght)));
        char **array = stoarr(string, width, lenght);
        return array;
}

int main(int argc, char *arg[]) {
    system("clear");
    char ***arrayNumber = malloc(sizeof(char**)*10);
    int i;for(i=0;i<10;i++) {
        char buffer[64]; memset(buffer, 0, 64);
        char numb[2]; memset(numb, 0, 2);
        sprintf(buffer, "../pbm/%d.pbm", i);
        FILE *f = fopen(buffer, "r");
        if(f == NULL) {
            fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        } else {
            arrayNumber[i] = clearPbm(createString(f, lenFile(f)));
            arrayNumber[i] = makeKBigger(arrayNumber[i], 1);
        } printArray(arrayNumber[i], 4, 7);
        fclose(f);
    }
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
