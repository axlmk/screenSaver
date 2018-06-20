#include "../header/file.h"
#include <time.h>
#define NUM_ELT_REF_ARR 11
#define LENGHT 5
#define WIDTH 3

void printPbmTest(char **array, int width, int k) {
	int i, j;
	for(i=0;i<LENGHT + 2*k;i++) {
		for(j=0;j<width + k;j++) {
            printf("%c", array[i][j]);
		} printf("\n");
	}
	printf("\n");
}

void printStringPbm(char *string, int width, int k) {
	int i=0;
	while(i<(WIDTH+k)*8) {
		//printf("\nlen : %d\n", strlen(string));
		if((i%(k+WIDTH))==0) {
			printf(" ");
		}
		if(string[i]=='0') {
			printf(" ");
		} else {
			printf("%c", string[i]);
		}
		i++;
	} printf("\n");
}

void printPbm(char **array, int lenTer, int widTer, int width, int lenght, int k) {
	int i, j;
	width += k;
	lenght += 2*k;
	for(i=0;i<(lenTer/2)-(lenght/2);i++) {
		printf("\n");
	}
	for(i=0;i<lenght;i++) {
		for(j=0;j<(widTer/2)-(((WIDTH+k)*8+8)/2);j++) {
			printf(" ");
		}
		printStringPbm(array[i], width, k);
	}
	for(i=0;i<(lenTer/2)-(lenght/2)-5;i++)
		printf("\n");
}

char **makeKBigger(char **arr, int k) {
    int width, lenght, i;
    lenght = LENGHT + 2*k;
    width = WIDTH + k;
    char **array = malloc(sizeof(char*)*(lenght));
    for(i=0; i<lenght; i++) {
        array[i] = malloc(sizeof(char)*width);
        int j;for(j=0;j<width;j++)
            array[i][j] = '0';
    } i = 0;
    int j;for(j=0; j < 7; j++) {
        if (arr[0][1] == 'X') {             // 0x0
            for(i=0;i<width;i++)            // 000
                array[0][i] = 'X';          // 111
        }
        if (arr[1][0] == 'X') {             // 000
            for(i=0;i<lenght/2;i++)         // x00
                array[i][0] = 'X';          // 111
        }
        if (arr[1][2] == 'X') {             // 000
            for(i=0;i<lenght/2;i++)         // 00x
                array[i][width-1] = 'X';    // 111
        }
        if (arr[2][1] == 'X') {             // 000
            for(i=0;i<width;i++)            // 000
                array[lenght/2][i] = 'X';   // 1X1
        }
        if (arr[3][0] == 'X') {
            for(i=lenght/2;i<lenght;i++)
                array[i][0] = 'X';
        }
        if (arr[3][2] == 'X') {
            for(i=lenght/2;i<lenght;i++)
                array[i][width-1] = 'X';
        }
        if (arr[4][1] == 'X') {
            for(i=0;i<width;i++)
                array[lenght-1][i] = 'X';
        }
		if(arr[1][1] == 'X' && arr[3][1] == 'X') {
			array[(LENGHT+2*k)/3][(WIDTH+k)/2] = 'X';
			array[2*(LENGHT+2*k)/3][(WIDTH+k)/2] = 'X';
		}
    }
    return array;
}

char ***numberPbm(int k) {
    char ***arrayNumber = malloc(sizeof(char**) * NUM_ELT_REF_ARR);
    int i;for(i=0;i<NUM_ELT_REF_ARR;i++) {
        char buffer[64]; buffer[0] = '\0';
        sprintf(buffer, "../pbm/%d.pbm", i);
        FILE *f = fopen(buffer, "r");
        if(f == NULL) {
            perror("Erreur lors de l'ouverture du fichier");
        } else {
            arrayNumber[i] = clearPbm(createString(f, lenFile(f)));
            arrayNumber[i] = makeKBigger(arrayNumber[i], k);
        }
        fclose(f);
    }
    return arrayNumber;
}

char **createDateArray(struct tm *actualTime, char ***referenceArray, int k) {
    int numArr[8];
    numArr[0] = actualTime->tm_hour / 10;
    numArr[1] = actualTime->tm_hour % 10;
    numArr[2] = 10;
    numArr[3] = actualTime->tm_min / 10;
    numArr[4] = actualTime->tm_min % 10;
    numArr[5] = 10;
    numArr[6] = actualTime->tm_sec / 10;
    numArr[7] = actualTime->tm_sec % 10;
	char **dateArray = malloc(sizeof(char*)*(LENGHT+2*k));
	int i;for(i=0;i<LENGHT+2*k;i++)
		dateArray[i] = malloc(sizeof(char)*((WIDTH+k)*8));
	int j;for(j=0;j<LENGHT+2*k;j++) {
		int u = 0;
	    while(u < 8) {
			for(i=0;i<WIDTH+k;i++)
				dateArray[j][i+u*(WIDTH+k)] = referenceArray[numArr[u]][j][i];
			u++;
	    }
	}
	return dateArray;
}

struct tm *datetime() {
    time_t result;
    result = time(NULL);
    return localtime(&result);
}

int main(int argc, char *argv[]) {
    int k = 3;
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
