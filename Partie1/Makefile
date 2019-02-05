all: Game_SortingRobot Checker_SortingRobot main_auPlusProche test_avl

entree_sortie.o: entree_sortie.c entree_sortie.h
	gcc -c entree_sortie.c

Solution.o: Solution.c Solution.h entree_sortie.h
	gcc -c Solution.c -g

Grille.o: Grille.c Grille.h Solution.h
	gcc -c Grille.c -g

API_AffGrille.o: API_AffGrille.c API_AffGrille.h Grille.h
	gcc -c API_AffGrille.c

Game_SortingRobot.o: Game_SortingRobot.c Grille.h API_AffGrille.h Solution.h 
	gcc -c Game_SortingRobot.c 

Game_SortingRobot: Game_SortingRobot.o API_AffGrille.o Grille.o Solution.o entree_sortie.o
	gcc -o Game_SortingRobot Game_SortingRobot.o API_AffGrille.o Grille.o Solution.o entree_sortie.o -lSDL

Checker_SortingRobot.o: Checker_SortingRobot.c Grille.h API_AffGrille.h Solution.h
	gcc -c Checker_SortingRobot.c

Checker_SortingRobot: Checker_SortingRobot.o  API_AffGrille.o Grille.o Solution.o entree_sortie.o
	gcc -o Checker_SortingRobot Checker_SortingRobot.o  API_AffGrille.o Grille.o Solution.o entree_sortie.o -lSDL

LDC.o : LDC.c
	gcc -c LDC.c -g

auPlusProche.o : auPlusProche.c 
	gcc -c auPlusProche.c -g 

AVL.o : AVL.c
	gcc -c AVL.c -g

AVL_test.o : AVL_test.c 
	gcc -c AVL_test.c

main_auPlusProche.o : main_auPlusProche.c
	gcc -c main_auPlusProche.c -g

test_avl : AVL.o AVL_test.o
	gcc -o test_avl AVL.o AVL_test.o

main_auPlusProche : main_auPlusProche.o auPlusProche.o Solution.o Grille.o  entree_sortie.o LDC.o AVL.o
	gcc -o main_auPlusProche main_auPlusProche.o auPlusProche.o Solution.o Grille.o entree_sortie.o AVL.o LDC.o -g

clean:
	rm -f *.o Game_SortingRobot Checker_SortingRobot main_auPlusProche test_avl Courbe
