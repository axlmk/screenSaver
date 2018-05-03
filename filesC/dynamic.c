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

char **createDateArray(struct tm *actual_time, char ***referenceArray) {

}

struct tm *datetime() {
    time_t result;
    result = time(NULL);
    return localtime(&result);
}

int main(int argc, char *argv[]) {
    system("clear");
    //int k = (int)argv[1];
    char ***arrayNumber = numberPbm(2);
    while(1) {
        int i = 0;
        while(i < n) {
            struct winsize w;
            ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

            struct tm *actual_time = datetime();
            char **pbmArray = createDateArray(actual_time, arrayNumber);
            //make an array of arrays which contain all numbers
            //print line by line this array
            //wait 1 second
            //print sentence
            //add a point for each i
        }
    }

    return 0;
}
