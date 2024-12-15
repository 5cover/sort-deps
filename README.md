# Namelazz

Order things that depend on each other.

- Functions in a programing language
- Production rules in a formal grammar
- Nodes in a Mermaid flowchart
- ...

## Ordering system

Goal : canonical, human ordering.

We want to see the big picture first. Keep the most fundamental and atomic details at the bottom, and the great overseering items at the top.

In concrete terms:

- Items that have no dependents (*roots*) are first;
- Items that have no dependencies (*leaves*) are last;
- Items are sorted by count of dependents
- Custom rules possible (such as alphabetical sorting on other properties)
- Base items only have dependencies.
- Dependencies should be as close as possible to their dependents

An item's *name* identifies it uniquely. In a context of a programming language, it might be function's name. If function overloading is supported, it would include the function's arguments.

An item can specify it needs to be defined before its dependents. This is the case for C macros, for instance.

## Example

A single-file Sudoku game.

Symbol list:

Kind|Name
-|-
Macro|AFFICHAGE_ESPACE
Macro|AFFICHAGE_INTERSECTION
Macro|AFFICHAGE_INTERSECTION
Macro|AFFICHAGE_MARGE_NUMEROS_LIGNES
Macro|AFFICHAGE_PADDING
Macro|AFFICHAGE_TRAIT_HORIZONTAL
Macro|AFFICHAGE_TRAIT_VERTICAL
Macro|AFFICHAGE_VALEUR_VIDE
Macro|N
Macro|TAILLE
Macro|VALEUR_VIDE
Type definition|tGrille
Function declaration|afficherGrille
Function declaration|afficherLigneContenu
Function declaration|afficherLigneNumerosDeColonne
Function declaration|afficherLigneSeparationBlocs
Function declaration|afficherPlusieursFois
Function declaration|afficherValeur
Function declaration|chargerGrille
Function declaration|nombreDeChiffres
Function declaration|nombreDeValeurs
Function declaration|possible
Function declaration|possibleBloc
Function declaration|possibleColonne
Function declaration|possibleLigne
Function declaration|saisir
Function definition|afficherGrille
Function definition|afficherLigneContenu
Function definition|afficherLigneNumerosDeColonne
Function definition|afficherLigneSeparationBlocs
Function definition|afficherPlusieursFois
Function definition|afficherValeur
Function definition|chargerGrille
Function definition|main
Function definition|nombreDeChiffres
Function definition|nombreDeValeurs
Function definition|possible
Function definition|possibleBloc
Function definition|possibleColonne
Function definition|possibleLigne
Function definition|saisir

