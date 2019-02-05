#include "LCircuit.h"
#include "ListeDC.h"
#include "Graphe.h"


Cell_circuit *LCCreerCellule(LDC *L, int jmin, int jmax , int imin, int imax){
  Cell_circuit *cell = (Cell_circuit *) malloc(sizeof(Cell_circuit));

  if (cell == NULL) {
    fprintf(stderr, "Erreur lors de l'allocation de la cellule\n");
    return NULL;
  }
  cell->L = L;
  cell->jmin = jmin;
  cell->jmax = jmax;
  cell->imin = imin;
  cell->imax = imax;
  cell->suiv = NULL;
  cell->prec = NULL;
  return cell;
}

void LCInitialise(Lcircuit *lc){
  if (lc == NULL) {
    fprintf(stderr, "Erreur lors de l'allocation de la cellule\n");
    return;
  }
  lc->premier = NULL;
  lc->dernier = NULL;
  lc->nb_circuit = 0;
}
int LCVide(Lcircuit *lc){
  if (lc == NULL) {
    fprintf(stderr, "la liste n'a pas ete allouee\n");
    return -1;
  }
  return lc->premier == NULL;
}

void LCInsererEnTete(Lcircuit* lc, LDC *L, int jmin, int jmax, int imin , int imax){
  Cell_circuit *nouv = LCCreerCellule(L,jmin, jmax , imin, imax);
  if (( LCVide(lc) == -1)|| (nouv == NULL)) {
    fprintf(stderr, "Erreur lors de l'ajout de la cellule\n");
    return;
  }
  if (LCVide(lc)) 
    lc->dernier=nouv;
  
  nouv->suiv = lc->premier;
  lc->premier = nouv;
  nouv->prec = NULL;
  lc->nb_circuit ++;
}

void LCInsererEnFin(Lcircuit* lc, LDC *L, int jmin, int jmax, int imin , int imax){

  Cell_circuit *nouv = LCCreerCellule(L,jmin, jmax , imin , imax);
  if (( LCVide(lc) == -1)|| (nouv == NULL)) {
    fprintf(stderr, "Erreur lors de l'ajout de la cellule\n");
    return;
  }
  if (LCVide(lc)){
      lc->premier = nouv;
      lc->dernier = nouv;
  }
  else{
      nouv->prec = lc->dernier;
      lc->dernier->suiv = nouv;
      lc->dernier = nouv;
  }
  
  lc->nb_circuit++;

}

void LCDesalloue(Lcircuit *lc){
  Cell_circuit *courant = NULL, *prec = NULL;
  if (LCVide(lc) || lc == NULL) {
    return;
  }
  courant = lc->premier;

  while (courant != NULL) {
    prec = courant;
    courant = courant->suiv;
    LDCdesalloue(prec->L);
    free(prec->L);
    free(prec);
  }
  lc->premier = NULL;
  lc->dernier = NULL;
}

void LCAfficher(Lcircuit *lc){
  Cell_circuit *cour = lc->premier ;
  while (cour){
    LDCafficher(cour->L);
    cour = cour->suiv;
  }
}


void LCSupprimerCellule(Lcircuit *lc, Cell_circuit *cell ){
  Cell_circuit *temp = NULL;

  if (LCVide(lc) != 0) {
    fprintf(stderr, "\tLa cellule n'a pas ete enlevee\n");
    return;
  }

  if (cell->prec == NULL) {
    lc->premier = cell->suiv;
  } else {
    cell->prec->suiv = cell->suiv;
  }

  if (cell == lc->dernier)
    lc->dernier = cell->prec;
  else
    cell->suiv->prec = cell->prec;
    
  LDCdesalloue(cell->L);
  free(cell->L);
  free(cell);
  lc->nb_circuit --;
}
