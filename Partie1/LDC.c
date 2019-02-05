#include "LDC.h"
#include <stdio.h>
#include <stdlib.h>


CelluleLDC* creerCellule(int i, int j){
    CelluleLDC* cellule = (CelluleLDC *) malloc(sizeof(CelluleLDC));
    if (cellule == NULL) {
        fprintf(stderr, "Erreur\n");
        return NULL;
    }
    cellule->suiv = NULL;
    cellule-> prec = NULL;
    cellule->i = i;
    cellule->j = j;

    return cellule;

}


void LDCInitialise(LDC *ldc){
    if (ldc != NULL) {
        fprintf(stderr, "La liste est déja initialisée \n");
        return;
    }
    ldc->premier = NULL;
    ldc->dernier = NULL;
}

int LDCVide(LDC* ldc){
    return ldc->premier == NULL;
}

void LDCInsererEnFin(LDC** ldc, int i, int j){
    CelluleLDC* cell = creerCellule(i,j);

    if ( !(*ldc) ){
        LDC *templdc = malloc(sizeof(LDC));
        templdc->premier = cell;
        templdc->dernier = cell;
         
        *ldc = templdc;
    }
    else if(LDCVide(*ldc)){
        (*ldc)->premier = cell;
        (*ldc)->dernier = cell;
    }
    else{
        cell->prec = (*ldc)->dernier;
        (*ldc)->dernier->suiv = cell;
        (*ldc)->dernier = cell;
    }
}


void LDCenleverCellule(LDC* ldc, CelluleLDC* cel){

  if (LDCVide(ldc) || cel == NULL) {
    fprintf(stderr, "Erreur\n");
    return;
  }
  // Si la cellule se trouve au debut de la liste
  if (cel->prec == NULL) {
    ldc->premier = cel->suiv;
    ldc->premier->prec = NULL;
  } else {
    cel->prec->suiv = cel->suiv;
  }
  // Si la cellule se trouve à la fin de la liste
  if (cel->suiv == NULL) {
    ldc->dernier = cel->prec;
    ldc->dernier->suiv = NULL;
  } else {
    cel->suiv->prec = cel->prec;
  }
}



void LDCafficher(LDC* ldc){

    CelluleLDC* tmp = NULL;
    if ( !ldc ) return;
    if (LDCVide(ldc)) return;

    tmp = ldc->premier;
    while (tmp!= NULL) {
        printf("(%d, %d)\t\t\n", tmp->i, tmp->j);
        tmp = tmp->suiv;
    }
    printf("\n");

}

void LDCdesalloue(LDC* ldc){
    CelluleLDC* cell = NULL, *tmp = NULL;

    if (LDCVide(ldc)) return;

    cell = ldc->premier;

    while (cell!= NULL) {
        tmp = cell;
        cell = cell->suiv;
        free(tmp);
    }

}

CelluleLDC* LDCrechercherPlusProcheCase(LDC* ldc, int i, int j){

    if (LDCVide(ldc) || !ldc ){
        fprintf(stderr , " erreur dans la création !\n" );
        return NULL;
    } 

    CelluleLDC *tmp = NULL, *caseProche = NULL;

    int min =0; 

    tmp = ldc->premier;
    min = abs(ldc->premier->i - i ) + abs(ldc->premier->j -j) ;
    caseProche = tmp;
    /*on parcourt la liste et on cherche la case la plus proche de (i,j) */
    while(tmp){ 
        if ( (abs(tmp->i - i) + abs(tmp->j - j) ) < min){
            min = (abs(tmp->i - i) + abs(tmp->j - j));
            caseProche = tmp;   
        }
        tmp = tmp->suiv;
    }
    return caseProche;


}

void supprimerCell(LDC * ldc , CelluleLDC * cell){
    if ( !ldc || !cell){
        fprintf(stderr , "erreur!");
        return;   
    }
    CelluleLDC *prec = cell->prec , *suiv = cell->suiv;
    if ( !prec || !suiv ){
        if ( ldc->premier == cell ){
            ldc->premier = suiv;
            if (suiv) suiv->prec = NULL;
        }
        
        if ( ldc->dernier == cell ){
            ldc->dernier = prec;
            if (prec) prec->suiv = NULL;
        }
    }
    else{
            if (prec ) prec->suiv = suiv;
            if ( suiv) suiv->prec = prec;
    }

    free(cell);
}