Now, for the dependency graph (Doxygen `@ref` doesn't count as a dependency):

Function definitions and their declarations are interdependent.

A function definition's only dependencies are its declarations.

```mermaid
%%{init: {"flowchart": {"defaultRenderer": "elk"}} }%%
flowchart LR
macro-N["macro N"]
macro-TAILLE-->macro-N
fdef-possibleBloc-->macro-N
fdef-afficherGrille-->macro-N
fdef-afficherLigneNumerosDeColonne-->macro-N
fdef-afficherLigneSeparationBlocs-->macro-N
fdef-afficherLigneContenu-->macro-N

macro-TAILLE["macro TAILLE"]
macro-AFFICHAGE_PADDING-->macro-TAILLE
typedef-tGrille-->macro-TAILLE
fdef-main-->macro-TAILLE
fdef-chargerGrille-->macro-TAILLE
fdef-nombreDeValeurs-->macro-TAILLE
fdef-saisir-->macro-TAILLE
fdef-possibleLigne-->macro-TAILLE
fdef-possibleColonne-->macro-TAILLE

macro-VALEUR_VIDE["macro VALEUR_VIDE"]
fdef-main-->macro-VALEUR_VIDE
fdef-nombreDeValeurs-->macro-VALEUR_VIDE
fdef-afficherValeur-->macro-VALEUR_VIDE

macro-AFFICHAGE_PADDING["macro AFFICHAGE_PADDING"]
fdef-afficherLigneNumerosDeColonne-->macro-AFFICHAGE_PADDING
fdef-afficherLigneSeparationBlocs-->macro-AFFICHAGE_PADDING
fdef-afficherLigneContenu-->macro-AFFICHAGE_PADDING
fdef-afficherValeur-->macro-AFFICHAGE_PADDING

macro-AFFICHAGE_MARGE_NUMEROS_LIGNES["macro AFFICHAGE_MARGE_NUMEROS_LIGNES"]
fdef-afficherLigneNumerosDeColonne-->macro-AFFICHAGE_MARGE_NUMEROS_LIGNES
fdef-afficherLigneSeparationBlocs-->macro-AFFICHAGE_MARGE_NUMEROS_LIGNES
fdef-afficherLigneContenu-->macro-AFFICHAGE_MARGE_NUMEROS_LIGNES

macro-AFFICHAGE_ESPACE["macro AFFICHAGE_ESPACE"]
fdef-afficherLigneNumerosDeColonne-->macro-AFFICHAGE_ESPACE
fdef-afficherLigneSeparationBlocs-->macro-AFFICHAGE_ESPACE
fdef-afficherLigneContenu-->macro-AFFICHAGE_ESPACE
fdef-afficherValeur-->macro-AFFICHAGE_ESPACE

macro-AFFICHAGE_VALEUR_VIDE["macro AFFICHAGE_VALEUR_VIDE"]
fdef-afficherValeur-->macro-AFFICHAGE_VALEUR_VIDE

macro-AFFICHAGE_INTERSECTION["macro AFFICHAGE_INTERSECTION"]
fdef-afficherLigneSeparationBlocs-->macro-AFFICHAGE_INTERSECTION

macro-AFFICHAGE_TRAIT_VERTICAL["macro AFFICHAGE_TRAIT_VERTICAL"]
fdef-afficherLigneContenu-->macro-AFFICHAGE_TRAIT_VERTICAL

macro-AFFICHAGE_TRAIT_HORIZONTAL["macro AFFICHAGE_TRAIT_HORIZONTAL"]
fdef-afficherLigneSeparationBlocs-->macro-AFFICHAGE_TRAIT_HORIZONTAL

typedef-tGrille["typedef tGrille"]
fdecl-chargerGrille-->typedef-tGrille
fdecl-nombreDeValeurs-->typedef-tGrille
fdecl-possible-->typedef-tGrille
fdecl-possibleLigne-->typedef-tGrille
fdecl-possibleColonne-->typedef-tGrille
fdecl-possibleBloc-->typedef-tGrille
fdecl-afficherGrille-->typedef-tGrille
fdecl-afficherLigneContenu-->typedef-tGrille
fdef-main-->typedef-tGrille
fdef-chargerGrille-->typedef-tGrille
fdef-nombreDeValeurs-->typedef-tGrille
fdef-possible-->typedef-tGrille
fdef-possibleLigne-->typedef-tGrille
fdef-possibleColonne-->typedef-tGrille
fdef-possibleBloc-->typedef-tGrille
fdef-afficherGrille-->typedef-tGrille
fdef-afficherLigneContenu-->typedef-tGrille

fdecl-nombreDeChiffres["fdecl nombreDeChiffres"]
fdef-nombreDeChiffres-->fdecl-nombreDeChiffres
macro-AFFICHAGE_PADDING-->fdecl-nombreDeChiffres

fdecl-nombreDeValeurs["fdecl nombreDeValeurs"]
fdef-nombreDeValeurs-->fdecl-nombreDeValeurs
fdef-main-->fdecl-nombreDeValeurs

fdecl-chargerGrille["fdecl chargerGrille"]
fdef-chargerGrille-->fdecl-chargerGrille
fdef-main-->fdecl-chargerGrille

fdecl-possible["fdecl possible"]
fdef-possible-->fdecl-possible
fdef-main-->fdecl-possible

fdecl-saisir["fdecl saisir"]
fdef-saisir-->fdecl-saisir
fdef-main-->fdecl-saisir

fdecl-possibleColonne["fdecl possibleColonne"]
fdef-possibleColonne-->fdecl-possibleColonne
fdef-possible-->fdecl-possibleColonne

fdecl-possibleLigne["fdecl possibleLigne"]
fdef-possibleLigne-->fdecl-possibleLigne
fdef-possible-->fdecl-possibleLigne

fdecl-afficherGrille["fdecl afficherGrille"]
fdef-afficherGrille-->fdecl-afficherGrille
fdef-main-->fdecl-afficherGrille

fdecl-possibleBloc["fdecl possibleBloc"]
fdef-possibleBloc-->fdecl-possibleBloc
fdef-possible-->fdecl-possibleBloc

fdecl-afficherLigneSeparationBlocs["fdecl afficherLigneSeparationBlocs"]
fdef-afficherLigneSeparationBlocs-->fdecl-afficherLigneSeparationBlocs
fdef-afficherGrille-->fdecl-afficherLigneSeparationBlocs

fdecl-afficherLigneNumerosDeColonne["fdecl afficherLigneNumerosDeColonne"]
fdef-afficherLigneNumerosDeColonne-->fdecl-afficherLigneNumerosDeColonne
fdef-afficherGrille-->fdecl-afficherLigneNumerosDeColonne

fdecl-afficherPlusieursFois["fdecl afficherPlusieursFois"]
fdef-afficherPlusieursFois-->fdecl-afficherPlusieursFois
fdef-afficherLigneNumerosDeColonne-->fdecl-afficherPlusieursFois
fdef-afficherLigneSeparationBlocs-->fdecl-afficherPlusieursFois
fdef-afficherLigneContenu-->fdecl-afficherPlusieursFois

fdecl-afficherLigneContenu["fdecl afficherLigneContenu"]
fdef-afficherLigneContenu-->fdecl-afficherLigneContenu
fdef-afficherGrille-->fdecl-afficherLigneContenu

fdecl-afficherValeur["fdecl afficherValeur"]
fdef-afficherValeur-->fdecl-afficherValeur
fdef-afficherLigneContenu-->fdecl-afficherValeur

fdef-main["fdef main"]

fdef-chargerGrille["fdef chargerGrille"]
fdecl-chargerGrille-->fdef-chargerGrille

fdef-nombreDeChiffres["fdef nombreDeChiffres"]
fdecl-nombreDeChiffres-->fdef-nombreDeChiffres

fdef-saisir["fdef saisir"]
fdecl-saisir-->fdef-saisir

fdef-nombreDeValeurs["fdef nombreDeValeurs"]
fdecl-nombreDeValeurs-->fdef-nombreDeValeurs

fdef-possibleLigne["fdef possibleLigne"]
fdecl-possibleLigne-->fdef-possibleLigne

fdef-possible["fdef possible"]
fdecl-possible-->fdef-possible

fdef-possibleBloc["fdef possibleBloc"]
fdecl-possibleBloc-->fdef-possibleBloc

fdef-possibleColonne["fdef possibleColonne"]
fdecl-possibleColonne-->fdef-possibleColonne

fdef-afficherLigneNumerosDeColonne["fdef afficherLigneNumerosDeColonne"]
fdecl-afficherLigneNumerosDeColonne-->fdef-afficherLigneNumerosDeColonne

fdef-afficherGrille["fdef afficherGrille"]
fdecl-afficherGrille-->fdef-afficherGrille

fdef-afficherLigneContenu["fdef afficherLigneContenu"]
fdecl-afficherLigneContenu-->fdef-afficherLigneContenu

fdef-afficherLigneSeparationBlocs["fdef afficherLigneSeparationBlocs"]
fdecl-afficherLigneSeparationBlocs-->fdef-afficherLigneSeparationBlocs

fdef-afficherPlusieursFois["fdef afficherPlusieursFois"]
fdecl-afficherPlusieursFois-->fdef-afficherPlusieursFois

fdef-afficherValeur["fdef afficherValeur"]
fdecl-afficherValeur-->fdef-afficherValeur
```
