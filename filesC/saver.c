#include <sys/types.h>
#include "../header/stat.h"
#include "../header/file.h"
#include <dirent.h>

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
		perror("Une erreur est survenue lors de l'ouverture du fichier <logs>");
	} else {
		fseek(f, 0, SEEK_END); //rajoute la date a la derniere ligne
		fprintf(f, "%d/%d/%d %d:%d:%d;%d;%s\n", t->tm_mday, t->tm_mon, (t->tm_year+1900), t->tm_hour, t->tm_min, t->tm_sec, Type, "qsdf"); //ecrit l'heure du lancement du screen
	}
	fclose(f);
}

int directoryCount(char *path) {
	DIR *dir;
	struct dirent *ent;
	int n=0;
	if ((dir = opendir (path)) != NULL) {
	  while ((ent = readdir (dir)) != NULL) {
		  n++;
	  }
	  closedir (dir);
	} else {
	  perror ("Une erreur est survenue lors de l'ouverture du repertoire");
  } return n-2;
}

int randum(int n) {
	srand(time(NULL));
	return rand()%n;
}

void execProcess(screenType Type) {
	pid_t child_pid;
	child_pid = fork(); //cree un nouveau processus
	if (child_pid==0) {
		write_history(Type);
	} else {
		if (Type == STATIC) {
			char path[64]; path[0] = '\0';
			strcpy(path, "../pbm/img/");
			int n = directoryCount(path);
			int r = randum(n)+1;
			path[0] = '\0';
			sprintf(path, "../pbm/img/%d.pbm", r);
			execl("../bin/static", path, NULL);
		} else if (Type == DYNAMIC) {
			execl("../bin/dynamic", NULL);
		} else if (Type == INTERACTIVE) {
			execl("../bin/interactive", "10", "10", NULL);
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
		int r = randum(3);
		r = 1;
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
