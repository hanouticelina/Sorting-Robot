#include <stdlib.h>
#include <stdio.h>
#include "Solution.h"
#include "Grille.h"
#include <math.h>
#include <time.h>
#include "LDC.h"
#include "AVL.h"

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

int caseNoire( Grille *G , int i , int j){ //retourne 1 si la case est noire, 0 sinon
    if ( G->T[i][j].fond == G->T[i][j].piece)
        return 1;
    return 0;
}

int pieceNoir( Grille *G , int i , int j){ //retourne 1 si la case ne contient pas de piece, 0 sinon
    if ( G->T[i][j].piece == -1)
        return 1;
    return 0;
}
int robotPortePiece(Grille*G, int i, int j){ //retourne la couleur de la piece portée par le robot si il en porte, 0 sinon
    if(G->T[i][j].robot >= 0 )
        return G->T[i][j].robot;
    return 0;
}

/*  retourne  la  case  ( k,l)  de  couleur c qui  soit  
la  plus  proche  de  (i,j) au  sens  de l’algorithme “au plus proche” */
void RechercheCaseNaif_c(Grille* G, int c,int i, int j,int *k,int *l){
    int w = 0 , v = 0 , min = G->m + G->n; 
    for ( w = 0 ; w < G->m ; w ++)
        for ( v = 0 ; v < G->n ; v++){
            if ( G->T[w][v].fond == c && G->T[w][v].piece != c ){ // si la case est non noire et de couleur c
                if (abs(w-i) + abs(v-j) < min ){ //on cherche la distance minimum
                    min = abs(w-i) + abs(v-j);
                    *k = w;
                    *l = v;
                }

            }

        }
}

/*  retourne  la  case  ( k,l)  non-noire qui  soit  
la  plus  proche  de  (i,j) au  sens  de l’algorithme “au plus proche” */
void RechercheCaseNaif_nn(Grille* G,int i, int j,int *k,int *l){
    int w = 0 , v = 0 , min = G->m + G->n; 
    for ( w = 0 ; w < G->m ; w ++)
        for ( v = 0 ; v < G->n ; v++){
            if ( !caseNoire(G , w , v) && !pieceNoir(G , w , v) ){ // si la case est non noire
                if (abs(w-i) + abs(v-j) < min ){
                    min = abs(w-i) + abs(v-j);
                    *k = w;
                    *l = v;
                }

            }
        }
}

//version naive de l'algorithme
void algorithme_naif(Grille *G , Solution *S){
    int i = 0 , j = 0 , couleur = 0;
    while( G->cptr_noire < G->n * G->m ){
        if ( G->T[G->ir][G->jr].robot == -1 ) { // si le robot ne porte pas de piece
            RechercheCaseNaif_nn(G , G->ir, G->jr, &i , &j);
            plusCourtChemin(S , G->ir , G->jr , i , j);
            changement_case(G , i , j);
            couleur = G->T[G->ir][G->jr].piece ;
            swap_case(G);
            Ajout_action(S , 'S');
        }
        RechercheCaseNaif_c(G ,G->T[G->ir][G->jr].robot, G->ir , G->jr , &i , &j);  //on cherche la case la plus proche et ayant la meme couleur que la piece portée par le robot
        plusCourtChemin(S , G->ir , G->jr , i , j);
        changement_case(G , i , j );
        swap_case(G);
        Ajout_action(S , 'S');
        
        
    }
}



/*--------------------------VERSION CIRCULAIRE----------------------*/


