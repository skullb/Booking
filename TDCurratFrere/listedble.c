/* Listedble.c */
#include <stdio.h>
#include <stdlib.h>

typedef void * typeObjet;

/* D�finition d'un �l�ment de la liste */
typedef struct elt {
    typeObjet RefObjet;          // r�f�rence de l'objet
    struct elt *suivant;         // Pointeur sur l'�l�ment suivant
    struct elt *precedent;       // Pointeur sur l'�l�ment pr�c�denments
}  typeElt;

/* D�finition d'un descripteur de liste */
typedef struct LH {     // LH comme Liste Header
    int         nbElt;           // nombre d'�l�ments
    typeElt * premier;  // pointeur sur le premier �l�ment de la liste
    typeElt * dernier;  // pointe sur le dernier
} typeListe;




/* Creer un descripteur de liste pour une nouvelle liste */
typeListe * creerListe () {
    typeListe * ptListe;
    
    ptListe = (typeListe *) malloc(sizeof(typeListe));
    
    if (ptListe != NULL) {
        ptListe->premier = NULL;
        ptListe->dernier = NULL;
        ptListe->nbElt = 0;
    }
    return(ptListe);
}

/* Creer un nouvel �l�ment sans l'ins�rer dans la liste */
typeElt *creerElt (void * pObjet) {
	typeElt *nouveau;

	/* Allocation de la m�moire pour le nouvel �l�ment */
	nouveau = (typeElt *) malloc (sizeof (typeElt));
	if (nouveau != NULL) {
		nouveau->RefObjet = pObjet;
		nouveau->suivant = nouveau; // le nouvel �l�ment pointe sur lui-m�me
		nouveau->precedent = nouveau; // le nouvel �l�ment pointe sur lui-m�me
	}
	return nouveau;
}

void detruireElt(typeElt *pElt){

    free(pElt);
}

/* Donne la valeur de l'�l�ment courant */
void * valElt (typeElt *courant) {
	return courant->RefObjet;
}

/* Donne le pointeur sur l'�l�ment suivant */
typeElt *suivantElt (typeElt *courant) {
	return courant->suivant;
}

/* Donne le pointeur sur l'�l�ment pr�c�dent */
typeElt *precedentElt (typeElt *courant) {
	return courant->precedent;
}

/* Ins�re l'�l�ment nouveau dans la liste apr�s le courant */
// Ins�re en premier quand courant == NULL
void insereElt (typeListe *ptListe, typeElt *courant, typeElt *nouveau) {
    
    ptListe->nbElt++;
    
    if (ptListe->premier != NULL) {
        // la liste n'est pas vide
        if (courant == NULL) {
            //on insere au d�but de la liste
            ptListe->premier=nouveau;
            courant=ptListe->dernier; // on ins�re � la suite du dernier
        } else {
            // on insere apr�s le courant, on traite le cas particulier de la fin de liste
            if (courant == ptListe->dernier)
                ptListe->dernier=nouveau;
        }
    } else {
        // la liste est vide
        courant = nouveau;
        ptListe->premier=nouveau;
        ptListe->dernier=nouveau;
    }

    // on ins�re le nouvel �l�ment � la suite du courant
    nouveau->precedent = courant;
    nouveau->suivant = courant->suivant;
    (courant->suivant)->precedent = nouveau;
    courant->suivant = nouveau;
    
}

/* Enlever l'�l�ment courant de la liste pass�e en param�tre */
/* Enlever le 1er si courant = 1er de la liste */
void enleverElt (typeListe *ptListe, typeElt *courant) {
    // on suppose ici  que l'on n'appelle cette fonction
    // que s'il existe au minimum un �l�ment dans la liste

    ptListe->nbElt--;

    // il faut traiter le cas particulier ou on enl�ve le dernier �l�ment
    // de la liste
    if (courant == ptListe->premier && courant == ptListe->dernier) {
        // c'est le denier �l�ment
        ptListe->premier = NULL;
        ptListe->dernier = NULL;
    } else {
        // il y a au moins deux �l�ments, on traite les cas ou
        // on supprime le premier ou le dernier �l�ment
        if (courant == ptListe->premier) {
            ptListe->premier=courant->suivant;
        }
        if (courant == ptListe->dernier) {
            ptListe->dernier=courant->precedent;
        }
        // on reforme la chaine dans les deux sens une fois l'�l�ment supprim�
        (courant->precedent)->suivant = courant->suivant;
        (courant->suivant)->precedent = courant->precedent;
    }
    
    // on r�-initialise l'�l�ment enlev� pour pointer sur lui-m�me
    courant->precedent = courant;
    courant->suivant = courant;
}

/* renvoient les premier et dernier �l�ments de la liste */

typeElt * premierElt(typeListe *ptListe){
    return(ptListe->premier);
}

typeElt * dernierElt(typeListe *ptListe) {
    return(ptListe->dernier);
}

int nbElements(typeListe *ptListe) {
    return(ptListe->nbElt);
}

/* Detruit la liste */
void detruireListe (typeListe *ptListe) {
    while (ptListe->premier != NULL) {  // Tant qu'il reste un �l�ment
        enleverElt (ptListe, ptListe->premier); // Detruire le premier
    }
    free(ptListe);
}


