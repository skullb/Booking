/*********************************************************************/
/* TDCurratFrere mars 2016                                           */
/* Auteur : Benjamin Currat                                          */
/* Date : mars 2016                                                  */
/*********************************************************************/

#include "listedble.h"
#include "FileList.h"
#include "Util.h"
#include <stdio.h>
#include <stdlib.h>

#define SOURCE_FILE_PATH "swissliste.txt"
#define EXPORT_FILE_PATH "swissliste2.txt"
#define DB_SIZE 100


typedef struct {
	char    *nom;		// nom du client
	char    *prenom;		// prénom du client
	int     miles;			//Miles parcourus pendant l'année
	int     ordreArrivee;	//Ordre d'arrivé du client
	int		priorite;		//Priorité pour les vols
	int		anneesFidelite;	//Nombre d'année de fidélité
} client;

/*initialisation des structures de clients avec la description de ligne du fichier*/
void initModel(FileLineDescriptor **pDescriptors, client **pCLients){
	int i;

	
	
		
	for (i = 0; i < DB_SIZE; i++) {

		pCLients[i] = (client *)malloc(sizeof(client));
		pDescriptors[i] = (FileLineDescriptor *)malloc(sizeof(FileLineDescriptor));

		// initialisation d'un client vide
		//pCLients[i] = {NULL, NULL, 0,0,0,0}
		pCLients[i]->nom = malloc(30*sizeof(char));
		pCLients[i]->prenom = malloc(30 * sizeof(char));
		pCLients[i]->miles = 0;
		pCLients[i]->priorite = 0;
		pCLients[i]->ordreArrivee = 0;
		pCLients[i]->anneesFidelite = 0;

		// descripteur de champs du fichier
		pDescriptors[i]->refObject = &pCLients[i];
		pDescriptors[i]->separator = "\t";
		pDescriptors[i]->columns = malloc(5 * sizeof(CellDescriptor));
		pDescriptors[i]->columns[0].cellRef = pCLients[i]->nom;
		pDescriptors[i]->columns[0].format = "%s";
		pDescriptors[i]->columns[1].cellRef = pCLients[i]->prenom;
		pDescriptors[i]->columns[1].format = "%s";
		pDescriptors[i]->columns[2].cellRef = &pCLients[i]->miles;
		pDescriptors[i]->columns[2].format = "%d";
		pDescriptors[i]->columns[3].cellRef = &pCLients[i]->ordreArrivee;
		pDescriptors[i]->columns[3].format = "%d";
		pDescriptors[i]->columns[4].cellRef = &pCLients[i]->anneesFidelite;
		pDescriptors[i]->columns[4].format = "%d";
	}
}

void destructModel(FileLineDescriptor **pDescriptors, client **pCLients){
	int i;
	for (i = 0; i < DB_SIZE; i++) {
		free(pCLients[i]->nom);
		free(pCLients[i]->prenom);
		free(pDescriptors[i]->columns);
	}

	free(pCLients);
	free(pDescriptors);
}


void main(){

	int cmd, val, i;
	client **c = NULL;
	FileLineDescriptor **swissPassengerLineDesc =NULL;
	idListe sortedList;

	// allocation de la taille maximum de la base
	c = malloc(DB_SIZE * sizeof(client));
	// allocation de la taille maximum des descripteurs de ligne
	swissPassengerLineDesc = malloc(DB_SIZE * sizeof(FileLineDescriptor *));

	// initialisation de la db au max
	initModel(swissPassengerLineDesc, c);

	sortedList = creerListe();
	if (!sortedList) {
		printf("erreur sur initialisation de la liste... Au revoir !\n");
		exit(-1);
	};

	// lire  le fichier 
	readFile(SOURCE_FILE_PATH, swissPassengerLineDesc);

	for (i = 0; i < DB_SIZE; i++){
		if (c[i]->nom != NULL){
			printf("%s\t%s\t%d\t%d \n", c[i]->nom, c[i]->prenom, c[i]->miles,c[i]->anneesFidelite);
		}
	}

	getchar();
	destructModel(swissPassengerLineDesc, c);

	// stocker dans une liste en passant la function de priorité
	//storeInSortedList(sortedList, c, (*) isPrior()(*,*));

	//printf("Commande: ");
	//cmd = saisieInt();

	//while (cmd != 0){
	//	switch (cmd){

	//	case 1:
	//		/* cas menu 1 */
	//		printf(" => Valeur: ");

	//		break;

	//	case 2:
	//		/* cas menu 2 */

	//		break;

	//	case 3:
	//		/* cas menu 3 */

	//		break;
	//	default:
	//		printf("Commande inconnue\n");
	//		break;
	//	}

	//	printf("Commande: ");
	//	cmd = saisieInt();
}