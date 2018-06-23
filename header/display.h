#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <stdio.h>
#include <stdlib.h>
#define DIM 6

void printStringPlane(char *string, int n, int len);
void spaceAbove(int y);
void spaceLeft(int x);
void displayPlaneXAxe(int x, int x_term, int n, int k, char **plane);
void displayPlane(int x, int y, int x_term, int y_term, char **plane);

#endif
