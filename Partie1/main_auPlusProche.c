#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Solution.h"
#include "Grille.h"
#include <math.h>
#include <time.h>
#include "auPlusProche.h"

void menu()
{
  printf("==================== MENU SORTING ROBOT ====================\n");
  printf("1 : Algorithme naif\n");
  printf("2 : Algorithme Circulaire\n");
  printf("3 : Algorithme Par couleur\n");
  printf("4 : Algorithme Par AVL\n");
  printf("Entrez votre choix [1-4] : \n");
}

int main(int argc , char **argv) {
    Solution s;
    Solution_init(&s);
    Grille G;
    
    clock_t temps_initial;
    clock_t temps_final;
    double temps_cpu = 0.0;
    int choix;
   
    if(argc != 5){
        printf("Format : <m> <n> <nbcoul> <graine>\n");
        return 1;
    }
    G.m=atoi(argv[1]);
    G.n=atoi(argv[2]);
    G.nbcoul=atoi(argv[3]);
    if (G.m > G.n){
        printf("Il doit y avoir plus de colonnes que de lignes\n");
        exit(1);
    }
    
    if (G.nbcoul > G.m*G.n){
        printf("Il ne doit pas y avoir plus de couleurs que de cases\n");
        exit(1);
    }


    Grille_allocation(&G);
    Gene_Grille(&G , atoi(argv[4]) );
    menu();
    scanf(" %d",&choix);
    while(choix<1 || choix>4){
            printf("chiffre incorrect. Veuillez en saisir un autre :\n");
            menu();
            scanf(" %d",&choix);
        }
    switch(choix){
            case 1: 
                temps_initial = clock();
                algorithme_naif(&G , &s);
                temps_final = clock();
                temps_cpu = ((double) (temps_final - temps_initial))/((double) CLOCKS_PER_SEC);
                printf("l'Algorithme naif a été effectué avec succès! duree : %7.5e\n", temps_cpu);
                break;
            case 2:
                temps_initial = clock();
                algorithme_circulaire(&G , &s);
                temps_final = clock();
                temps_cpu = ((double) (temps_final - temps_initial))/((double) CLOCKS_PER_SEC);
                printf("l'Algorithme circulaire a été effectué avec succès! duree : %7.5e\n", temps_cpu);
                break;
            case 3:  
                temps_initial = clock();
                algorithme_parcouleur(&G , &s);
                temps_final = clock();
                temps_cpu = ((double) (temps_final - temps_initial))/((double) CLOCKS_PER_SEC);
                printf("l'Algorithme par couleur a été effectué avec succès! duree : %7.5e\n", temps_cpu);
                break;
            case 4:
                temps_initial = clock();
                algorithme_AVL(&G , &s);
                temps_final = clock();
                temps_cpu = ((double) (temps_final - temps_initial))/((double) CLOCKS_PER_SEC);
                printf("l'Algorithme par AVL a été effectué avec succès! duree : %7.5e\n", temps_cpu);
                break;
    }
    Ecriture_Disque(G.m , G.n , G.nbcoul , atoi(argv[4]) , &s);
    Desallouer_Solution(&s);
    return 0;
}

