/** @file
 * @brief Jeu de Sudoku
 * @version 1.0.0
 * @date 23/11/2023
 * @author Raphaël BARDINI 1C2
 * @remarks GCC : compiler avec l'option @c -lm (utilisation de @c math.h)
 *
 * SAÉ 1.01 - Jeu de Sudoku en ligne de commande.
 */

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/// @brief Entier : facteur de taille de la grille
/// @remark Cette valeur peut être modifiée pour jouer avec une grille d'une taille différente.
#define N 3

/// @brief Entier : côté de la grille
#define TAILLE (N * N)

/// @brief Entier : représente une valeur vide sur la grille.
#define VALEUR_VIDE 0

/// @brief Matrice carrée d'entiers de côté @ref TAILLE représentant une grille de Sudoku
typedef int tGrille[TAILLE][TAILLE];

/// @brief Affiche une grille et son contenu à l’écran.
/// @param grille E : @ref tGrille : la grille à afficher
void afficherGrille(tGrille grille);

/// @brief Charge en mémoire une grille de Sudoku existante à partir d’un fichier dont le nom est lu au clavier.
/// @param g S : @ref tGrille : la grille à remplir
/// @remark Quitte le programme avec pour code de sortie @c EXIT_FAILURE si le fichier ne peut pas être ouvert.
void chargerGrille(tGrille g);

/// @brief Retourne le nombre de valeurs présentes dans une grille.
/// @param grille E : @ref tGrille : la grille
/// @return entier : le nombre de valeurs différentes de @ref VALEUR_VIDE dans @p grille.
int nombreDeValeurs(tGrille grille);

/// @brief Vérifie qu'une valeur peut être ajoutée à la grille.
/// @param grille E : @ref tGrille : la grille
/// @param numLigne E : entier : numéro de ligne de la case visée
/// @param numColonne E : entier : numéro de colonne de la case visée
/// @param valeur E : entier : la valeur à insérer dans la grille
/// @return booléen : @c true si la valeur peut être ajoutée à la grille à l'emplacement indiqué ; @c false sinon.
/// @remark Affiche un message d'erreur explicite si la valeur ne peut pas être ajoutée à la grille.
///
/// D'après les règles du Sudoku, une valeur ne peut être ajoutée à la grille que quand elle n'est pas déjà présente
/// dans la ligne, dans la colonne et dans le bloc.
bool possible(tGrille grille, int numLigne, int numColonne, int valeur);

/// @brief Lit au clavier un entier compris entre 1 et @ref TAILLE.
/// @param saisie S : entier : assigné à l'entier lu
/// @remark La saisie se répète et un message d'erreur est affiché tant que la valeur n’est pas valide.
void saisir(int *saisie);

int main()
{
    int valeur;     // valeur entrée
    int numLigne;   // numéro de ligne où insérer la valeur
    int numColonne; // numéro de colonne où insérer la valeur
    tGrille grille; // grille de jeu

    chargerGrille(grille);

    // nombre de valeurs insérées dans la grille
    // initialisé au nombre de valeurs initiales
    int nbValeursEntrees = nombreDeValeurs(grille);

    // boucle principale
    while (nbValeursEntrees < TAILLE * TAILLE) {
        afficherGrille(grille);

        printf("Indices de la case ?\n");
        printf("Ligne : ");
        saisir(&numLigne);
        printf("Colonne : ");
        saisir(&numColonne);

        // Les indices de tableau sont basés à 0 en C. Or l'utilisateur a entré des indices basés à 1.
        // Il faut donc décrémenter les indices entrés.
        numLigne--;
        numColonne--;

        if (grille[numLigne][numColonne] != VALEUR_VIDE) {
            printf("IMPOSSIBLE, la case n'est pas libre.\n");
        } else {
            printf("Valeur à insérer : ");
            saisir(&valeur);
            if (possible(grille, numLigne, numColonne, valeur)) {
                grille[numLigne][numColonne] = valeur;
                nbValeursEntrees++;
            }
        }
    }

    afficherGrille(grille); // afficher la grille complète

    printf("Grille pleine, fin de partie\n");

    return EXIT_SUCCESS;
}

