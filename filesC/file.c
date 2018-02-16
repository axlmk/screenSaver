#include "../header/file.h"

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
	int N = strlen(array), i=0, j=0;
	char *buffer = malloc(sizeof(char)*N);
	memset(buffer, 0, N);
	while(i<N) {
		if(array[i]==' ') {
			i++;
		} else {
			buffer[j] = array[i];
			i++; j++;
		}
	};
	return buffer;

}

char **stoarr(char *array, int width, int lenght) {
	char **buffer = malloc(sizeof(char*)*width);
	int i;for(i=0;i<width;i++)
		buffer[i] = malloc(sizeof(char)*lenght);

	int j;for(j=0;j<lenght;j++) {
		for(i=0;i<width;i++)
			buffer[j][i] = array[j*width+i];
	}
	return buffer;

}

char *takeOffSharp(char *array) { //si # a la derniere ligne on a un \n en trop car il va garder le dernier \n "enregistré"
	int i=0, j=0, N = strlen(array);
	char *buffer = malloc(sizeof(char)*N);
	memset(buffer, 0, N);
	while(i<N) {
		if(array[i]=='#') {
			if(i==0) {
				while(array[i]!='\n' && array[i]!='\0')
					i++;
				i++;
			} else if(array[i-1]=='\n') {
				while(array[i]!='\n' && array[i]!='\0')
					i++;
				i++;
			} else {
				while(array[i]!='\n' && array[i]!='\0')
					i++;
			}
		} else {
			buffer[j] = array[i];
			j++;i++;
		}
	}
	return buffer;
}