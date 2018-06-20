#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include "../header/stat.h"
#include <string.h>

typedef enum screenType screenType; // enum simplifiant les types d'ecrans choisis
enum screenType {
	STATIC = 1,
	DYNAMIC = 2,
	INTERACTIVE = 3
};

void write_history(screenType Type) {
	time_t *temps;
	time(temps);
	struct tm *t;
	t = localtime(temps); // créer une variable temps a utiliser pour ecrire ans le fichier
	FILE *f = fopen("../stat/logs.txt", "r+");
	if (f==NULL) {
		fprintf(stderr, "Une erreur est survenue lors de l'ouverture du fichier <logs>.\n");
	} else {
		fseek(f, 0, SEEK_END); //rajoute la date a la derniere ligne
		fprintf(f, "%d/%d/%d %d:%d:%d;%d;%s\n", t->tm_mday, t->tm_mon, (t->tm_year+1900), t->tm_hour, t->tm_min, t->tm_sec, Type, "qsdf"); //ecrit l'heure du lancement du screen
	}
	fclose(f);
}

void execProcess(screenType Type) {
	pid_t child_pid;
	child_pid = fork(); //cree un nouveau processus
	if (child_pid==0) {
		write_history(Type);
	} else {
		char *envPath = malloc(sizeof(char)*(strlen("../bin/dynamic"))); // A MODIFIER (enlever le dynamic)
		strcpy(envPath, ("../bin/"));
		if (Type == STATIC) {
			/*envPath = realloc(envPath, sizeof(char)*(strlen(envPath)+strlen("static")));
			strcat(envPath, "static");
			char *envPathPbm = malloc(sizeof(char)*(strlen("../pbm/")));
			strcpy(envPathPbm, "../pbm/");
			envPathPbm = realloc(envPathPbm, sizeof(char)*(strlen(envPathPbm)+strlen("img1.txt"))); // random file
			strcat(envPathPbm, "img1.txt");*/
			execl("static", "../pbm/img1.pbm", NULL);
		} else if (Type == DYNAMIC) {
			//strcat(envPath, "dynamic");
			execl("dynamic", NULL);
		} else if (Type == INTERACTIVE) {
			//strcat(envPath, "/interactive");
			execl("interactive", "10", "10", NULL);
		} else {
			fprintf(stderr, "Erreur, le type choisie n'existe pas.\n");
		}
		fprintf(stderr, "Une erreur est survenue lors de l'execution du nouveau processus. Pid : %d\n", child_pid);
	}
}

int main (int argc, char *argv[]) {
	if (argc == 2) { //verifie s'il y a des options lors l'ouverture du fichier
		if(!strcmp(argv[1], "-stat")) { //le truc qui manque c'est ici qui faut le mettre bisous
			FILE *logs = fopen("logs.txt", "r");
			while (fgetc(logs)!=EOF) {
				fseek(logs, -1, SEEK_CUR);
				printf("%c", fgetc(logs));
			}
			fclose(logs);
			return EXIT_SUCCESS;
		} else if(!strcmp(argv[1], "--help")) { //donne les options disponibles
			printf("Les options disponibles sont :\n");
			printf("-stat	Affiche les statistiques d'utilisation du saver.\n");
		} else { //gerer l'erreur
			fprintf(stderr, "L'option choisie n'existe pas, tapez <--help> pour voir les options disponibles.\n");
			return EXIT_FAILURE;
		}
	} else if (argc == 1) { // lance les screensavers
		srand(time(NULL));
		int r=rand()%2+1;
		scanf("%d", &r);
		//r = 3; // r prends une variable aléatoire qui va servir a choisir le screen
		if (r==1) {
			execProcess(STATIC);
		} else if (r==2) {
			execProcess(DYNAMIC);
		} else if (r==3) {
			execProcess(INTERACTIVE);
		} else { //gere l'erreur
			fprintf(stderr, "Il s'est produit une erreur lors du chargement de <r>.\n");
			return EXIT_FAILURE;
		}
	} else { // gere l'erreur
		fprintf(stderr, "Le nombre d'arguments est incorrect. Il ne peut y avoir qu'un seul argument fournit.\n");
		return EXIT_FAILURE;
	}
	return 0;
}
