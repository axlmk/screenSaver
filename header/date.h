#ifndef _DATE_H_
#define _DATE_H_
#define NUM_ELT_REF_ARR 11
#define LENGHT 5
#define WIDTH 3

struct tm *datetime();
char **makeKBigger(char **arr, int k);
char ***numberPbm(int k);
char **createDateArray(struct tm *actualTime, char ***referenceArray, int k);

#endif
