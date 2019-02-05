#ifndef __AuPlusProche__
#define __AuPlusProche__

#include "Solution.h"
#include "Grille.h"
#include "LDC.h"
#include "AVL.h"

void plusCourtChemin(Solution *S , int i , int  j , int k , int l );
int caseNoire( Grille *G , int i , int j);
int pieceNoir( Grille *G , int i , int j);
int robotPortePiece(Grille*G, int i, int j);
void RechercheCaseNaif_c(Grille* G, int c,int i, int j,int *k,int *l);
void RechercheCaseNaif_nn(Grille* G,int i, int j,int *k,int *l);
void algorithme_naif(Grille *G , Solution *S);
void rechercheCaseCirculaire_c(Grille *G , int c , int i, int j  , int *k , int *l);
void rechercheCaseCirculaire_nn(Grille *G ,int i, int j  , int *k , int *l);
void algorithme_circulaire(Grille *G , Solution *S);
void algorithme_parcouleur(Grille *G, Solution *S);
AVL ***creation_matriceAVL( Grille * G );
void case_proche_AVL(AVL ***M , Grille *G ,int couleur ,  int i , int j , int *k , int *l);
void algorithme_AVL(Grille *G , Solution *S );



#endif