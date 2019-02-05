#ifndef __LISTE_CIRCUIT__
#define __LISTE_CIRCUIT__

#include <stdio.h>
#include <stdlib.h>
#include "ListeDC.h"

typedef struct cell_circuit {
  LDC *L;
  int jmin, jmax , imin , imax ;
  struct cell_circuit *suiv;
  struct cell_circuit *prec;
} Cell_circuit;

typedef struct {
  int nb_circuit;
  Cell_circuit *premier;
  Cell_circuit *dernier;
} Lcircuit;

Cell_circuit *LCCreerCellule(LDC *L, int jmin, int jmax , int imin , int imax);
void LCInitialise(Lcircuit *lc);
int LCVide(Lcircuit *lc);
void LCInsererEnTete(Lcircuit* lc, LDC *L, int jmin, int jmax , int imin , int imax);
void LCInsererEnFin(Lcircuit *lc, LDC *L, int jmin, int jmax , int imin , int imax);
void LCEnleverCellule(Lcircuit *lc, Cell_circuit *cel);
void LCDesalloue(Lcircuit *lc);
void LCAfficher(Lcircuit *lc);
void LCSupprimerCellule(Lcircuit *lc, Cell_circuit *cell);
#endif