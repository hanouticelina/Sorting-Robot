
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX 100000
#include "AVL.h"

int main(int argc, char** argv){

    if(argc != 2){
        fprintf(stderr,"format : ./avl_test <nb_tests> \n");
        return 0;
    }
    int j = 0 ,i = 0, val = 0 ,nb_elements = atoi(argv[1]);
    char operation[] = { 'a' , 's' , 'r' };
    AVL *avl = NULL;
    while(i < nb_elements){
        j = rand() % 3 ;
        printf("oper : %c \t \n ", operation[j]);
        val = rand() % MAX; 
       // if ( operation[j] == 'a' )
            avl = insererNoeud(avl , i);
        /*else if ( operation[j] == 's')
            avl = supprimeNoeud(avl , val);
        else {  
            if ( rechercheNoeud(avl , val) != NULL )
                printf("la valeur %d  existe \n" , val);
            else   
                printf("la valeur %d n'existe pas! \n", val);
        }*/
        i++;
    }
    afficherAVL(avl);
    avl = supprimeNoeud(avl , 14);
    avl = supprimeNoeud(avl , 5);
    afficherAVL(avl);
    return 0;
}
