#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	system("clear");
	FILE *f = fopen(argv[0], "r");
	if(f==NULL) {
		fprintf(stderr, "Une erreur est survenue lors de l'ouverture du fichier.\n");
		return EXIT_FAILURE;
	} else  {
		fseek(f, 0, SEEK_SET);
		while (fgetc(f)!=EOF) { //lis le fichier log.txt
			fseek(f, -1, SEEK_CUR);
			printf("%c", fgetc(f));
		}
	}
	return EXIT_SUCCESS;
}