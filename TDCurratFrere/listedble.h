// Listedble.h
/* Type d'un element */

//#ifndef bool
//typedef enum { false, true } bool;
//#endif

typedef int *   idListe;    // identifiant de liste
typedef int *   idElt;      // identifiant d'lment dans une liste
typedef void *  refObjet;   // rfrence d'un objet dans un lment

/* Initialise la liste ; renvoie un identifiant de liste */
idListe creerListe ();

/* Detruit la liste passe en paramtre */
void detruireListe (idListe id);

/* Assigner un lment de liste ˆ un objet mtier sans l'insrer dans une liste */
idElt creerElt (refObjet val);

/* Dtruire l'lment pass en paramtre*/
void detruireElt (idElt id);

/* Renvoit l'identifiant de l'objet correspondant ˆ l'lment pass en paramtre */
refObjet valElt (idElt id);

/* Insre l'lment nouveau dans la liste aprs le courant */
// Insre en premier quand courant == NULL
void insereElt (idListe id, idElt courant, idElt nouveau);

/* Enlever l'lment courant de la liste*/
void enleverElt (idListe id, idElt courant);

/* Fonctions renvoyant l'identifiant de l'lment suivant ou prcdent */
idElt suivantElt (idElt id);
idElt precedentElt (idElt id);

/* fonctions renvoyant le premier et le dernier lment d'une liste chaine */
idElt premierElt(idListe id);
idElt dernierElt(idListe id);

int nbElements(idListe id);
