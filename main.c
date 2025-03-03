#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_NOM 50

/*--------------------------------------------
  STRUCTURE DE DONNEES
--------------------------------------------*/
typedef struct Personne {
  char nom[TAILLE_NOM];
  int age;
  struct Personne *enfant; // Pointeur vers le premier enfant
  struct Personne *frere;  // Pointeur vers le frère/soeur suivant(e)
} Personne;

/*--------------------------------------------
  FONCTIONS DE BASE
--------------------------------------------*/

/**
 * Crée une nouvelle personne (allocation dynamique).
 */
Personne *creerPersonne(const char *nom, int age) {
  Personne *nouvelle = (Personne *)malloc(sizeof(Personne));
  if (!nouvelle) {
    printf("Erreur d'allocation memoire.\n");
    exit(EXIT_FAILURE);
  }
  strncpy(nouvelle->nom, nom, TAILLE_NOM - 1);
  nouvelle->nom[TAILLE_NOM - 1] = '\0'; // Securite
  nouvelle->age = age;
  nouvelle->enfant = NULL;
  nouvelle->frere = NULL;
  return nouvelle;
}

/**
 * Recherche une personne par son nom dans l'arbre (ou foret).
 * Parcours en profondeur (enfant puis frere).
 * Retourne un pointeur vers la personne si trouvee, sinon NULL.
 */
Personne *rechercherPersonne(Personne *racine, const char *nom) {
  if (racine == NULL) {
    return NULL;
  }
  if (strcmp(racine->nom, nom) == 0) {
    return racine;
  }
  // Chercher dans les enfants
  Personne *trouveEnfant = rechercherPersonne(racine->enfant, nom);
  if (trouveEnfant != NULL) {
    return trouveEnfant;
  }
  // Chercher dans les freres/soeurs
  return rechercherPersonne(racine->frere, nom);
}

/**
 * Ajoute un enfant a un parent existant.
 * L'enfant est insere en tete de la liste d'enfants.
 */
void ajouterEnfant(Personne *parent, Personne *enfant) {
  if (!parent || !enfant)
    return;
  // L'enfant actuel du parent devient le frere/soeur du nouvel enfant
  enfant->frere = parent->enfant;
  parent->enfant = enfant;
}

/**
 * Ajoute un frere/soeur a une personne existante.
 * Le nouveau frere/soeur est insere juste apres la personne cible.
 */
void ajouterFrere(Personne *personne, Personne *frereSoeur) {
  if (!personne || !frereSoeur)
    return;
  frereSoeur->frere = personne->frere;
  personne->frere = frereSoeur;
}

/*--------------------------------------------
  FONCTION D'AFFICHAGE DE L'ARBRE
--------------------------------------------*/

/**
 * Affiche l'arbre genealogique a partir d'une racine.
 * 'niveau' gere l'indentation.
 */
void afficherArbre(Personne *racine, int niveau) {
  if (racine == NULL)
    return;

  // Indentation : par exemple 4 points par niveau
  for (int i = 0; i < niveau; i++) {
    printf("....");
  }
  printf("%s, %d\n", racine->nom, racine->age);

  // Afficher les enfants (niveau + 1)
  afficherArbre(racine->enfant, niveau + 1);

  // Afficher le frere/soeur (meme niveau)
  afficherArbre(racine->frere, niveau);
}

/*--------------------------------------------
  FONCTIONS UTILES POUR TRI ET AFFICHAGE
  DES ENFANTS OU FRERES PAR AGE DECROISSANT
--------------------------------------------*/

/**
 * Compte le nombre d'elements dans une liste
 * chainee simple (enfants ou freres).
 */
int compterElementsListe(Personne *tete) {
  int count = 0;
  Personne *courant = tete;
  while (courant) {
    count++;
    courant = courant->frere;
  }
  return count;
}

/**
 * Collecte tous les elements d'une liste chainee (tete -> frere -> frere...)
 * dans un tableau de pointeurs. 'index' va s'incrementer au fur et a mesure.
 */
void collecterElementsListe(Personne *tete, Personne **tableau, int *index) {
  Personne *courant = tete;
  while (courant) {
    tableau[*index] = courant;
    (*index)++;
    courant = courant->frere;
  }
}

/**
 * Trie un tableau de Personne* par age decroissant (bubble sort ou autre).
 */
void trierParAgeDecroissant(Personne **tableau, int taille) {
  for (int i = 0; i < taille - 1; i++) {
    for (int j = 0; j < taille - i - 1; j++) {
      if (tableau[j]->age < tableau[j + 1]->age) {
        // Echange
        Personne *temp = tableau[j];
        tableau[j] = tableau[j + 1];
        tableau[j + 1] = temp;
      }
    }
  }
}

/**
 * Affiche la liste d'elements (apres tri) : nom et age.
 * Utilitaire qui suppose que le tri a deja ete effectue.
 */
void afficherTableauPersonnes(Personne **tableau, int taille) {
  for (int i = 0; i < taille; i++) {
    printf("- %s, %d\n", tableau[i]->nom, tableau[i]->age);
  }
}

/**
 * Affiche soit les enfants, soit les freres/soeurs d'une personne
 * par ordre decroissant d'age.
 * Parametre 'type' : 1 = enfants, 2 = freres/soeurs
 */
