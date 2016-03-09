#include "listedble.h"


typedef void * cellType;

typedef struct CD {
	cellType *cellRef; // pointeur sur la cellule ou stocker la donn�e
	const char *format; // format de cellule
} CellDescriptor;

typedef struct FD {
	
	CellDescriptor *columns; // liste des descripteur de colonnes
	const char *separator; // format de la ligne
	refObjet *refObject;
	int maxItems;
} FileLineDescriptor;

/* Lit le fichier pass� en param�tre ligne par ligne et stock le r�sultat dans une liste*/
void readFile(const char *pFilePath, idListe pObject, FileLineDescriptor **pColumnDescriptor, void(*insertVoid) (idListe, refObjet));

/* exporter la liste vers un nouveau fichier */
void ecrireFichier(const char *pOutputFile, idListe pObject, FileLineDescriptor **pColumnDescriptor);