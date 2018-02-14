#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

char *createArray(FILE *f, int N) {
	char *array = malloc(sizeof(char)*(N+1));
	fseek(f, 0, SEEK_SET);
	int i=0;while(fgetc(f)!=EOF) {
		fseek(f, -1, SEEK_CUR);
		array[i]=fgetc(f);
		i++;
	}
	return array;
}

char *takeOffData(char *array) {

}

void getDataPbm(char *array, char *magicNumber, int *width, int *lenght) {
	int i=0, j=0, n=0;
	char buffer[10] = "\0";
	while(array[i]!='\n') {
		buffer[j]=array[i];
		i++;j++;
	}i++; strcpy(magicNumber, buffer); memset(buffer, 0, 10); j=0;//magicNumber

	while(array[i]!='\n') {
		buffer[j]=array[i];
		i++;j++;
	}i++; *width = atoi(buffer); memset(buffer, 0, 10), j=0;

	while(array[i]!='\n') {
		buffer[j]=array[i];
		i++;j++;
	}*lenght = atoi(buffer);

}

int lenFile(FILE *f) {
	fseek(f, 0, SEEK_END);
	int n = ftell(f);
	fseek(f, 0, SEEK_SET);
	return n;

}

char *eraseSharp(char *array, int N) { //si # a la derniere ligne on a un \n en trop car il va garder le dernier \n "enregistré"
	int i=0, j=0;
	char *buffer = malloc(sizeof(char)*N);
	memset(buffer, 0, N);
	while(array[i]!='\0') {
		if(array[i]=='#') {
			while(array[i]!='\n' && array[i]!='\0') {
				i++;
			} i++;
		} else {
			buffer[j] = array[i];
			j++;i++;
		}
	}
	return buffer;
}

int main(int argc, char *argv[]) {
	system("clear");
	FILE *f = fopen(argv[0], "r");
	if(f==NULL) {
		fprintf(stderr, "Une erreur est survenue lors de l'ouverture du fichier.\n");
		return EXIT_FAILURE;
	} else  {
		struct winsize w;
    	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		char magicNumber[10] = "\0";
		int width, length;
		char *array = eraseSharp(createArray(f, lenFile(f)), lenFile(f));
		getDataPbm(array, magicNumber, &width, &length);
	}
	return EXIT_SUCCESS;
}