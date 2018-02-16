#include <stdio.h>
#include <stdlib.h>
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

int main(int argc, char *argv[]) {
	system("clear");
	FILE *f = fopen(argv[0], "r");
	if(f==NULL) {
		fprintf(stderr, "Une erreur est survenue lors de l'ouverture du fichier.\n");
		fclose(f);
		return EXIT_FAILURE;
	} else  {
		struct winsize w;
    	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		char magicNumber[10] = "\0";
		int width, lenght;
		int N = lenFile(f);
		char *string = takeOffSharp(createArray(f, N));
		string = getDataPbm(string, magicNumber, &width, &lenght);
		string = takeOffCarriage(takeOffSpace(string));
		printPbm(stoarr(string, width, lenght), w.ws_row, w.ws_col, width, lenght);
		fgetc(stdin);
	}
	fclose(f);
	return EXIT_SUCCESS;
}