/* version circulaire, elle retourne  la  case  ( k,l)  de  couleur c qui  soit  
la  plus  proche  de  (i,j) au  sens  de l’algorithme “au plus proche” */
void rechercheCaseCirculaire_c(Grille *G , int c , int i, int j  , int *k , int *l) {
    int rayon=0, ld =j , lg = j, w = i;
    while(rayon < G->m + G->n){
        ld = j;
        lg = j;
        w = i - rayon;
        while ( w <= i){
            if(w >= 0 &&  w < G->m  ){
                if(ld >= 0 && ld < G->n  )
                    if ( G->T[w][ld].fond == c && G->T[w][ld].piece != c){
                        *k=w;
                        *l=ld;
                        return;
                    }
                if ( lg < G->n && lg >= 0)
                    if ( G->T[w][lg].fond == c && G->T[w][lg].piece != c){
                        *k = w;
                        *l = lg;
                        return;
                    }
            }
            w++;
            lg--;
            ld++;
        }
        w = i+1;
        lg = j - rayon +1;
        ld = j+rayon-1;
          while (w >= 0 &&  w <= i + rayon){
            if( w < G->m ){
                if (ld < G->n && ld >= 0 )
                    if ( G->T[w][ld].fond == c && G->T[w][ld].piece != c){
                        *k=w;
                        *l=ld;
                        return;
                    }
                if ( lg >= 0 && lg < G->n)
                    if ( G->T[w][lg].fond == c && G->T[w][lg].piece != c){
                        *k = w;
                        *l = lg;
                        return;
                    }
            }
            w++;
            lg++;
            ld--;
        }
        rayon++;
    }
}

/* version circulaire, elle retourne  la  case  ( k,l)  non noire qui  soit  
la  plus  proche  de  (i,j) au  sens  de l’algorithme “au plus proche” */
void rechercheCaseCirculaire_nn(Grille *G ,int i, int j  , int *k , int *l){
     int rayon=1, ld =j , lg = j, w = i;
    while(rayon < G->m + G->n){
        ld = j;
        lg = j;
        w = i - rayon;
        while ( w <= i){
            if( w >= 0 && w < G->m ){
                if (ld >= 0 && ld < G->n)
                    if (!caseNoire(G , w , ld) && !pieceNoir(G , w , ld) ){
                        *k=w;
                        *l=ld;
                        return;
                    }
                if (lg >= 0 && lg < G->n)
                    if (!caseNoire(G , w , lg) && !pieceNoir(G , w , lg) ){
                        *k = w;
                        *l = lg;
                        return;
                    }
            }
            w++;
            lg--;
            ld++;
        }
        w = i+1;
        lg = j - rayon +1;
        ld = j+rayon-1;
          while ( w <= i + rayon){
            if( w >= 0 && w < G->m ){
                if ( ld < G->n && ld >= 0 )
                    if (!caseNoire(G , w , ld) && !pieceNoir(G , w , ld) ){
                        *k=w;
                        *l=ld;
                        return;
                    }
                if ( lg >= 0 && lg < G->n )
                    if ( !caseNoire(G , w , lg) && !pieceNoir(G , w , lg)){
                        *k = w;
                        *l = lg;
                        return;
                    }
            }
            w++;
            lg++;
            ld--;
        }
        rayon++;
    }
}

//version circulaire de l'algorithme
void algorithme_circulaire(Grille *G , Solution *S) {
    int i = 0 , j = 0 , couleur = 0;
    while( G->cptr_noire < G->n * G->m ){
        if(G->T[G->ir][G->jr].robot == -1){
            rechercheCaseCirculaire_nn(G , G->ir, G->jr, &i , &j);
            plusCourtChemin(S , G->ir , G->jr , i , j);
            changement_case(G , i , j);
            swap_case(G);
            Ajout_action(S , 'S');
        }
        rechercheCaseCirculaire_c(G ,G->T[G->ir][G->jr].robot, G->ir , G->jr , &i , &j);
        plusCourtChemin(S , G->ir , G->jr , i , j);
        changement_case(G , i , j );
        swap_case(G);
        Ajout_action(S , 'S');
    }
}

/*----------------------VERSION PAR COULEUR---------------------------------------------*/

