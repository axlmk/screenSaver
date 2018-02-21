#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/file.h"


void printStringPbm(char *string) {
	int i;for(i=0;i<strlen(string);i++) {
		if(string[i]=='0') {
			printf(" ");
		} else {
			printf("%c", string[i]);
		}
	} printf("\n");
}

void printPbm(char **array, int lenTer, int widTer, int width, int lenght) {
	int i, j;
	//fprintf(stderr, "%d %d %d %d", lenTer, widTer, width, lenght);
	for(i=0;i<(lenTer/2)-(lenght/2);i++) {
		printf("\n");
	}
	for(i=0;i<lenght;i++) {
		for(j=0;j<(widTer/2)-(width/2);j++) {
			printf(" ");
		}
		printStringPbm(array[i]);
	}
	for(i=0;i<(lenTer/2)-(lenght/2);i++)
		printf("\n");
}


char **makeKBigger(char **arr, int k) {
    int lenght, width, i;
    lenght = 5 + 2*k;
    width = 3 + k;
    char **array = malloc(sizeof(char*)*(width));
    for(i=0; i<width; i++) {
        array[i] = malloc(sizeof(char)*lenght);
        int j;for(j=0;i<lenght;i++)
            array[i][j] == '0';
    } i = 0;
    if(arr[1][0] == 'X') {
        for(i=0;i<width;i++)
            array[i][0] = 'X';
    } else if (arr[0][1] == 'X') {
        for(i=0;i<lenght/2;i++)
            array[0][i] = 'X';
    } else if (arr[2][1] == 'X') {
        for(i=0;i<lenght/2;i++)
            array[2][i] = 'X';
    } else if (arr[1][2] == 'X') {
        for(i=0;i<width;i++)
            array[i][2] = 'X';
    } else if (arr[0][3] == 'X') {
        for(i=lenght/2;i<lenght;i++)
            array[0][i] = 'X';
    } else if (arr[2][3] == 'X') {
        for(i=lenght/2;i<lenght;i++)
            array[2][i] = 'X';
    } else if (arr[0][4] == 'X') {
        for(i=0;i<width;i++)
            array[i][4] = 'X';
    }
    return array;
}

char **clearPbm(char *str) {
        char magicNumber[10] = "\0";
		int width, lenght;
		char *string = takeOffCarriage(takeOffSpace(getDataPbm(takeOffSharp(str), magicNumber, &width, &lenght))); 
        printf("%s\n", string);
        char **array = stoarr(string, width, lenght);
        printf("sdf");
        return array;
}

int main(int argc, char *arg[]) {
    system("clear");
    char ***arrayNumber = malloc(sizeof(char**)*10);
    int i;for(i=0;i<10;i++) {
        char buffer[64]; memset(buffer, 0, 64);
        char numb[2]; memset(numb, 0, 2);
        sprintf(buffer, "../pbm/%d.pbm", i);
        printf("-%s-\n", buffer);
        FILE *f = fopen(buffer, "r");
        if(f == NULL) {
            fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        } else {
            arrayNumber[i] = clearPbm(createString(f, lenFile(f)));
        }
        fclose(f);
        //printPbm(arrayNumber[i], 80, 20, 3, 5);
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
