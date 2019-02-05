#ifndef __GRAPH_H__
#define __GRAPH_H__

#include"Grille.h"
#include "ListeDC.h"
#include "LCircuit.h"
#include "Solution.h"

typedef struct sommet Sommet;

typedef struct arete {
  struct sommet *succ;
  struct arete *suiv;
} Arc;

struct sommet{
  int i,j;
  Arc *Lsucc;
  int visit;
};


typedef struct{
  int n,m;
  Sommet *** Tsom;
} Graphe;

void Graphe_init(Graphe *H, int m, int n);

void Graphe_ajout_arc(Graphe *H, int i1, int j1, int i2, int j2);
void Graphe_Initialiser_Sommets(Graphe *H);
void Graphe_creation(Grille *G, Graphe *H);

void Graphe_affiche(Graphe *H);
int Rech_Circuit_rec(Graphe *H, Cell_circuit* lc, int i, int j, int i_cour, int j_cour);
void Graphe_Rech_Circuit_rec(Graphe *H, Lcircuit* lc);
Cell_circuit* Rech_circuit_ite ( Graphe *G , int i ,int j );
Lcircuit *Graphe_rech_circuit(Graphe *G);
Cell_char * Ajout_action_apres_c( Solution * S , Cell_char *c , int j, char a, Cell_char** Tref);
void Ajout_circuit_dans_solution(Cell_circuit *Circ, Solution* S, Cell_char** Tref, int* Jdroite);
Cell_char* pluscourtchemin_apres_c_ite( Solution * S , Cell_char *c , int j, int l, Cell_char** Tref);
void algorithme_circuit_CasLigne1x1(Grille *G , Solution *S);
#endif
