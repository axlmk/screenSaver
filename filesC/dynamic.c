#include "../header/file.h"
#include <time.h>
#define NUM_ELT_REF_ARR 11
#define LENGHT 5
#define WIDTH 3

/*void printPbmTest(char **array, int width, int lenght, int k) {
	int i, j;
	for(i=0;i<lenght + 2*k;i++) {
		for(j=0;j<width + k;j++) {
            printf("%c", array[i][j]);
		} printf("\n");
	}
	printf("\n");
}*/

void printStringPbm(char *string, int k) {
	int i=0;
	while(i<strlen(string)) {
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
		for(j=0;j<((widTer)/2)-((width+7)/2);j++) {
			printf(" ");
		}
		printStringPbm(array[i], k);
	}
	for(i=0;i<(lenTer/2)-(lenght/2);i++)
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
    }
    return array;
}

char **clearPbm(char *str) {
        char magicNumber[10] = "\0";
		int width, lenght;
		char *string = takeOffCarriage(takeOffSpace(getDataPbm(takeOffSharp(str), magicNumber, &width, &lenght)));
        char **array = stoarr(string, width, lenght);
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
		dateArray[i] = malloc(sizeof(char)*((WIDTH+k)*8+7));
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
    //system("clear");
    int k = 0;
    //k += (int)argv[1];
    char ***arrayNumber = numberPbm(k);
    //while(1) {
        int i = 0;
        int n = 1;
        while(i < n) {
            struct winsize w;
            ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

            struct tm *actualTime = datetime();
            char **pbmArray = createDateArray(actualTime, arrayNumber, k);
			printPbm(pbmArray, w.ws_row, w.ws_col, WIDTH*7, LENGHT, k);
            sleep(1);
            //print sentence
            //add a point for each i
            i++;
        }
    //}

    return 0;
}
