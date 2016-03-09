#include "Util.h"
#define TEXTEMAX 100


int typeInt(char *_questionDeSaisie, char *_textErreur, int _taille)
{
	int valeur, n;
	char *ligne;
	ligne = (char*)malloc(_taille*sizeof(char));

	if (ligne != NULL)
	{
		printf("%s", _questionDeSaisie);
		fgets(ligne, _taille, stdin);
		n = sscanf(ligne, "%d", &valeur);
		while (n != 1) { // Tant que la saisie n'est pas une valeur numérique
			printf("%s", _textErreur);
			fgets(ligne, _taille, stdin);
			n = sscanf(ligne, "%d", &valeur);
		}
	}
	free(ligne);

	return valeur;
}

char *typeText(char *_questionDeSaisie, char *_textErreur) {
	char ligne[TEXTEMAX];
	char *nom;
	printf("%s", _questionDeSaisie);
	fgets(ligne, TEXTEMAX, stdin);         // Saisie d'une ligne au clavier
	while (strlen(ligne) <= 2) {
		printf("%s", _textErreur);
		fgets(ligne, TEXTEMAX, stdin);
	}
	ligne[strlen(ligne) - 1] = '\0'; // enlever \n
	nom = (char *)malloc(strlen(ligne) + 1); // allouer la mémoire nécessaire
	strcpy(nom, ligne); // Recopier le nom dans cette mémoire
	return nom;
}