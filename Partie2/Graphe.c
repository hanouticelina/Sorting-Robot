#include<stdlib.h>
#include"Graphe.h"
#include "Grille.h"
#include <math.h>
#include<stdio.h>


void Graphe_init(Graphe *H, int m, int n){
  int i,j;

  H->m=m;
  H->n=n;
  H->Tsom=(Sommet***)malloc(m*sizeof(Sommet**));
  for (i=0;i<m;i++){
    H->Tsom[i]=(Sommet**)malloc(n*sizeof(Sommet*));
    for (j=0;j<n;j++)
      H->Tsom[i][j]=(Sommet*)malloc(sizeof(Sommet));
  }

  for (i=0;i<m;i++)
    for (j=0;j<n;j++){
      H->Tsom[i][j]->i=i;
      H->Tsom[i][j]->j=j;
      H->Tsom[i][j]->Lsucc=NULL;
      H->Tsom[i][j]->visit=-1;
    }
  

}

void Graphe_ajout_arc(Graphe *H, int i1, int j1, int i2, int j2){
  Arc *a=(Arc*) malloc(sizeof(Arc));
  a->succ=H->Tsom[i2][j2];
  a->suiv=H->Tsom[i1][j1]->Lsucc;
  H->Tsom[i1][j1]->Lsucc=a;  
}


void Graphe_creation(Grille *G, Graphe *H){

  int i,j,k;
  CelluleLDC *cour1,*cour2;

  Graphe_init(H,G->m,G->n);

  LDC* TC=(LDC*) malloc(sizeof(LDC)*G->nbcoul);
  
  for (i=0;i<G->m;i++)
    for (j=0;j<G->n;j++)
      if (G->T[i][j].fond!=G->T[i][j].piece)
	LDCInsererEnTete(&TC[G->T[i][j].fond],i,j);

  for (k=0;k<G->nbcoul;k++){
    cour1=TC[k].premier;
    while(cour1!=NULL){
      cour2=TC[G->T[cour1->i][cour1->j].piece].premier;
      while (cour2!=NULL){
	Graphe_ajout_arc(H,cour1->i,cour1->j,cour2->i,cour2->j);
	cour2=cour2->suiv;
      }      
      cour1=cour1->suiv;
    }
  }
  
  for (k=0;k<G->nbcoul;k++)
    LDCdesalloue(&(TC[k]));
      
}


void Graphe_affiche(Graphe *H){
  int i,j;
  Arc *cour;

  printf("Graphe H :\n");
  for (i=0;i<H->m;i++)
    for (j=0;j<H->n;j++){
      printf("(%d,%d) ",i,j);
      if (H->Tsom[i][j]->Lsucc==NULL)
	printf(" noir\n");
      else{
	printf(" arc vers ");
	cour=H->Tsom[i][j]->Lsucc;
	while (cour!=NULL){
	  printf("(%d,%d) ", cour->succ->i, cour->succ->j);
	  cour=cour->suiv;
	}
	printf("\n");
      }

    }


}
/*--------------------------RECHERCHE CIRCUIT: VERSION RECURSIVE -----------------*/
int Rech_Circuit_rec(Graphe *H, Cell_circuit* lc, int i, int j, int i_cour, int j_cour)
{
  int k, l;
  Arc *cour = NULL;
  lc->jmin = j;
  lc->jmax = j;
  lc->imin = i;
  lc->imax = i;
  H->Tsom[i_cour][j_cour]->visit = 0;
  cour = H->Tsom[i_cour][j_cour]->Lsucc;
  while (cour != NULL) {
    k = cour->succ->i;
    l = cour->succ->j;
	  if(H->Tsom[k][l]->visit == -1 && Rech_Circuit_rec(H, lc, i, j, k, l)) {
        LDCInsererEnTete(lc->L, i_cour, j_cour);
        if (j_cour < lc->jmin) {
            lc->jmin = j_cour;
        }
        if (j_cour > lc->jmax) {
              lc->jmax = j_cour;
        }
         if ( i_cour > lc->imax)
            lc->imax = i_cour;
        else  
          if ( i_cour < lc->imin)
            lc->imin = i_cour ;
        return 1;
    }
    if (H->Tsom[k][l]->visit == 0 && k == i && l == j){
        LDCInsererEnTete(lc->L, i_cour, j_cour);
        return 1;    
    }
    cour = cour->suiv;
  }
  H->Tsom[i_cour][j_cour]->visit = 1;
  return 0;
}
void Graphe_Rech_Circuit_rec(Graphe *H, Lcircuit* lc){
  int i, j;
  for (i = 0; i < H->m; i++) {
    for (j = 0; j < H->n; j++) {  
      if (H->Tsom[i][j] == NULL) {
	        fprintf(stderr, "Un sommet n'a pas été alloue\n");
	        return;
      }
      
      if (H->Tsom[i][j]->Lsucc == NULL) 
	      H->Tsom[i][j]->visit = -2;
      
      else
        H->Tsom[i][j]->visit = -1;
      
    }
  } 
  for (i = 0; i < H->m; i++) {
    for (j = 0; j < H->n; j++) { 
      Cell_circuit *temp = malloc(sizeof(Cell_circuit));
      temp->L = malloc(sizeof(LDC));
      LDCInitialise(temp->L);
      if (temp == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation d'une cellule de circuit\n");
        return;
      }
      if ( H->Tsom[i][j]->visit == -1 && H->Tsom[i][j]->visit != -2 ) {
          Rech_Circuit_rec(H, temp, i, j, i, j);
          if(temp)
              LCInsererEnFin(lc, temp->L, temp->jmin, temp->jmax, temp->imin , temp->imax);
      }
      
    }
  }

}

