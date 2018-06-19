#include "../header/file.h"
#include <time.h>
#define NUM_ELT_REF_ARR 11

void printPbmTest(char **array, int width, int lenght) {
	int i, j;
	for(i=0;i<lenght;i++) {
		for(j=0;j<width;j++) {
            printf("%c", array[j][i]);
		} printf("\n");
	}
}


char **makeKBigger(char **arr, int k) {
    int width, lenght, i;
    lenght = 5 + 2*k;
    width = 3 + k;
    char **array = malloc(sizeof(char*)*(width));
    for(i=0; i<width; i++) {
        array[i] = malloc(sizeof(char)*lenght);

        int j;for(j=0;j<lenght;j++)
            array[i][j] = '0';
    } i = 0;

    int j;for(j=0; j < 7; j++) {
        if (arr[1][0] == 'X') {             // 0x0
            for(i=0;i<width;i++)            // 000
                array[i][0] = 'X';          // 111
        }
        if (arr[0][1] == 'X') {             // 000
            for(i=0;i<lenght/2;i++)         // x00
                array[0][i] = 'X';          // 111
        }
        if (arr[2][1] == 'X') {             // 000
            for(i=0;i<lenght/2;i++)         // 00x
                array[width-1][i] = 'X';    // 111
        }
        if (arr[1][2] == 'X') {             // 000
            for(i=0;i<width;i++)            // 000
                array[i][lenght/2] = 'X';   // 1X1
        }
        if (arr[0][3] == 'X') {
            for(i=lenght/2;i<lenght;i++)
                array[0][i] = 'X';
        }
        if (arr[2][3] == 'X') {
            for(i=lenght/2;i<lenght;i++)
                array[width-1][i] = 'X';
        }
        if (arr[1][4] == 'X') {
            for(i=0;i<width;i++)
                array[i][lenght-1] = 'X';
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

char **createDateArray(struct tm *actualTime, char ***referenceArray, int size) {
    int numArr[8];
    numArr[0] = actualTime->tm_hour % 10;
    numArr[1] = actualTime->tm_hour / 10;
    numArr[2] = 10;
    numArr[3] = actualTime->tm_min % 10;
    numArr[4] = actualTime->tm_min / 10;
    numArr[5] = 10;
    numArr[6] = actualTime->tm_sec % 10;
    numArr[7] = actualTime->tm_sec / 10;
    int u = 0;
    while(u < 8) {

    }
}

struct tm *datetime() {
    time_t result;
    result = time(NULL);
    return localtime(&result);
}

int main(int argc, char *argv[]) {
    system("clear");
    int k = 0;
    k += (int)argv[1];
    char ***arrayNumber = numberPbm(k);
    while(1) {
        int i = 0;
        int n = 5;
        while(i < n) {
            struct winsize w;
            ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

            struct tm *actualTime = datetime();
            char **pbmArray = createDateArray(actualTime, arrayNumber, 3 + k);
            //make an array of arrays which contain all numbers
            //print line by line this array
            sleep(1);
            //print sentence
            //add a point for each i
            i++;
        }
    }

    return 0;
}