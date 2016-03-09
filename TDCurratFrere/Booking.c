/*********************************************************************/
/*Travail personnel Alg SD IGL2
/*
/*TDCurratFrere mars 2016                                           */
/* Auteurs : Benjamin Currat et Laurent Frère
/*
/* Date : mars 2016

Thème: Liste d'attent pour prendre un vol (Surbooking)

Description de l'algorithme:


Limite de l'algorithme:
-Pas de contrôle sur la pertinence des valeurs saisie au clavier à l'insertion d'un client.
-L'ordre d'arrivée est évalué, une fois le fichier chargé

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
	char    *surname;		// nom du client
	char    *firstName;		// prénom du client
	int     miles;			//Miles parcourus pendant l'année
	int     order;			//Ordre d'arrivé du client
	int		fidelity;		//Nombre d'année de fidélité
} client;

/*
Formule de surbooking
Arguments:
	pMiles : Miles parcourus pendant l'année
	pFidelity : Nombre d'année de fidélité
	pOrder : Ordre d'arrivé du client dans la file d'attente
Retourne:
	Priorité d'un voyageur calculée(int)
*/
int calculatePriority(int pMiles, int pFidelity, int pOrder);

/*
On ajoute dans la liste des clients, un client saisie à la console.
Actions:
	-Questions à la console.
	-Défini l'ordre d'arrivée du client.
	-Ajoute le client dans la liste (l'ordonnancement se fera via la méthode d'insertion)
Argument:
	pClients : liste de clients dans lequel le client doit être ajouté.
	pOrder : ordre d'arrivée du dernier client (int).
*/
void addClientConsole(idListe pClients, int *pOrder);

/*
On insert un client dans la liste des clients suivant une méthode définie
Actions:
	-Parcours la liste pour trouver l'endroit d'insertion.
	-Ajoute l'élément.

Critères d'insertion:

Argument:
	pCLients : liste de clients dans lequel le client doit être ajouté.
	pNewCLient : Client devant être ajouté à la liste.
*/
void insertClient(idListe pClients, client *pNewClient);

/*initialisation des structures de clients avec la description de ligne du fichier*/
void initModel(FileLineDescriptor **pDescriptors, client **pCLients);

/* Destructeur de model */
void destructModel(FileLineDescriptor **pDescriptors, client **pCLients);


void main(){

	client **c = NULL;
	FileLineDescriptor **swissPassengerLineDesc = NULL;

	idListe listeClients;			//Liste chainée des informations clients
	int cmd, val, NumeroArrivee = 0;			//Numéro d'arrivée du dernier client. 
												//Initialisé à 0 pour que le premier client ajouté commence à 1


	// allocation de la taille maximum de la base
	c = malloc(DB_SIZE * sizeof(client));
	// allocation de la taille maximum des descripteurs de ligne
	swissPassengerLineDesc = malloc(DB_SIZE * sizeof(FileLineDescriptor *));

	// initialisation de la db au max
	initModel(swissPassengerLineDesc, c);

	listeClients = creerListe();
	if (!listeClients) {
		printf("erreur sur initialisation de la liste... Au revoir !\n");
		exit(-1);
	};

	// lecture du fichier et stockage dans la liste
	readFile(SOURCE_FILE_PATH, listeClients, swissPassengerLineDesc, insertClient);

	// destruction du tableau de base contentant les clients
	destructModel(swissPassengerLineDesc, c);

	printf("Commande: ");
	cmd = saisieInt();

	while (cmd != 0){
		switch (cmd){

		case 1:
			/* cas menu 1 */
			printf(" => Valeur: ");

			break;

		case 2:
			/* cas menu 2 */

			break;

		case 3:
			/* cas menu 3 */

			break;
		default:
			printf("Commande inconnue\n");
			break;
		}

		printf("Commande: ");
		cmd = saisieInt();
	}

	addClientConsole(listeClients, &NumeroArrivee);


	detruireListe(listeClients);

	
}
int calculatePriority(int pMiles, int pFidelity, int pOrder)
{
	return (pMiles / 1000) + pFidelity - pOrder;
}