/*-------------------------RECHERCHE CIRCUIT :VERSION ITERATIVE (uniquement pour le cas une case par couleur) --------------*/
Cell_circuit* Rech_circuit_ite ( Graphe *G , int i ,int j ){
  //on parcourt tout les sommets d'un circuit et on les affiche un apres un

  Cell_circuit *temp = malloc(sizeof(Cell_circuit));
  temp->L = malloc(sizeof(LDC));
  LDCInitialise(temp->L);
  
  if ( !temp ) return NULL;
  temp->jmin = j;
  temp->jmax = j;
  temp->imin = i;
  temp->imax = i;
  if ( !G ) return NULL;

  G->Tsom[i][j]->visit = 0;
  Arc *cour = G->Tsom[i][j]->Lsucc ;
  LDCInsererEnTete(temp->L , i , j);
  while  ( cour ){
    if ( j > temp->jmax)
      temp->jmax = j;
    else 
      if (j < temp->jmin) 
        temp->jmin = j;
    if ( i > temp->imax)
      temp->imax = i;
    else  
      if ( i < temp->imin)
        temp->imin = i ;
    cour->succ->visit = 0;
    if( cour->succ->i == i && cour->succ->j == j)
        return temp;
    LDCInsererEnFin(temp->L , cour->succ->i, cour->succ->j);
    cour = cour->succ->Lsucc;
    // on sait qu'on est dans un cas nb_coul = n*n
  }
  if ( G->Tsom[i][j]->visit == -2 ) //case noire
    fprintf(stderr ," erreur dans la detection de circuits!\n");
  return NULL;
}


Lcircuit *Graphe_rech_circuit(Graphe *G){
  Lcircuit *lcir = malloc(sizeof(Lcircuit));
  LCInitialise(lcir);
  Cell_circuit *temp = NULL;
  int i = 0 , j = 0;
  int k;
  for (i = 0; i < G->m; ++i) {
    for (j = 0; j < G->n; ++j) {  
      if (G->Tsom[i][j] == NULL) {
          fprintf(stderr, "Erreur lors de l'allocation du sommet : (%d,%d)\n", i, j);
	        return NULL;
      }
      if (G->Tsom[i][j]->Lsucc == NULL)
	      G->Tsom[i][j]->visit = -2;
      else
        G->Tsom[i][j]->visit = -1;

    }
  }
  for ( i = 0 ; i  < G->m ; i++)
    for ( j = 0 ; j < G->n ; j++){
      if ( G->Tsom[i][j]->visit == -1 && G->Tsom[i][j]->visit != -2 ){
          temp = Rech_circuit_ite(G , i , j);
          if (temp)
            LCInsererEnFin(lcir , temp->L , temp->jmin ,temp->jmax , temp->imin , temp->imax); 
      }
    }
  
  return lcir;
}


