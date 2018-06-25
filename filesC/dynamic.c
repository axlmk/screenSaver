#include "../header/file.h"
#include "../header/date.h"
#include "../header/dateDisplay.h"
#include <time.h>

int main(int argc, char *argv[]) {
    int k = atoi(argv[1]);
	int N = 5;
    char ***arrayNumber = numberPbm(k);
    while(1) {
        int i = 0;
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        struct tm *actualTime = datetime();

        char **pbmArray = createDateArray(actualTime, arrayNumber, k);
		system("clear");
		printPbm(pbmArray, w.ws_row, w.ws_col, WIDTH*8, LENGHT, k);
		free(pbmArray);

		int j;for(j=0;j<(w.ws_col/2)-20;j++) {
			printf(" ");
		}
		printf("Cet ecran sera actualise dans quelques secondes");
		fflush(stdout);
		for(j=0;j<N;j++) {
			fflush(stdout);
	        sleep(1);
			printf(".");
        }
    }

    return 0;
}
