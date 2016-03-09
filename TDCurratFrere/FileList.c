/*********************************************************************/
/* TDCurratFrere mars 2016                                           */
/* Auteur : Benjamin Currat                                          */
/* Date : mars 2016                                                  */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FileList.h"
#define LGL 255


/* Lit le fichier passé en paramêtre ligne par ligne et stock le résultat
dans les pointeurs du descripteur de ligne*/
void readFile(const char *pFilePath, idListe pObject, 
	FileLineDescriptor **pColumnDescriptor, void (*insertVoid) (idListe, refObjet))
{
	int i, c, colSize, line=0, column;
	FILE *file;
	file = fopen(pFilePath, "r");
	char *currentLine = malloc(LGL*sizeof(char*));
	char *token;
//	bool error = false;

	// voir strtok => separaration des formats
	//int columnsCount = sizeof(pColumnDescriptor) / sizeof(FileLineDescriptor);
	
	if (file) {
		fgets(currentLine, LGL, file);
		while (!feof(file) /*&& !error*/) {
			column = 0;
			token = strtok(currentLine, pColumnDescriptor[line]->separator);
			while (NULL != token){
				// scanner le résultat du token et le stocker dans le pointeur associé	
				sscanf(token, pColumnDescriptor[line]->columns[column].format,
					pColumnDescriptor[line]->columns[column].cellRef);
				column++;
				token = strtok(NULL, pColumnDescriptor[line]->separator);
			}

			// insertion dans la liste
			insertVoid(pObject, pColumnDescriptor[line]->refObject);

			// ligne suivante
			fgets(currentLine, LGL, file);
			line++;
		}
		// libérer la ligne courrante
		free(currentLine);

		fclose(file);
	}
}


/* exporter la liste vers un nouveau fichier */
void ecrireFichier(const char *pOutputFile, idListe pListe, 
	FileLineDescriptor **pColumnDescriptor)
{
	FILE *file;
	idElt item = premierElt(pListe);
	int line = 0, column = 0;
	char *currentLine = malloc(LGL*sizeof(char*));

	file = fopen(pOutputFile, "w");

	if (file){
		while (item){
			
			for (column = 0; column < pColumnDescriptor[line]->nbColumns; column++){
				strcat(currentLine,pColumnDescriptor[line]->columns[column].cellRef);
				strcat(currentLine, pColumnDescriptor[line]->separator);
			}
			// ligne suivante
			fprintf(file, "%s\n", currentLine);
			line++;
		}
	}

	free(currentLine);
	fclose(file);

}