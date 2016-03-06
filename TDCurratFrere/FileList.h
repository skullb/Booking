#include "listedble.h"


typedef void * cellType;

typedef struct CD {
	cellType *cellRef; // pointeur sur la cellule ou stocker la donnée
	const char *format; // format de cellule
} CellDescriptor;

typedef struct FD {
	
	CellDescriptor *columns; // liste des descripteur de colonnes
	const char *separator; // format de la ligne
	refObjet *refObject;
	int maxItems;
} FileLineDescriptor;




/* initialisation */
void initFileListReader(const int pMaxSize);

/* Lit le fichier passé en paramêtre ligne par ligne et stock le résultat dans une liste*/
void readFile(const char *pFilePath, FileLineDescriptor **pColumnDescriptor);

/* enregistrement de la ligne dans son model metier */
void storeLine(idListe pListe, CellDescriptor pColumnPointer, int (*getSortPosition)());

/* exporter la liste vers un nouveau fichier */
void ecrireFichier(const char *pOutputFile, FileLineDescriptor **pColumnDescriptor);