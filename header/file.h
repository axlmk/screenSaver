#ifndef _FILE_H_
#define _FILE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

char *createString(FILE *f, int N);
char *takeOffData(char *array, int N);
char *getDataPbm(char *array, char *magicNumber, int *width, int *lenght);
int lenFile(FILE *f);
char *takeOffCarriage(char *array);
char *takeOffSpace(char *array);
char **stoarr(char *array, int width, int lenght);
char *takeOffSharp(char *array); //si # a la derniere ligne on a un \n en trop car il va garder le dernier \n "enregistré"

#endif