#ifndef __AVL__
#define __AVL__

#include <stdio.h>
#include <stdlib.h>

typedef struct s_avltree {
  int content; /* contenu du noeud */
  int hauteur; /* hauteur de l'arbre */
  struct s_avltree* fg;
  struct s_avltree* fd;
} AVL;


AVL* creerNoeud(int content, AVL* fg, AVL* fd); 
int hauteur(AVL* avl);
void hauteurFils(AVL *avl, int* hg, int* hd);
void majHauteur(AVL* avl);
AVL* rotDroite(AVL* rac); //rotation droite
AVL* rotGauche(AVL* rac); //rotation gauche
AVL* doubleRotDroite(AVL* rac); //double rotation droite
AVL* equilibrer(AVL* avl); //reequilibre l'arbre AVL
void AVLdesalloue(AVL* avl);
AVL* insererNoeud(AVL* avl, int val); // insere un element dans l'arbre AVL
AVL* supprimeNoeud(AVL* avl, int val); // supprime un noeud de l'arbre AVL
AVL *rechercheNoeud(AVL *avl , int val);
void afficherAVL(AVL *avl);
int supprimerMaxArbre(AVL **avl); //supprimer le max de l'avl
AVL*** init_matriceAVL ( int nb_coul , int nb_lignes ); //initialise la matrice d'AVL
void recherche_procheAVL(AVL *arbre , int valeur , int *j);
#endif