/// @brief Affiche une ligne de la grille.
/// @param grille E : @ref tGrille : la grille
/// @param numLigne E : entier : le numéro de la ligne à afficher (entre 0 et @ref TAILLE - 1)
void afficherLigneContenu(tGrille grille, int numLigne);

/// @brief Affiche la ligne des numéros de colonne.
void afficherLigneNumerosDeColonne(void);

/// @brief Affiche une ligne de séparation de blocs.
void afficherLigneSeparationBlocs(void);

void afficherGrille(tGrille grille)
{
    afficherLigneNumerosDeColonne();

    // Affichage du corps de la grille
    for (int numBloc = 0; numBloc < N; numBloc++) {
        afficherLigneSeparationBlocs();

        // Pour chaque ligne du bloc
        for (int numLigneBloc = 0; numLigneBloc < N; numLigneBloc++) {
            // Faire un calcul pour obtenir le véritable numéro de ligne, puis afficher la ligne.
            afficherLigneContenu(grille, numBloc * N + numLigneBloc);
        }
    }

    // Afficher la dernière ligne de séparation tout en bas
    afficherLigneSeparationBlocs();
}

void chargerGrille(tGrille g)
{
    // Code déjà fourni pour cette procédure.
    char nomFichier[20];
    FILE *f;
    printf("Nom du fichier ? ");
    scanf("%s", nomFichier);
    f = fopen(nomFichier, "rb");
    if (f == NULL) {
        printf("\n ERREUR sur le fichier %s\n", nomFichier);
        exit(EXIT_FAILURE); // arrêter le programme si le fichier ne peut pas être ouvert
    } else {
        fread(g, sizeof(int), TAILLE * TAILLE, f);
        fclose(f); // ne pas appeler fclose sur un NULL (comportement indéfini)
    }
}

int nombreDeValeurs(tGrille grille)
{
    int nbValeurs = 0;

    for (int numLigne = 0; numLigne < TAILLE; numLigne++) {
        for (int numColonne = 0; numColonne < TAILLE; numColonne++) {
            if (grille[numLigne][numColonne] != VALEUR_VIDE) {
                nbValeurs++;
            }
        }
    }

    return nbValeurs;
}

/// @brief Détermine si une valeur est absente du bloc contenant la case indiquée.
/// @param grille E : @ref tGrille : la grille
/// @param numLigne E : entier : le numéro de ligne de la case
/// @param numColonne E : entier : le numéro de colonne de la case
/// @param valeur E : entier : la valeur à rechercher
/// @return booléen : @c true si @p valeur est absente du bloc contenant la case de @p grille indiquée par @p numLigne
/// et @p numColonne ; @c false sinon.
bool possibleBloc(tGrille grille, int numLigne, int numColonne, int valeur);

/// @brief Détermine si une valeur est absente de la colonne indiquée.
/// @param grille E : @ref tGrille : la grille
/// @param numColonne E : entier : le numéro de colonne
/// @param valeur E : entier : la valeur à rechercher
/// @return booléen : @c true si @p valeur est absente du la colonne @p numColonne de @p grille ; @c false sinon.
bool possibleColonne(tGrille grille, int numColonne, int valeur);

/// @brief Détermine si une valeur est absente de la ligne indiquée.
/// @param grille E : @ref tGrille : la grille
/// @param numLigne E : entier : le numéro de ligne
/// @param valeur E : entier : la valeur à rechercher
/// @return booléen : @c true si @p valeur est absente de la ligne @p numLigne de @p grille ; @c false sinon.
bool possibleLigne(tGrille grille, int numLigne, int valeur);

