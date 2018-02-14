#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

char *createArray(FILE f*, int N) {
	char *array = malloc(sizeof(char)*(N+1));
	fseek(f, 0, SEEK_SET);
	while(fgetc(f)!=EOF) {
		fseek(f, -1, SEEK_CUR)
		array[i]=fgetc(f);
	}
	return array;
}

char *eraseSharp(char *array) {

	return
}
}
int magicNumber(FILE *f) {

	return magic;
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
		char magicNumber[3] = "\0";
		int width, height;
		}
	}
	return EXIT_SUCCESS;
}