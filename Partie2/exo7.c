#include <stdio.h>
#include <stdlib.h>
#include "Graphe.h"



void plusCourtChemin(Solution *S , int i , int  j , int k , int l ) {
    
    int r = 0;
    char moveL = 'D' , moveC = 'R';
    if ( l < j )
        moveC = 'L' ;
    if ( i > k)
        moveL = 'U' ;
    for ( r = 0 ; r < abs(i - k) ; r++)
        Ajout_action(S , moveL);
    for ( r = 0 ; r < abs(j - l ) ; r++)
        Ajout_action(S , moveC);

}

/* fonction qui retourne le circuit le plus proche d'une case donnée*/
Cell_circuit* RecherchePlusProcheCircuit(Grille *G,Lcircuit *LC, int i, int j){
  Cell_circuit *cour = NULL, *precedent = NULL, *plusProcheCircuit;
  int k, l, min = G->m + G->n;
  if(LC == NULL){
   fprintf(stderr,"liste de circuits vide\n");
   return NULL;
  }
  cour = LC->premier;
  while (cour != NULL) {
    k = cour->L->premier->i;
    l = cour->L->premier->j;
    if (( abs(i-k) + abs(j-l)) < min) {
      plusProcheCircuit = cour;
      min = abs(i-k) + abs(j-l);
    }
    
    cour = cour->suiv;
  }
  return plusProcheCircuit;
}


void algorithme_graphe_naif(Grille *G, Solution *S){

  Graphe *H = NULL;
  Lcircuit *lc = NULL;
  Cell_circuit *circ = NULL, *courant = NULL;
  CelluleLDC *cell = NULL;
  int k = 0, l = 0;
  
  H = malloc(sizeof(Graphe));
  if (H == NULL) return;
  Graphe_creation(G, H);
  lc = malloc(sizeof(Lcircuit));
  LCInitialise(lc);
  
  lc = Graphe_rech_circuit(H);
  if (lc == NULL) return;

  //on traite d'abord le premier circuit
  circ = lc->premier;
  cell = circ->L->premier;
  k = cell->i;
  l = cell->j;
  while (cell ) {
      plusCourtChemin(S , G->ir , G->jr , cell->i , cell->j);
      changement_case(G , cell->i , cell->j );
      swap_case(G);
      Ajout_action(S , 'S');
      cell = cell->suiv;
  }
  plusCourtChemin(S , G->ir , G->jr , k , l );
  changement_case(G , k , l);
  swap_case(G);
  Ajout_action(S , 'S');
  LCSupprimerCellule(lc, lc->premier);


  while (LCVide(lc) == 0) {
    courant = RecherchePlusProcheCircuit(G,lc, k, l); //on recherche le precedent du plus proche circuit
    if (courant == NULL) circ = lc->premier; //si on trouve pas un plus proche, on parcourt la liste chainée
    else circ = courant; //sinon on traite le circuit trouvé
    cell = circ->L->premier;
    k = cell->i;
    l = cell->j;
    while (cell) { //on parcourt le circuit
      plusCourtChemin(S , G->ir , G->jr , cell->i , cell->j); 
      changement_case(G , cell->i , cell->j );
      swap_case(G);
      Ajout_action(S , 'S');
      cell = cell->suiv;
    }
    plusCourtChemin(S , G->ir , G->jr , k , l); //on boucle le circuit
    changement_case(G , k , l);
    swap_case(G);
    Ajout_action(S , 'S');
    LCSupprimerCellule(lc,courant); //on supprime le circuit de la liste chainée lc
  }

  LCDesalloue(lc);

}

int main (int argc ,char **argv ){

    Grille G;
    Solution S;
    int graine;
    Solution_init(&S);
    if(argc!=5){
        printf("Format: <nb_lignes> <nb_colonnes> <nb_couleurs> <graine>\n");
        return 1;
    }

    G.m=atoi(argv[1]);
    G.n=atoi(argv[2]);    
    G.nbcoul=atoi(argv[3]);

    if (G.m * G.n != G.nbcoul){
        printf("Il doit y avoir autant de couleurs que de cases\n");
        return 1;
    }

    graine=atoi(argv[4]);
    Grille_allocation(&G);
    Gene_Grille(&G , graine);
    algorithme_graphe_naif(&G, &S);
    Ecriture_Disque(G.m , G.n , G.nbcoul , graine , &S);
    return 0;
} 
