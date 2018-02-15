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

char *takeOffData(char *array, int N) {
	int i=N, len = strlen(array);
	char *buffer = malloc(sizeof(char)*(len-N));
	memset(buffer, 0, len-N);
	while(array[i]!='\0') {
		buffer[i-N] = array[i];
		i++;
	}
	//fprintf(stderr, "%s", buffer);
	return buffer;
}

char *getDataPbm(char *array, char *magicNumber, int *width, int *lenght) {
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
	}i++; *lenght = atoi(buffer);
	return takeOffData(array, i);
}

int lenFile(FILE *f) {
	fseek(f, 0, SEEK_END);
	int n = ftell(f);
	fseek(f, 0, SEEK_SET);
	return n;

}

char *takeOffCarriage(char *array) {
	int N = strlen(array), i=0, j=0;
	char *buffer = malloc(sizeof(char)*N);
	memset(buffer, 0, N);
	while(i<N) {
		if(array[i]=='\n') {
			i++;
		} else {
			buffer[j] = array[i];
			i++; j++;
		}
	};
	return buffer;
}

char *takeOffSpace(char *array) {

}

char **stoarr(char *array, int width, int lenght) {
	char **buffer = malloc(sizeof(char*)*width);
	int i;for(i=0;i<width;i++)
		buffer[i] = malloc(sizeof(char)*lenght);

	int j;for(j=0;j<lenght;j++) {
		for(i=0;i<width;i++)
			buffer[j][i] = array[j*lenght+i];
	}
	return buffer;

}

char *takeOffSharp(char *array) { //si # a la derniere ligne on a un \n en trop car il va garder le dernier \n "enregistré"
	int i=0, j=0, N = strlen(array);
	char *buffer = malloc(sizeof(char)*N);
	memset(buffer, 0, N);
	while(i<N) {
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
		printf("%s", string);
		//string = getDataPbm(string, magicNumber, &width, &lenght);
		//string = takeOffCarriage(string);
		//printPbm(stoarr(string, width, lenght), w.ws_row, w.ws_col, width, lenght);
	}
	fclose(f);
	return EXIT_SUCCESS;
}