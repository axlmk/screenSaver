#include "../header/shifting.h"

int convert_x(int x, int x_term) {
	if(x < 0) {
		return x_term-1;
	} else if(x >= x_term) {
		return 0;
	} else {
		return x;
	}
}

int convert_y(int y, int y_term) {
	if(y < 0) {
		return y_term-1;
	} else if(y >= (y_term)) {
		return 0;
	} else {
		return y;
	}
}

char keyFromFrame(int planeFrame) {
	switch (planeFrame) {
		case 0:
			return 'd';
		break;
		case 1:
			return 's';
		break;
		case 2:
			return 'q';
		break;
		case 3:
			return 'z';
		break;
		default:
			return 'l';

	}
}

int moving(char key, int *x, int *y, int *planeFrame) {
	int end = 1;
	if(key == 'z') {
		*y-=1;
		*planeFrame = 3;
	} else if(key == 'q') {
		*x-=1;
		*planeFrame = 2;
	} else if(key == 'd') {
		*x+=1;
		*planeFrame = 0;
	} else if(key == 's') {
		*y+=1;
		*planeFrame = 1;
	} else if(key == 'l') {
		end = 0;
	} else {
		end = moving(keyFromFrame(*planeFrame), x, y, planeFrame);
	}
	return end;
}
