#include "../header/stat.h"

int checkLines(FILE *f) {
	int i=0;
	while(fgetc(f)!=EOF) {
		fseek(f, -1, SEEK_CUR);
		if (fgetc(f)==*"#") {
			while(fgetc(f)!=*"\n");
		} else {
			while(fgetc(f)!=*"\n");
		}
	}
	fseek(f, 0, SEEK_SET);
	return i;
}

int nbrMax(FILE *f) {
	int i=0, j=0, max=0;
	while(fgetc(f)!=EOF) {
		fseek(f, -1, SEEK_CUR);
		if (fgetc(f)==*"#") {
			while(fgetc(f)!=*"\n");
		} else {
			while(fgetc(f)!=*"\n") {
				j++;
			}
			if(j>max) {
				max=j;
			}
		}
	}
	fseek(f, 0, SEEK_SET);
	return j;
}

/*char **initArray(const char *c) {
	FILE *f = fopen(c, "r");
	if (f==NULL) {
		fprintf(stderr, "Erraeur lors de l'ouverture du fichier.\n");
		fclose(f);
		return NULL;
	} else {
		int i=0, j=0;
		char **arr = malloc(sizeof(char*)*checkLines(f));
		for(i=0;i<checkLines(f); i++) {
			arr[i]= malloc(sizeof(char)*nbrMax(f));
			memset(arr[i], 0, nbrMax(f));
		}
		i=0;
		while (fgetc(f)!=EOF) {
			fseek(f, -1, SEEK_CUR);
			if (fgetc(f)==*"#") {
				while(fgetc(f)!=*"\n");
				i--;
			} else {
				fseek(f, -1, SEEK_CUR);
				j=0;
				while (fgetc(f)!=*"\n") {
					fseek(f, -1, SEEK_CUR);
					arr[i][j]=fgetc(f);
					j++;
				}
			}
			i++;
		}
		fclose(f);
		return arr;
	}
}*/

void launchStat() {
	printf("Ceci est le menu statistique.\n");
	int quit=1;
	do {
		printf("\nComment souhaitez-vous acceder aux informations ?\n");
		printf("1 - Tris des dates\n2 - Statistiques du nombres d'ecrans lances\n");
		printf("3 - Statistiques des paramètre d'un ecran specifique\n4 - Quitter\n");
		int type=0;
		const char path[17] = "../stat/logs.txt";
		scanf("%d", &type); //a sécuriser
		if (type==1) {
			FILE *f = fopen(path, "r");
			if(f == NULL) {
					printf(stderr, "Une erreur lors de l'ouverture du fichier est survenue <log>.\n");
			} else {
				while(fgetc(f)!=EOF) {
					fseek(f, -1, SEEK_CUR);
					if(fgetc(f)==*"#")
						while(fgetc(f)!=*"\n");
					else {

					}
				}
			}
		} else if (type==2) {
			FILE *f = fopen(path, "r");
			if (f==NULL) {
				fprintf(stderr, "Erreur lors de l'ouverture du fichier\n");
			} else {
				int saver=0, saver1=0, saver2=0, saver3=0;
				while(fgetc(f)!=EOF) {
					fseek(f, -1, SEEK_CUR);
					if (fgetc(f)==*"#") {
						while(fgetc(f)!=*"\n");
					}
					while(fgetc(f)!=*";");
					saver=fgetc(f);
					if (saver==*"1") {
						saver1++;
					} else if (saver==*"2") {
						saver2++;
					} else if (saver==*"3") {
						saver3++;
					} else {
						fprintf(stderr, "Erreur lors de la detection du type\n");
					}
					while(fgetc(f)!=*"\n");
				}
				printf("%d ecrans statiques ont ete lances.\n", saver1);
				printf("%d ecrans dynamiques ont ete lances.\n", saver2);
				printf("%d ecrans interactifs ont ete lances.\n", saver3);
			}
			quit=0;
		} else if (type==3) {
			printf("yolo paramtres");
		} else if (type==4) {
			printf("Vous quittez le menu stat.\n");
			quit=0;
		} else {
			printf("Le caractere saisie n'est pas valide.\n");
		}
	} while (quit!=0);
}
