#include "../header/display.h"

void printStringPlane(char *string, int n, int len) {
	int i;for(i=n;i<len;i++) {
		if(string[i]=='X')
			printf("%c", string[i]);
		else
			printf(" ");
	}
}

void spaceAbove(int y) {
	int i;for(i=0;i<y;i++)
		printf("\n");
}

void spaceLeft(int x) {
	int i;for(i=0;i<x;i++)
		printf(" ");
}

void displayPlaneXAxe(int x, int x_term, int n, int k, char **plane) {
	int i;for(i=n;i<k;i++) {
		if(x_term-
			DIM < x && x < x_term) {
			printStringPlane(plane[i], x_term-x, DIM);
			spaceLeft(x_term-DIM);
			printStringPlane(plane[i], 0, x_term-x);
			printf("\n");
		} else {
			spaceLeft(x);
			printStringPlane(plane[i], 0, DIM);
			printf("\n");
		}
	}
}

void displayPlane(int x, int y, int x_term, int y_term, char **plane) {
	system("clear");
	if(y_term-DIM < y && y < y_term){
		displayPlaneXAxe(x, x_term, y_term-y, DIM, plane);
		spaceAbove(y_term-DIM);
		displayPlaneXAxe(x, x_term, 0, y_term-y, plane);
	} else {
		spaceAbove(y);
		displayPlaneXAxe(x, x_term, 0, DIM, plane);
		spaceAbove(y_term-DIM-y);
	}
}
