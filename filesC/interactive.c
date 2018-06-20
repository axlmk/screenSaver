#include "../header/file.h"
#define DIM 6
#define NUM_FRAME 4

void printStringPlane(char *string) {
	int i;for(i=0;i<strlen(string);i++) {
		if(string[i]=='X')
			printf("%c", string[i]);
		else
			printf(" ");
	} printf("\n");
}

void spaceAbove(int y) {
	int i;for(i=0;i<y;i++)
		printf("\n");
}

void spaceLeft(int x) {
	int i;for(i=0;i<x;i++)
		printf(" ");
}
void displayPlane(int x, int y, int x_term, int y_term, char **plane) {
	system("clear");
	spaceAbove(y);
	int i;for(i=0;i<DIM;i++) {
		spaceLeft(x);
		printStringPlane(plane[i]);
	}
	spaceAbove(x_term-DIM-y);
}

FILE *openFile(int i) {
	char buffer[64]; buffer[0] = '\0';
	sprintf(buffer, "../pbm/plane%d.pbm", i);
	FILE *f = fopen(buffer, "r");
	if(f == NULL) {
		perror("Erreur lors de l'ouverture du fichier");
		return NULL;
	} else {
		return f;
	}
}

char ***setPlaneFrame() {
    char ***plane = malloc(sizeof(char**) * NUM_FRAME);
    int i;for(i=1;i<NUM_FRAME+1;i++) {
        FILE *f = openFile(i);
        plane[i-1] = clearPbm(createString(f, lenFile(f)));
        fclose(f);
    }
    return plane;
}

int moving(char key, int *x, int *y) {
	int end = 1;
	if(key == 'z') {
		*y-=1;
	} else if(key == 'q') {
		*x-=1;
	} else if(key == 'd') {
		*x+=1;
	} else if(key == 's') {
		*y+=1;
	} else if(key == 'l') {
		end = 0;
	}
	return end;
}

int main(int argc, char *argv[]) {
	if(argc==2) {
		int x_pos = atoi(argv[0]), y_pos = atoi(argv[1]);
		char ***plane = setPlaneFrame();
		int end = 1;
		while(end) {
			struct winsize w;
	        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
			displayPlane(x_pos, y_pos, w.ws_col, w.ws_row, plane[0]);
			char key = '0';
			scanf("%c", &key);
			end = moving(key, &x_pos, &y_pos);
		}
	} else {
		fprintf(stderr, "Erreur, le nombre d'arguments est invalide.\n");
		return EXIT_FAILURE;
	}
    return 0;
}