Cell_char * Ajout_action_apres_c( Solution * S , Cell_char *c , int j, char a, Cell_char** Tref){
  Cell_char *temp_c = malloc(sizeof ( Cell_char)) , *save_c = NULL ;
  temp_c->a = a ;
  temp_c->suiv = NULL;
  if ( c ){
    save_c = c->suiv;
    c->suiv = temp_c;
    temp_c->suiv = save_c;
  }
  else {
    if ( !S ){
      fprintf(stderr ,  "erreur dans l'initialisation de la solution \n");
      return NULL;
    }
    S->prem = temp_c;
    S->dern = temp_c; 
  }
  S->cptr_pas++; 
  Tref[j] = temp_c ;
  return temp_c;
}

Cell_char* pluscourtchemin_apres_c_ite( Solution * S , Cell_char *c , int j, int l, Cell_char** Tref){
    int r = 0;
    Cell_char* cell = c;
    if ( l < j )
        for ( r = j ; r != l ; r--){
            cell = Ajout_action_apres_c(S,c,r-1,'L',Tref);
            c = cell;
        }
    if ( l > j )
        for ( r = j ; r != l ; r++){
            cell = Ajout_action_apres_c(S,c,r+1,'R',Tref);
            c = cell;
        }
    return cell;
}

void Ajout_circuit_dans_solution(Cell_circuit *Circ, Solution* S, Cell_char** Tref, int* Jdroite){
  
  if ( !S ){
    fprintf(stderr, "Solution non initialisée\n");
    return;
  }
  int j = 0,l = 0;
  Cell_char* cell = Tref[Circ->jmin];
  CelluleLDC *cour = Circ->L->premier , *temp = NULL;
  if ( !cour ) return ;
  temp = cour->suiv;
   if ( cell->a != 'S') //chaque sequence correspondant a un circuit doit commencer par un swap
      cell = Ajout_action_apres_c(S, cell, cour->j, 'S', Tref);
  if (Circ->jmax > *Jdroite)
    *Jdroite = Circ->jmax;
  while ( temp ){
    l = temp->j;
    j = cour->j;
  
    cell = pluscourtchemin_apres_c_ite(S , cell , j , l , Tref );
    cell = Ajout_action_apres_c(S , cell , l , 'S' , Tref);
    cour = temp;
    temp = temp->suiv;
  }
  j = l; //on traite la dernière arete du circuit
  l = Circ->L->premier->j;
  cell = pluscourtchemin_apres_c_ite(S , cell , j , l , Tref );
  cell = Ajout_action_apres_c(S , cell , l , 'S' , Tref);
  
}

/*----------------------------- ALGORITHME DE DANIEL GRAF----------------------*/

void algorithme_circuit_CasLigne1x1(Grille *G , Solution *S){
  int Jdroite = 0 , Jdroite_sav = 0 , drap = 0 ;
  ///creation du graphe et des circuits
  Graphe H;
  Cell_char *cell = NULL;
  Graphe_init(&H, G->m, G->n);
  Graphe_creation(G, &H);
  Lcircuit *lc  = Graphe_rech_circuit(&H); //on detecte les circuits
  LCAfficher(lc);
  Cell_char **Tref = calloc(G->n , sizeof(Cell_char*));
  Cell_circuit *Circ = lc->premier;
  while ( Circ){
    if ( !Tref[Circ->jmin] ){  
      Jdroite_sav = Jdroite ;
      drap = 1;
      cell = pluscourtchemin_apres_c_ite(S , Tref[Jdroite] , Jdroite, Circ->jmin , Tref);
      Ajout_action_apres_c(S , cell , Circ->jmin , 'S' , Tref);
      if ( Circ->jmin > Jdroite) Jdroite = Circ->jmin; 
    }
    Ajout_circuit_dans_solution(Circ , S , Tref , &Jdroite);
    if ( drap == 1 ) {
      drap = 0;
      pluscourtchemin_apres_c_ite(S , Tref[Circ->jmin] , Circ->jmin , Jdroite_sav , Tref);
    }

    Circ = Circ->suiv;
  }
  free(Tref);
}



  
  







