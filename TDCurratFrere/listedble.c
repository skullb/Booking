/* Listedble.c */
#include <stdio.h>
#include <stdlib.h>

typedef void * typeObjet;

/* Définition d'un élément de la liste */
typedef struct elt {
    typeObjet RefObjet;          // rŽfŽrence de l'objet
    struct elt *suivant;         // Pointeur sur l'élément suivant
    struct elt *precedent;       // Pointeur sur l'élément précédenments
}  typeElt;

/* DŽfinition d'un descripteur de liste */
typedef struct LH {     // LH comme Liste Header
    int         nbElt;           // nombre d'ŽlŽments
    typeElt * premier;  // pointeur sur le premier ŽlŽment de la liste
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

/* Creer un nouvel élément sans l'insérer dans la liste */
typeElt *creerElt (void * pObjet) {
	typeElt *nouveau;

	/* Allocation de la mémoire pour le nouvel élément */
	nouveau = (typeElt *) malloc (sizeof (typeElt));
	if (nouveau != NULL) {
		nouveau->RefObjet = pObjet;
		nouveau->suivant = nouveau; // le nouvel ŽlŽment pointe sur lui-mme
		nouveau->precedent = nouveau; // le nouvel ŽlŽment pointe sur lui-mme
	}
	return nouveau;
}

void detruireElt(typeElt *pElt){

    free(pElt);
}

/* Donne la valeur de l'élément courant */
void * valElt (typeElt *courant) {
	return courant->RefObjet;
}

/* Donne le pointeur sur l'élément suivant */
typeElt *suivantElt (typeElt *courant) {
	return courant->suivant;
}

/* Donne le pointeur sur l'élément précédent */
typeElt *precedentElt (typeElt *courant) {
	return courant->precedent;
}

/* Insre l'ŽlŽment nouveau dans la liste aprs le courant */
// Insre en premier quand courant == NULL
void insereElt (typeListe *ptListe, typeElt *courant, typeElt *nouveau) {
    
    ptListe->nbElt++;
    
    if (ptListe->premier != NULL) {
        // la liste n'est pas vide
        if (courant == NULL) {
            //on insere au dŽbut de la liste
            ptListe->premier=nouveau;
            courant=ptListe->dernier; // on insre ˆ la suite du dernier
        } else {
            // on insere aprs le courant, on traite le cas particulier de la fin de liste
            if (courant == ptListe->dernier)
                ptListe->dernier=nouveau;
        }
    } else {
        // la liste est vide
        courant = nouveau;
        ptListe->premier=nouveau;
        ptListe->dernier=nouveau;
    }

    // on insŽre le nouvel ŽlŽment ˆ la suite du courant
    nouveau->precedent = courant;
    nouveau->suivant = courant->suivant;
    (courant->suivant)->precedent = nouveau;
    courant->suivant = nouveau;
    
}

/* Enlever l'ŽlŽment courant de la liste passŽe en paramtre */
/* Enlever le 1er si courant = 1er de la liste */
void enleverElt (typeListe *ptListe, typeElt *courant) {
    // on suppose ici  que l'on n'appelle cette fonction
    // que s'il existe au minimum un ŽlŽment dans la liste

    ptListe->nbElt--;

    // il faut traiter le cas particulier ou on enlve le dernier ŽlŽment
    // de la liste
    if (courant == ptListe->premier && courant == ptListe->dernier) {
        // c'est le denier ŽlŽment
        ptListe->premier = NULL;
        ptListe->dernier = NULL;
    } else {
        // il y a au moins deux ŽlŽments, on traite les cas ou
        // on supprime le premier ou le dernier ŽlŽment
        if (courant == ptListe->premier) {
            ptListe->premier=courant->suivant;
        }
        if (courant == ptListe->dernier) {
            ptListe->dernier=courant->precedent;
        }
        // on reforme la chaine dans les deux sens une fois l'ŽlŽment supprimŽ
        (courant->precedent)->suivant = courant->suivant;
        (courant->suivant)->precedent = courant->precedent;
    }
    
    // on rŽ-initialise l'ŽlŽment enlevŽ pour pointer sur lui-mme
    courant->precedent = courant;
    courant->suivant = courant;
}

/* renvoient les premier et dernier ŽlŽments de la liste */

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
    while (ptListe->premier != NULL) {  // Tant qu'il reste un ŽlŽment
        enleverElt (ptListe, ptListe->premier); // Detruire le premier
    }
    free(ptListe);
}