bool possible(tGrille grille, int numLigne, int numColonne, int valeur)
{
    bool pasDansLaLigne = possibleLigne(grille, numLigne, valeur);
    bool pasDansLaColonne = possibleColonne(grille, numColonne, valeur);
    bool pasDansLeBloc = possibleBloc(grille, numLigne, numColonne, valeur);

    bool placementPossible = pasDansLaLigne && pasDansLaColonne && pasDansLeBloc;

    if (!placementPossible) {
        printf("IMPOSSIBLE de placer %d ici car il est déjà présent dans :\n", valeur);
        if (!pasDansLaLigne) {
            printf("- la ligne %d\n", numLigne + 1);
        }
        if (!pasDansLaColonne) {
            printf("- la colonne %d\n", numColonne + 1);
        }
        if (!pasDansLeBloc) {
            printf("- le bloc contenant la case ligne %d, colonne %d\n", numLigne + 1, numColonne + 1);
        }
        putchar('\n');
    }

    return placementPossible;
}

void saisir(int *saisie)
{
    char entree[20];  // buffer d'entrée
    int entreeEntier; // entier entré converti
    bool erreurDeSaisie = true;

    while (erreurDeSaisie) {
        // scanf lira au maximum 19 caractères, et non pas 20,
        // car il faut conserver une place pour le caractère de fin de chaîne '\0'.
        scanf("%19s", entree);
        if (sscanf(entree, "%d", &entreeEntier) == 0) {
            printf("Veuillez saisir un entier : ");
        } else if (entreeEntier < 1 || entreeEntier > TAILLE) {
            printf("Veuillez saisir un entier entre 1 et %d : ", TAILLE);
        } else {
            erreurDeSaisie = false;
        }
    }

    *saisie = entreeEntier;
}

/// @brief Caractère : représente un espace dans l'affichage de la grille
#define AFFICHAGE_ESPACE ' '

/// @brief Entier : marge à droite des numéros de ligne dans l'affichage de la grille
#define AFFICHAGE_MARGE_NUMEROS_LIGNES 2

/// @brief Retourne le nombre de chiffres d'un entier.
/// @param n E : entier : un entier quelconque
/// @return entier : le nombre de chiffres de @p n en base 10.
int nombreDeChiffres(int n);

/// @brief Entier : marge intérieure de l'affichage de la grille
#define AFFICHAGE_PADDING nombreDeChiffres(TAILLE)

/// @brief Caractère : représente un trait vertical dans l'affichage de la grille
#define AFFICHAGE_TRAIT_VERTICAL '|'

/// @brief Affiche un même caractère un certain nombre de fois.
/// @param caractere E : caractère : le caractère à afficher
/// @param nbFois E : entier : nombre de fois
void afficherPlusieursFois(char caractere, int nbFois);

/// @brief Affiche une valeur de la grille sous la forme d'un nombre ou de @ref AFFICHAGE_VALEUR_VIDE pour représenter
/// @ref VALEUR_VIDE, avec un espace de marge de chaque côté.
/// @param valeur E : entier : la valeur à afficher
void afficherValeur(int valeur);

void afficherLigneContenu(tGrille grille, int numLigne)
{
    // Affichage du numéro de ligne
    printf("%*d", AFFICHAGE_PADDING, numLigne + 1);
    afficherPlusieursFois(AFFICHAGE_ESPACE, AFFICHAGE_MARGE_NUMEROS_LIGNES);
    putchar(AFFICHAGE_TRAIT_VERTICAL);

    // Affichage du contenu de la ligne
    for (int numBloc = 0; numBloc < N; numBloc++) {
        for (int numColonneBloc = 0; numColonneBloc < N; numColonneBloc++) {
            afficherValeur(grille[numLigne][numBloc * N + numColonneBloc]);
        }
        putchar(AFFICHAGE_TRAIT_VERTICAL);
    }

    putchar('\n');
}

