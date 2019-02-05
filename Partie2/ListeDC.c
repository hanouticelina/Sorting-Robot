#include<stdlib.h>
#include<stdio.h>
#include "ListeDC.h"

CelluleLDC* creerCelluleLDC(int i, int j){
  CelluleLDC* e =(CelluleLDC*)malloc(sizeof(CelluleLDC));
  e->prec=NULL;  /* Inutile mais bon reflexe */
  e->suiv=NULL;  /* Inutile mais bon reflexe */
  e->i=i;
  e->j=j;
  return e;

}

void LDCInitialise(LDC *ldc){
  ldc->premier=NULL;
  ldc->dernier=NULL;
}

int LDCVide(LDC* ldc){
 return (ldc->premier==NULL);
}

void LDCInsererEnTete(LDC* ldc, int i, int j){
  CelluleLDC* nouv=creerCelluleLDC(i,j);
  nouv->prec=NULL;
  if (LDCVide(ldc)) 
    ldc->dernier=nouv;
  else 
    ldc->premier->prec=nouv;
  nouv->suiv=ldc->premier;
  ldc->premier=nouv;
}


void LDCInsererEnFin(LDC* ldc, int i, int j){
  CelluleLDC* nouv=creerCelluleLDC(i,j);
  nouv->prec=ldc->dernier;
  if (LDCVide(ldc)) 
    ldc->premier=nouv;
  else 
    ldc->dernier->suiv=nouv;
  nouv->suiv=NULL;
  ldc->dernier=nouv;
}

void LDCenleverCellule(LDC* ldc, CelluleLDC* c){
  CelluleLDC* precC=c->prec;
  CelluleLDC* suivC=c->suiv;
  if (precC==NULL) 
    ldc->premier=suivC;
  else 
    precC->suiv=suivC;
  if (suivC==NULL) 
    ldc->dernier=precC;
  else 
    suivC->prec=precC;
  free(c);
}

void LDCafficher(LDC* ldc){
 printf("Liste : ");
  CelluleLDC* cour= ldc->premier;
  while(cour != NULL) {
    printf("(%d,%d) ", cour->i, cour->j);
    cour=cour->suiv;
  }
  printf("\n");
}

void LDCdesalloue(LDC *ldc){
 CelluleLDC *cour,*prec;
  cour=ldc->premier;
  while(cour!=NULL){
    prec=cour;
    cour=cour->suiv;
    free(prec);
  }
  ldc->premier=NULL;
  ldc->dernier=NULL;

}