void algorithme_parcouleur(Grille *G, Solution *S){
    LDC** TC = malloc(G->nbcoul* sizeof(LDC*));
    int i = 0 , j = 0 ;
    for ( i = 0 ; i < G->nbcoul ; i++){
        TC[i] = malloc(sizeof(LDC));
        TC[i]->premier = NULL;
        TC[i]->dernier = NULL;
    }
        
    for ( i = 0 ; i < G->m ; i++) //on insère les cases dans la liste chainée correspondante à sa couleur de fond
        for( j = 0; j < G->n ; j++)
            LDCInsererEnFin(&TC[G->T[i][j].fond],i,j);
        
    CelluleLDC *temp = NULL;
    G->ir = 0 ;
    G->jr = 0;
    while ( G->cptr_noire < G->n * G->m ) {
        if ( G->T[G->ir][G->jr].robot == -1 ){ //dans le cas ou le robot n'a pas de pièce
            rechercheCaseCirculaire_nn(G , G->ir , G->jr , &i , &j);
            plusCourtChemin(S , G->ir , G->jr , i , j);
            changement_case(G , i , j);
            swap_case(G);
            Ajout_action(S , 'S');
        }
        temp = LDCrechercherPlusProcheCase(TC[G->T[G->ir][G->jr].robot], G->ir , G->jr);  //on cherche la case la plus proche et ayant la meme couleur que la piece portée par le robot
        i = temp->i;
        j = temp->j;
        supprimerCell(TC[G->T[G->ir][G->jr].robot] , temp); //on supprime la cellule temp, pour qu'elle ne soit plus considérer accessible par le robot 
        plusCourtChemin(S , G->ir , G->jr , i , j);
        changement_case(G , i , j );
        swap_case(G);
        Ajout_action(S , 'S'); 
    }
    free(TC);
}

/*--------------VERSION AVEC AVL-------------------------*/

//Fonction qui crée la matrice d'AVL
AVL ***creation_matriceAVL( Grille * G ){
    int i = 0 , j = 0 ;
    AVL ***M = init_matriceAVL(G->nbcoul , G->m );
    for ( i = 0 ; i < G->m ; i++)
        for ( j = 0 ; j < G->n ; j++){
            M[G->T[i][j].fond][i] = insererNoeud(M[G->T[i][j].fond][i] , j);
        }
    return M;
}

//Fonction qui recherche la case la plus proche de (i,j)
void case_proche_AVL(AVL ***M , Grille *G ,int couleur ,  int i , int j , int *k , int *l){
    int s = 0 , min = G->m + G->n , w = 0 ;
    for ( s = 0 ; s < G->m ; s++ ){
        if ( M[couleur][s]){
            recherche_procheAVL(M[couleur][s] , j , &w);
            if (min > abs ( s - i) + abs(w - j) ){
                min = abs ( s - i) + abs(w - j);
                *k = s;
                *l = w; 
            }
        }
    }
}

//version par AVL
void algorithme_AVL(Grille *G , Solution *S){
    AVL ***M = creation_matriceAVL(G);
    if (M == NULL) {
    return;
    }
    int i = 0 , j = 0 , couleur = 0;
    while( G->cptr_noire < G->n * G->m ){
        if(G->T[G->ir][G->jr].robot == -1){ // si le robot ne porte pas de piece
            rechercheCaseCirculaire_nn(G , G->ir, G->jr, &i , &j); // on cherche la case la plus proche non noire
            plusCourtChemin(S , G->ir , G->jr , i , j);
            changement_case(G , i , j);
            swap_case(G);
            Ajout_action(S , 'S');
        }
        case_proche_AVL(M , G ,G->T[G->ir][G->jr].robot, G->ir , G->jr , &i , &j); //on cherche la case la plus proche et ayant la meme couleur que la piece portée par le robot
        M[G->T[G->ir][G->jr].robot][i] = supprimeNoeud(M[G->T[G->ir][G->jr].robot][i] , j); // on supprime le noeud car la case (i,j) ne doit plus être considéré accessible pour le robot
        plusCourtChemin(S , G->ir , G->jr , i , j);
        changement_case(G , i , j );
        swap_case(G);
        Ajout_action(S , 'S');
    }
    for (i = 0; i < G->nbcoul; ++i) {
         free(M[i]);
  }
  free(M);
 }