void addClientConsole(idListe pClients, int *pOrder)
{
	client newClient;

	//Identifie le client par la console
	newClient.surname = typeText("Nom du client: ", "Erreur de saisie. recommencer: ");
	newClient.firstName = typeText("Pr\202nom du client: ", "Erreur de saisie. recommencer: ");
	newClient.miles = typeInt("Miles parcourus pendant l'ann\202e? ", "Erreur de saisie. Veuillez saisir des miles: ", 10);
	newClient.fidelity = typeInt("Nombre d'ann\202es d'inscription au programme de fid\202lit\202: ", "Erreur de saisie. Veuillez saisir un nombre d'ann\202es: ", 3);

	//Définie ordre d'arrivée
	(*pOrder)+=1;
	newClient.order = *pOrder;

	//Insert dans la liste(le critère d'ordonnancement est dans la méthode appelée) 
	insertClient(pClients, &newClient);
}

void insertClient(idListe pClients, client *pNewClient)
{
	int nbItems = nbElements(pClients);

	// Aucun élément dans la liste => pas d'ordonnancement
	if (nbItems< 1)
	{
		insereElt(pClients, NULL, pNewClient);
	}
	else // on trie
	{
		int priorityNewClient, priorityCurrentClient,index = 1;		//Position dans la liste surant l'analyse
		client *currentClient = (client *) premierElt(pClients); //Premièreitem

		while (index <= nbItems)
		{
			priorityNewClient = calculatePriority(pNewClient->miles, pNewClient->fidelity, pNewClient->order);
			priorityCurrentClient = calculatePriority(currentClient->miles, currentClient->fidelity, currentClient->order);

			if (priorityNewClient < priorityCurrentClient)
			{
				//Le nouveau client est moins prioritaire que le client actuellement analysé
				//Par conséquent, on analyse le prochain client sauf si ce client est le dernier de la liste
				if (index == nbElements)
				{
					//le nouveau client est ajouté en fin de liste (cas où il est le moins prioritaire
					insereElt(pClients, currentClient, pNewClient);
				}
				//On passe au client suivant de la liste
				currentClient = suivantElt(currentClient);
			}
			else
			{
				//Le nouveau client est plus prioritaire que le client actuellement analysé
				//On l'insère donc
				if (index == 1) //Cas où le premiere de la liste est moins prioritaire
				{
					insereElt(pClients, NULL, pNewClient);
				}
				else
				{
					insereElt(pClients, precedentElt(currentClient), pNewClient);
				}
				index = nbItems ++; //Pour sortir de la liste
			}
			index++;
		}

	}
}


void initModel(FileLineDescriptor **pDescriptors, client **pCLients){
	int i;
		
	for (i = 0; i < DB_SIZE; i++) {

		pCLients[i] = (client *)malloc(sizeof(client));
		pDescriptors[i] = (FileLineDescriptor *)malloc(sizeof(FileLineDescriptor));

		// initialisation d'un client vide
		//pCLients[i] = {NULL, NULL, 0,0,0,0}
		pCLients[i]->surname = malloc(30*sizeof(char));
		pCLients[i]->firstName = malloc(30 * sizeof(char));
		pCLients[i]->miles = 0;
		pCLients[i]->order = 0;
		pCLients[i]->fidelity = 0;

		// descripteur de champs du fichier
		pDescriptors[i]->refObject = &pCLients[i];
		pDescriptors[i]->separator = "\t";
		pDescriptors[i]->columns = malloc(5 * sizeof(CellDescriptor));
		pDescriptors[i]->columns[0].cellRef = pCLients[i]->firstName;
		pDescriptors[i]->columns[0].format = "%s";
		pDescriptors[i]->columns[1].cellRef = pCLients[i]->surname;
		pDescriptors[i]->columns[1].format = "%s";
		pDescriptors[i]->columns[2].cellRef = &pCLients[i]->miles;
		pDescriptors[i]->columns[2].format = "%d";
		pDescriptors[i]->columns[3].cellRef = &pCLients[i]->fidelity;
		pDescriptors[i]->columns[3].format = "%d";
		pDescriptors[i]->columns[4].cellRef = &pCLients[i]->order;
		pDescriptors[i]->columns[4].format = "%d";
	
	}
}

void destructModel(FileLineDescriptor **pDescriptors, client **pCLients){
	int i;
	for (i = 0; i < DB_SIZE; i++) {
		free(pCLients[i]->surname);
		free(pCLients[i]->firstName);
		free(pDescriptors[i]->columns);
	}

	free(pCLients);
	free(pDescriptors);
}