void afficherLigneNumerosDeColonne(void)
{
    afficherPlusieursFois(AFFICHAGE_ESPACE, AFFICHAGE_PADDING + AFFICHAGE_MARGE_NUMEROS_LIGNES);

    for (int numBloc = 0; numBloc < N; numBloc++) {
        putchar(AFFICHAGE_ESPACE);
        for (int numColonneBloc = 0; numColonneBloc < N; numColonneBloc++) {
            // Ajouter 1 pour afficher les numéros de 1 à N et non pas de 0 à N - 1.
            printf("%c%*d%c", AFFICHAGE_ESPACE, AFFICHAGE_PADDING, numBloc * N + numColonneBloc + 1, AFFICHAGE_ESPACE);
        }
    }

    putchar('\n');
}

/// @brief Caractère : représente une intersection dans l'affichage de la grille
#define AFFICHAGE_INTERSECTION '+'

/// @brief Caractère : représente un trait horizontal dans l'affichage de la grille
#define AFFICHAGE_TRAIT_HORIZONTAL '-'

void afficherLigneSeparationBlocs(void)
{
    afficherPlusieursFois(AFFICHAGE_ESPACE, AFFICHAGE_PADDING + AFFICHAGE_MARGE_NUMEROS_LIGNES);
    putchar(AFFICHAGE_INTERSECTION);

    for (int numBloc = 0; numBloc < N; numBloc++) {
        // Ajouter 2 pour prendre en compte la marge horizontale des valeurs (1 espace à gauche et à droite).
        afficherPlusieursFois(AFFICHAGE_TRAIT_HORIZONTAL, N * (AFFICHAGE_PADDING + 2));
        putchar(AFFICHAGE_INTERSECTION);
    }

    putchar('\n');
}

bool possibleBloc(tGrille grille, int numLigne, int numColonne, int valeur)
{
    bool placementPossible = true;

    int numLigneBloc = numLigne - (numLigne % N);       // numéro de ligne de début du bloc
    int numColonneBloc = numColonne - (numColonne % N); // numéro de colonne de début du bloc

    for (int numLigne = numLigneBloc; placementPossible && numLigne < numLigneBloc + N; numLigne++) {
        for (int numColonne = numColonneBloc; placementPossible && numColonne < numColonneBloc + N; numColonne++) {
            placementPossible = grille[numLigne][numColonne] != valeur;
        }
    }

    return placementPossible;
}

bool possibleColonne(tGrille grille, int numColonne, int valeur)
{
    bool placementPossible = true;

    for (int numLigne = 0; placementPossible && numLigne < TAILLE; numLigne++) {
        placementPossible = grille[numLigne][numColonne] != valeur;
    }

    return placementPossible;
}

bool possibleLigne(tGrille grille, int numLigne, int valeur)
{
    bool placementPossible = true;

    // la boucle s'arrête dès qu'on trouve la valeur (placementPossible devient faux).
    for (int numColonne = 0; placementPossible && numColonne < TAILLE; numColonne++) {
        placementPossible = grille[numLigne][numColonne] != valeur;
    }

    return placementPossible;
}

int nombreDeChiffres(int n)
{
    return n == 0 ? 1 : (int)log10(abs(n)) + 1;
}

void afficherPlusieursFois(char caractere, int nbFois)
{
    for (int fois = 0; fois < nbFois; fois++) {
        putchar(caractere);
    }
}

/// @brief Caractère : représente une valeur vide dans l'affichage de la grille
#define AFFICHAGE_VALEUR_VIDE '.'

void afficherValeur(int valeur)
{
    putchar(AFFICHAGE_ESPACE);

    if (valeur == VALEUR_VIDE) {
        printf("%*c", AFFICHAGE_PADDING, AFFICHAGE_VALEUR_VIDE);
    } else {
        printf("%*d", AFFICHAGE_PADDING, valeur);
    }

    putchar(AFFICHAGE_ESPACE);
}
