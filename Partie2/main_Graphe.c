#include "Grille.h"
#include "Graphe.h"
#include "stdio.h"
#include "stdlib.h"

void menu()
{
  printf("==================== MENU SORTING ROBOT: Solveur avec Graphe ====================\n");
  printf("1 : afficher le graphe\n");
  printf("2 : afficher le graphe et les circuits de permutations\n");
  printf("3 : Algorithme de Daniel Graf\n");
  printf("Entrez votre choix [1-3] : \n");
}
int main(int argc, char* *argv){
    Grille G;
    Solution S;
    int graine, choix;
    Solution_init(&S);
    if(argc!=5){
        printf("Format: <nb_lignes> <nb_colonnes> <nb_couleurs> <graine>\n");
        return 1;
    }

    G.m=atoi(argv[1]);
    G.n=atoi(argv[2]);
    G.nbcoul=atoi(argv[3]);
    graine=atoi(argv[4]);

    if (G.m > G.n){
        printf("Il doit y avoir plus de colonnes que de lignes\n");
        exit(1);
    }
    
    if (G.nbcoul > G.m*G.n){
        printf("Il ne doit pas y avoir plus de couleurs que de cases\n");
        exit(1);
    }

    

    
    Grille_allocation(&G);
    Gene_Grille(&G,graine);
    Graphe *H = (Graphe*) malloc(sizeof(Graphe));
    if(H == NULL ){
        fprintf(stderr, "erreur lors de l'allocation du graphe\n ");
        exit(1);
    }
    Graphe_init(H, G.m, G.n);
    Graphe_creation(&G, H);
    menu();
    scanf(" %d",&choix);
    while(choix<1 || choix>4){
            printf("chiffre incorrect. Veuillez en saisir un autre :\n");
            menu();
            scanf(" %d",&choix);
        }
    switch(choix){
            case 1: 
                printf("affichage du graphe:\n");
                Graphe_affiche(H);
                break;
            case 2:
                printf("affichage du graphe et des circuits de permutations\n");
                Graphe_affiche(H);
                Lcircuit* lc = (Lcircuit *) calloc(1, sizeof(Lcircuit));
                LCInitialise(lc);
                if (lc == NULL) {
                fprintf(stderr, "la liste de circuits n'a pas ete allouee\n");
                exit(1);
                }
                printf("Circuits: \n");
                Graphe_Rech_Circuit_rec(H,lc);
                LCAfficher(lc);
                break;
            case 3:  
                algorithme_circuit_CasLigne1x1(&G , &S);
                printf("l'Algorithme de Daniel Graf a été effectué avec succès!\n");
                Ecriture_Disque(G.m , G.n , G.nbcoul , graine , &S);
                break;
            
    }

    return 0;
}
