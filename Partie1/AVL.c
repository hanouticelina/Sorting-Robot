#include "AVL.h"

AVL* creerNoeud(int content, AVL* fg, AVL* fd){
    AVL* n = (AVL*) malloc(sizeof(AVL));
    if(n == NULL) 
    {
        fprintf( stderr , " erreur d'allocation \n ");
        return NULL;
    }
    n->content = content;
    n->fg = fg;
    n->fd = fd;
    majHauteur(n);
    return n;
}

int hauteur(AVL* avl){
    if (avl == NULL) return -1;
    else
        return avl->hauteur;
    
}

void hauteurFils(AVL* avl, int* hg, int*hd){
    if(avl == NULL){ //si l'AVL est NULL
        *hg = -1;
        *hd = -1;
        return;
    }
    *hg = hauteur(avl->fg);
    *hd = hauteur(avl->fd);
}

void majHauteur(AVL* avl){
    
  if (avl == NULL) return;

  int hg, hd;
  hauteurFils(avl, &hg, &hd);
  avl->hauteur = 1 + (hg > hd ? hg : hd);
}

AVL* rotDroite(AVL* rac){

    AVL* nvrac = rac->fg;
    rac->fg = nvrac->fd;
    nvrac->fd = rac;

    majHauteur(rac);
    majHauteur(nvrac);

    return nvrac;
}

AVL* rotGauche(AVL* rac){

    AVL* nvrac = rac->fd;
    rac->fd = nvrac->fg;
    nvrac->fg = rac;

    majHauteur(rac);
    majHauteur(nvrac);
    
    return nvrac;

}

AVL* doubleRotDroite(AVL * rac){
    rac->fg = rotGauche(rac->fg);
    majHauteur(rac);

    return rotDroite(rac);
}

AVL* equilibrer(AVL* avl){

    if(avl == NULL) return NULL;
    int HG,HD;// HG hauteur du fils gauche
    int fils_hg, fils_hd; // hd , hg hauteur des fils d'un fils
    hauteurFils(avl, &HG,&HD);

    if(HG - HD == 2){
        hauteurFils(avl->fg,&fils_hg,&fils_hd);

        if(fils_hg < fils_hd) avl->fg = rotGauche(avl->fg);
        
        avl = rotDroite(avl);
    }
    if(HG - HD == -2){
        hauteurFils(avl->fd,&fils_hg,&fils_hd);
        if(fils_hd < fils_hg) avl->fd  = rotDroite(avl->fd);

        avl = rotGauche(avl); 
    }
    return avl;

}
void AVLdesalloue(AVL* avl){

    if(avl == NULL) return;
    AVLdesalloue(avl->fg);
    AVLdesalloue(avl->fd);
    free(avl);
}

AVL* insererNoeud(AVL* avl, int val){
    if(!avl){
        avl = creerNoeud(val , NULL , NULL);
        return avl;
    }
    if ( val > avl->content ) // On ajoute la valeur dans le fils droit si la valeur est plus grande que celle de la racine  
        avl->fd = insererNoeud(avl->fd , val);
    else  
        avl->fg = insererNoeud(avl->fg , val); // on l'ajoute dans le fils gauche sinon
    avl = equilibrer(avl);
    return avl;
}

AVL* supprimeNoeud(AVL* avl, int val){
    if( avl ){
        if ( val > avl->content ) // Si la valeur est dans le sous-arbre droit
            avl->fd = supprimeNoeud(avl->fd , val);
        else if( val < avl->content) // Si la valeur est dans le sous-arbre gauche
            avl->fg = supprimeNoeud(avl->fg , val);
        else{ // si il n'y a pas de fils gauche, 
            if ( avl->fg ) 
                avl->content = supprimerMaxArbre(&avl->fg);
            else{
                AVL *temp = avl;
                avl = avl->fd;
                free(temp);
            }
        }
        return avl;
    }
    else    
        return NULL;
}

int supprimerMaxArbre(AVL **avl){
    AVL *cur = *avl , *temp , *pere = NULL;
    int max = 0;
    while (cur){
        if ( !cur->fd ){
            max = cur->content;
            temp = cur->fg;
            if ( pere )
                pere->fd = cur->fg;
            else   
                *avl = cur->fg;
            free(cur);
            pere = equilibrer(pere);
            majHauteur(pere);
            return max;
        }
        pere = cur;
        cur = cur->fd;
    }
    fprintf(stderr , " arbre infini à droite !");
    return 0;
}

AVL *rechercheNoeud(AVL *avl , int val){
    if ( avl ){
        if ( val > avl->content )
            rechercheNoeud(avl->fd , val);
        else if ( val < avl->content )
            rechercheNoeud(avl->fg , val);
        else
            return avl;
    }
    else
        return NULL;
}

void afficherAVL(AVL *avl){
    if (avl ){
        afficherAVL(avl->fd);
        printf("- %d -\n" , avl->content);
        afficherAVL(avl->fg);
    }
}


AVL*** init_matriceAVL ( int nb_coul , int nb_lignes ){
    AVL ***M = malloc(sizeof(AVL**) * nb_coul);
    if ( M == NULL)  {
        fprintf(stderr , " erreur allocation !!!!!\n");
        return NULL;
    }
    int i = 0 , j = 0 ;
    for ( i = 0 ; i < nb_coul ; i++){
        M[i] = malloc(sizeof(AVL*) * nb_lignes);
        if ( M[i] ){
            for ( j = 0 ; j < nb_lignes ; j++ )
                M[i][j] = (AVL*)malloc(sizeof(AVL));
        }
        else {
            for ( j = 0 ; j  < i ; j++)
                free(M[j]);
            free(M);
            return NULL;
        }
    }
   return M;
}
//recherche le noeud ayant une valeur j tq |valeur -j| soit minimal
void recherche_procheAVL(AVL *arbre , int valeur , int *j){
    
    if(arbre == NULL){
        fprintf(stderr, "arbre NULL\n");
        return;
    }
    AVL *cour = arbre ;
    int min = abs(valeur - cour->content);
  
    *j = cour->content;
    while (cour){
        /*si la valeur est plus petite que la valeur du noeud courant,
        on continue la recherche dans le fils gauche*/ 
        if ( cour->content > valeur )
            cour = cour->fg;
        /*si la valeur est plus grande que la valeur du noeud courant,
        on continue la recherche dans le fils droit*/ 
        else if ( cour->content < valeur)
            cour = cour->fd;
        /*sinon on recupère la valeur du noeud courant*/
        else {
            *j = cour->content;
            break;
        }
        /* on teste si "la distance" entre la valeur du noeud courant et la valeur passée en parametre 
        est plus petite que le minimum (on cherche a minimiser la distance entre valeur et j) */
        if ( cour )
            if ( abs(cour->content - valeur) < min){
                min = abs(cour->content - valeur);
                *j = cour->content;
            }
    }
}

