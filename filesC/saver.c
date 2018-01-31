#include <stdlib.h>
#include "../header/stat.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

typedef enum screenType screenType;
enum screenType {
	STATIC = 1,
	DYNAMIC = 2,
	INTERACTIVE = 3
};

void history(screenType Type) {
	time_t *temps;
	time(temps);
	struct tm *t;
	t = localtime(temps);
	FILE *f = fopen("../stat/logs.txt", "r+");
	if (f==NULL) {
		fprintf(stderr, "Une erreur est survenue lors de l'ouverture du fichier <logs>.\n");
	} else {
		fseek(f, 0, SEEK_END);
		fprintf(f, "%d/%d/%d %d:%d:%d;%d;%s\n", t->tm_mday, t->tm_mon, (t->tm_year+1900), t->tm_hour, t->tm_min, t->tm_sec, Type, "qsdf");
	}
}
void execProcess(screenType Type) {
	pid_t child_pid;
	child_pid = fork();
	if (child_pid==0) {
		history(Type);//ecrire fichier
	} else {
		char *envPath = malloc(sizeof(char)*(strlen(getenv("EXIASAVER_HOME"))));
		strcpy(envPath, getenv("EXIASAVER_HOME"));
		if (Type == STATIC) {
			envPath = realloc(envPath, sizeof(char)*(strlen(envPath)+strlen("static")));
			strcat(envPath, "static");
//			char *envPathPbm = malloc(sizeof(char)*(strlen(getenv("$EXIASAVER1_PBM"))));
//			strcpy(envPathPbm, "$EXIASAVER1_PBM"); 
//			strcat(envPathPbm, "img1.txt"); // random file
			execl(envPath,  "", NULL);
		} else if (Type == DYNAMIC) {
			strcat(envPath, "/dynamic");
			execl(envPath,"", NULL);
		} else if (Type == INTERACTIVE) {
			char *x = malloc(sizeof(char));
			char *y = malloc(sizeof(char));
			strcat(envPath, "/interactive");
			execl(envPath, x, y, NULL);
		} else {
			fprintf(stderr, "Erreur, le type choisie n'existe pas.\n");
		}
		fprintf(stderr, "Une erreur est survenue lors de l'execution du nouveau processus.Pid : %d\n", child_pid);
	}
}

int main (int argc, char *argv[]) {
	system("clear");
	if (argc == 2) {
		if(!strcmp(argv[1], "-stat")) {
			FILE *logs = fopen("logs.txt", "r");
			while (fgetc(logs)!=EOF) {
				fseek(logs, -1, SEEK_CUR);
				printf("%c", fgetc(logs));
			}
			fclose(logs);
			return EXIT_SUCCESS;
		} else if(!strcmp(argv[1], "--help")) {
			printf("Les options disponibles sont :\n");
			printf("-stat	Affiche les statistiques d'utilisation du saver.\n");
		} else {
			fprintf(stderr, "L'option choisie n'existe pas, tapez <--help> pour voir les options disponibles.\n");
			return EXIT_FAILURE;
		}
	} else if (argc == 1) {
		srand(time(NULL));
		int r=rand()%3+1;
		int i=0;
		r = 1;
		if (r==1) {
			execProcess(STATIC);
		} else if (r==2) {
			execProcess(DYNAMIC);
		} else if (r==3) {
			execProcess(INTERACTIVE);
		} else {
			fprintf(stderr, "Il s'est produit une erreur lors du chargement de <r>.\n");
			return EXIT_FAILURE;
		}
	} else {
		fprintf(stderr, "Le nombre d'arguments est incorrect. Il ne peut y avoir qu'un seul argument fournit.\n");
		return EXIT_FAILURE;
	}
	return 0;
}
