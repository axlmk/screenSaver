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

void write_history(screenType Type, char *parameters) {
	time_t temps;
	struct tm *t;
	time(&temps);
	t = localtime(&temps); // créer une variable temps a utiliser pour ecrire ans le fichier
	FILE *f = fopen("../stat/logs.txt", "r+");
	if (f==NULL) {
		perror("Une erreur est survenue lors de l'ouverture du fichier <logs>");
	} else {
		fseek(f, 0, SEEK_END); //rajoute la date a la derniere ligne
		fprintf(f, "%d/%d/%d %d:%d:%d;%d;\"%s\"\n", t->tm_mday, t->tm_mon, (t->tm_year+1900), t->tm_hour, t->tm_min, t->tm_sec, Type, parameters); //ecrit l'heure du lancement du screen
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
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if(Type == STATIC) {
		char path[64]; path[0] = '\0';
		strcpy(path, "../pbm/img/");
		int n = directoryCount(path);
		int r = randum(n)+1;
		path[0] = '\0';
		sprintf(path, "../pbm/img/%d.pbm", r);
		if(child_pid == 0) {
			write_history(Type, path);
		} else {
			execl("../bin/static", path, NULL);
		}
	} else if(Type == DYNAMIC) {
		int k = randum(12);
		char c_k[4]; memset(c_k, 0, 4);
		sprintf(c_k, "%d", k);
		if(child_pid == 0) {
			write_history(Type, c_k);
		} else {
			execl("../bin/dynamic", c_k, NULL);
		}
	} else if(Type == INTERACTIVE) {
		int x = randum(w.ws_row);
		int y = randum(w.ws_col);
		char x_c[4]; memset(x_c, 0, 4);
		char y_c[4]; memset(y_c, 0, 4);
		sprintf(x_c, "%d", x);
		sprintf(y_c, "%d", y);
		if(child_pid == 0) {
			char param[8]; memset(param, 0, 8);
			sprintf(param, "%dx%d", x, y);
			write_history(Type, param);
		} else {
			execl("../bin/interactive", x_c, y_c, NULL);
		}
	}
}

int main (int argc, char *argv[]) {
	if (argc == 2) { //verifie s'il y a des options lors l'ouverture du fichier
		if(!strcmp(argv[1], "-stat")) { //le truc qui manque c'est ici qui faut le mettre bisous
			launchStat();
			return EXIT_SUCCESS;
		} else if(!strcmp(argv[1], "--help")) { //donne les options disponibles
			printf("Les options disponibles sont :\n");
			printf("-stat	Affiche les statistiques d'utilisation du saver.\n");
			return 0;
		} else { //gerer l'erreur
			fprintf(stderr, "L'option choisie n'existe pas, tapez <--help> pour voir les options disponibles.\n");
			return EXIT_FAILURE;
		}
	} else if (argc == 1) { // lance les screensavers
		int r = randum(3)+1;
		//r = 1;
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
