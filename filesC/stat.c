#include "../header/stat.h"

void launchStat() {
	printf("Ceci est le menu statistique.\n");
	int quit=1;
	do {
		printf("\nComment souhaitez-vous acceder aux informations ?\n");
		printf("1 - Tris par date\n2 - Statistiques du nombres d'ecrans lances\n");
		printf("3 - Statistiques des paramètres d'un ecran specifique\n4 - Quitter\n");
		int type=0;
		const char path[17] = "../stat/logs.txt";
		scanf("%d", &type); //a sécuriser
		system("clear");
		if (type==1) {
			FILE *f = fopen(path, "r");
			if(f == NULL) {
					fprintf(stderr, "Une erreur lors de l'ouverture du fichier est survenue <log>.\n");
			} else {
				fseek(f, 0, SEEK_SET);
				while(fgetc(f)!=EOF) {
					fseek(f, -1, SEEK_CUR);
					if(fgetc(f)=='#') {
						fseek(f, -1, SEEK_CUR);
						while(fgetc(f)!='\n');
					} else {
						fseek(f, -1, SEEK_CUR);
						printf("%c", fgetc(f));
					}
				}
			}
			fclose(f);
			quit = 0;
		} else if (type==2) {
			FILE *f = fopen(path, "r");
			if (f==NULL) {
				fprintf(stderr, "Erreur lors de l'ouverture du fichier\n");
			} else {
				int saver=0, saver1=0, saver2=0, saver3=0;
				while(fgetc(f)!=EOF) {
					fseek(f, -1, SEEK_CUR);
					if (fgetc(f)=='#') {
						fseek(f, -1, SEEK_CUR);
						while(fgetc(f)!='\n');
					} else {
						fseek(f, -1, SEEK_CUR);
						while(fgetc(f)!=';');
						saver=fgetc(f);
						if (saver=='1') {
							saver1++;
						} else if (saver=='2') {
							saver2++;
						} else if (saver=='3') {
							saver3++;
						} else {
							fprintf(stderr, "Erreur lors de la detection du type %c\n", saver);
						}
						while(fgetc(f)!='\n');
					}
				}
				printf("%d ecrans statiques ont ete lances.\n", saver1);
				printf("%d ecrans dynamiques ont ete lances.\n", saver2);
				printf("%d ecrans interactifs ont ete lances.\n", saver3);
			}
			fclose(f);
			quit=0;
		} else if (type==3) {
			FILE *f = fopen(path, "r");
			if (f==NULL) {
				fprintf(stderr, "Erreur lors de l'ouverture du fichier\n");
			} else {
				char c = '0';
				printf("Veuillez saisir le nombre de l'ecran dont vous voulez obtenir les parametres :\n");
				scanf("%c", &c); //oui c'est degueu mais j'ai la flemme de vider le tempon
				scanf("%c", &c);
				while(fgetc(f)!=EOF) {
					fseek(f, -1, SEEK_CUR);
					if (fgetc(f)=='#') {
						fseek(f, -1, SEEK_CUR);
						while(fgetc(f)!='\n');
					} else {
						fseek(f, -1, SEEK_CUR);
						while(fgetc(f)!=';');
						if (fgetc(f)==c) {
							char buff[64]; memset(buff, 0, 64);
							int u = 0;
							while(fgetc(f)!='\"');
							while(fgetc(f)!='\"') {
								fseek(f, -1, SEEK_CUR);
								buff[u] = fgetc(f);
								u++;
							} printf("%s\n", buff);
						}
						while(fgetc(f)!='\n');
					}
				}
			}
			fclose(f);
			quit=0;
		} else if (type==4) {
			printf("Vous quittez le menu stat.\n");
			quit=0;
		} else {
			printf("Le caractere saisie n'est pas valide.\n");
		}
	} while (quit!=0);
}