void afficherFilsOuFreresDesc(Personne *personne, int type) {
  if (!personne)
    return;

  // On recupere la "tete" de la liste a afficher
  Personne *liste = NULL;
  if (type == 1) {
    liste = personne->enfant; // enfants
  } else {
    liste = personne->frere; // freres/soeurs
  }

  if (liste == NULL) {
    if (type == 1) {
      printf("Cette personne n'a pas d'enfants.\n");
    } else {
      printf("Cette personne n'a pas de freres/soeurs.\n");
    }
    return;
  }

  // Compter et collecter
  int nb = compterElementsListe(liste);
  Personne **tableau = (Personne **)malloc(nb * sizeof(Personne *));
  if (!tableau) {
    printf("Erreur d'allocation memoire (tableau).\n");
    return;
  }

  int index = 0;
  collecterElementsListe(liste, tableau, &index);

  // Trier par age decroissant
  trierParAgeDecroissant(tableau, nb);

  // Affichage
  printf("Liste des %s de %s par ordre decroissant d'age :\n",
         (type == 1) ? "enfants" : "freres/soeurs", personne->nom);
  afficherTableauPersonnes(tableau, nb);

  free(tableau);
}

/*--------------------------------------------
  FONCTION DE MENU
--------------------------------------------*/
int menu() {
  int choix;
  printf("\n=== MENU GESTION ARBRE GENEALOGIQUE ===\n");
  printf("1. Creer/Definir la racine (si inexistante)\n");
  printf("2. Ajouter un enfant\n");
  printf("3. Ajouter un frere/une soeur\n");
  printf("4. Afficher l'arbre\n");
  printf(
      "5. Afficher les enfants ou freres d'une personne (ordre decroissant)\n");
  printf("6. Quitter\n");
  printf("Choix : ");
  scanf("%d", &choix);
  getchar(); // pour consommer le \n
  return choix;
}

/*--------------------------------------------
  FONCTION PRINCIPALE
--------------------------------------------*/
int main() {
  Personne *racine = NULL; // racine de l'arbre (ou premiere racine)
  int choix;
  char nomParent[TAILLE_NOM];
  char nom[TAILLE_NOM];
  int age;

  do {
    choix = menu();
    switch (choix) {
    case 1: {
      if (racine != NULL) {
        printf("La racine existe deja : %s, %d\n", racine->nom, racine->age);
      } else {
        printf("Entrez le nom de la racine : ");
        fgets(nom, TAILLE_NOM, stdin);
        nom[strcspn(nom, "\n")] = '\0'; // enlever le \n
        printf("Entrez l'age : ");
        scanf("%d", &age);
        getchar();
        racine = creerPersonne(nom, age);
        printf("Racine cree : %s, %d\n", racine->nom, racine->age);
      }
      break;
    }

    case 2: {
      if (racine == NULL) {
        printf("Aucune racine. Veuillez d'abord creer la racine.\n");
      } else {
        printf("Entrez le nom du parent : ");
        fgets(nomParent, TAILLE_NOM, stdin);
        nomParent[strcspn(nomParent, "\n")] = '\0';
        Personne *parent = rechercherPersonne(racine, nomParent);
        if (parent == NULL) {
          printf("Parent introuvable dans l'arbre.\n");
        } else {
          printf("Entrez le nom du nouvel enfant : ");
          fgets(nom, TAILLE_NOM, stdin);
          nom[strcspn(nom, "\n")] = '\0';
          printf("Entrez l'age de l'enfant : ");
          scanf("%d", &age);
          getchar();
          Personne *enfant = creerPersonne(nom, age);
          ajouterEnfant(parent, enfant);
          printf("Enfant ajoute a %s.\n", parent->nom);
        }
      }
      break;
    }

    case 3: {
      if (racine == NULL) {
        printf("Aucune racine. Veuillez d'abord creer la racine.\n");
      } else {
        printf("Entrez le nom de la personne a qui ajouter un frere/soeur : ");
        fgets(nomParent, TAILLE_NOM, stdin);
        nomParent[strcspn(nomParent, "\n")] = '\0';
        Personne *personne = rechercherPersonne(racine, nomParent);
        if (personne == NULL) {
          printf("Personne introuvable dans l'arbre.\n");
        } else {
          printf("Entrez le nom du frere/soeur : ");
          fgets(nom, TAILLE_NOM, stdin);
          nom[strcspn(nom, "\n")] = '\0';
          printf("Entrez l'age : ");
          scanf("%d", &age);
          getchar();
          Personne *frereSoeur = creerPersonne(nom, age);
          ajouterFrere(personne, frereSoeur);
          printf("Frere/soeur ajoute(e) a %s.\n", personne->nom);
        }
      }
      break;
    }

    case 4: {
      if (racine == NULL) {
        printf("Aucune racine n'existe.\n");
      } else {
        printf("\n--- AFFICHAGE DE L'ARBRE GENEALOGIQUE ---\n");
        afficherArbre(racine, 0);
        printf("------------------------------------------\n");
      }
      break;
    }

    case 5: {
      // Afficher les enfants ou freres d'une personne, par ordre decroissant
      if (racine == NULL) {
        printf("Aucune racine n'existe.\n");
      } else {
        printf("Entrez le nom de la personne : ");
        fgets(nomParent, TAILLE_NOM, stdin);
        nomParent[strcspn(nomParent, "\n")] = '\0';
        Personne *personne = rechercherPersonne(racine, nomParent);
        if (personne == NULL) {
          printf("Personne introuvable dans l'arbre.\n");
        } else {
          int sousChoix;
          printf("Tapez 1 pour afficher les enfants, 2 pour afficher les "
                 "freres/soeurs : ");
          scanf("%d", &sousChoix);
          getchar();
          if (sousChoix == 1 || sousChoix == 2) {
            afficherFilsOuFreresDesc(personne, sousChoix);
          } else {
            printf("Choix invalide.\n");
          }
        }
      }
      break;
    }

    case 6:
      printf("Fermeture du programme.\n");
      break;

    default:
      printf("Choix invalide.\n");
      break;
    }

  } while (choix != 6);

  return 0;
}
