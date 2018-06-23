#ifndef _SHIFTING_H_
#define _SHIFTING_H_

int convert_x(int x, int x_term);
int convert_y(int y, int y_term);
char keyFromFrame(int planeFrame);
int moving(char key, int *x, int *y, int *planeFrame);

#endif
