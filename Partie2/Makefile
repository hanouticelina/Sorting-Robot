all: Game_SortingRobot Checker_SortingRobot main_Graphe exo7

entree_sortie.o: entree_sortie.c entree_sortie.h
	gcc -c entree_sortie.c

Solution.o: Solution.c Solution.h entree_sortie.h
	gcc -c Solution.c

Grille.o: Grille.c Grille.h Solution.h
	gcc -c Grille.c

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

Graphe.o: Graphe.c Graphe.h Grille.h
	gcc -c Graphe.c -g
	
LCircuit.o : LCircuit.c 
	gcc -c LCircuit.c 	

ListeDC.o: ListeDC.c 
	gcc -c ListeDC.c

main_Graphe.o : main_Graphe.c 
	gcc -c main_Graphe.c -g

exo7.o : exo7.c 
	gcc -c exo7.c -g

exo7 : exo7.o Graphe.o Grille.o ListeDC.o LCircuit.o Solution.o entree_sortie.o
	gcc -o exo7 exo7.o Graphe.o Grille.o ListeDC.o LCircuit.o Solution.o entree_sortie.o

main_Graphe: main_Graphe.o Graphe.o Grille.o ListeDC.o LCircuit.o Solution.o entree_sortie.o
	gcc -o main_Graphe main_Graphe.o Graphe.o Grille.o ListeDC.o LCircuit.o Solution.o entree_sortie.o

clean:
	rm -f *.o Game_SortingRobot Checker_SortingRobot main_Graphe exo7
