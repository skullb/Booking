#include "Util.h"

int saisieIntAvecArguments(char *QuestionDeSaisie, char *textErreur, int taille)
{

	int valeur, n;
	char *ligne;
	ligne = (char*)malloc(taille*sizeof(char));

	if (ligne != NULL)
	{
		printf("%s", QuestionDeSaisie);
		fgets(ligne, taille, stdin);
		n = sscanf(ligne, "%d", &valeur);
		while (n != 1) { // Tant que la saisie n'est pas une valeur numérique
			printf("%s", textErreur);
			fgets(ligne, taille, stdin);
			n = sscanf(ligne, "%d", &valeur);
		}
	}
	free(ligne);

	return valeur;
}






