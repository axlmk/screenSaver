#include "../header/dateDisplay.h"

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
