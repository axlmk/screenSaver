#include "../header/file.h"
#include "../header/display.h"
#include "../header/shifting.h"
#define NUM_FRAME 4

FILE *openFile(int i) {
	char buffer[64]; buffer[0] = '\0';
	sprintf(buffer, "../pbm/plane/plane%d.pbm", i);
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

int main(int argc, char *argv[]) {
	if(argc==2) {
		srand(time(NULL));
		int planeFrame = rand()%4;
		int x_pos = atoi(argv[0]), y_pos = atoi(argv[1]);
		int end = 1;
		char ***plane = setPlaneFrame();
		char key = '0';
		while(end) {
			struct winsize w;
	        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
			x_pos = convert_x(x_pos, w.ws_col);
			y_pos = convert_y(y_pos, (w.ws_row - 1));
			displayPlane(x_pos, y_pos, w.ws_col, (w.ws_row - 1), plane[planeFrame]); //w.ws_row-1 car il faut compter la ligne de frappe des touches
			scanf("%c", &key);
			end = moving(key, &x_pos, &y_pos, &planeFrame);
		}
	} else {
		fprintf(stderr, "Erreur, le nombre d'arguments est invalide.\n");
		return EXIT_FAILURE;
	}
    return 0;
}
