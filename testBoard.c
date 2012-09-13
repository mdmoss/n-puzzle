/*
 * testBoard.c
 *
 * Matthew Moss, mdmo552
 * Thu13Harp, Tutor: Kitten Tofu
 * 1/10/2011
 * 
 * Tester for a board ADT
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Board.h"

void compareTest (void);
void manhattanCostTest (void);
void outOfPlaceCostTest (void);
void disorderTest (void);

int main (int argc, char * argv[]) {

    int contentsT[9] = {1,2,3,4,5,6,7,8,BLANK};
    Board t = makeBoard (contentsT, 3);
 
    disposeBoard (t);
 
    compareTest();
 
    outOfPlaceCostTest();
    
    manhattanCostTest();
    
    disorderTest();
    
    printf ("Board ADT passed all tests\n");
    
    return EXIT_SUCCESS;
}

void compareTest (void) {

    int contentsA[] = {1,2,3,4};
    Board a = makeBoard (contentsA, 2);
    
    int contentsB[] = {1,2,3,4};
    Board b = makeBoard (contentsB, 2);

    int contentsC[] = {1,2,4,3};
    Board c = makeBoard (contentsC, 2);
    
    assert (compareBoards (a, b) == TRUE);
    assert (compareBoards (a, c) == FALSE);
}

void outOfPlaceCostTest (void) {
    
    int contentsA[9] = {1,1,1,1,1,1,1,1,1};
    Board a = makeBoard (contentsA, 3);
    
    int contentsB[9] = {9,9,9,9,9,9,9,9,9};
    Board b = makeBoard (contentsB, 3);
 
    int contentsC[9] = {1,2,1,2,1,2,1,2,1};
    Board c = makeBoard (contentsC, 3);
 
    assert (outOfPlaceCost (a, b) == 9);
    assert (outOfPlaceCost (a, c) == 4);
 
    disposeBoard (a);
    disposeBoard (b);
    disposeBoard (c);
}

void manhattanCostTest (void) {

    int contentsI[4] = {1,2,3,BLANK};
    Board i = makeBoard (contentsI, 2);
    
    int contentsJ[4] = {1,2,BLANK,3};
    Board j = makeBoard (contentsJ, 2);
    
    assert (manhattanCost (i, j) == 1);
 
    int contentsK[4] = {BLANK,1,2,3};
    Board k = makeBoard (contentsK, 2);
    
    assert (manhattanCost (i, k) == 4);
    
    disposeBoard (i);
    disposeBoard (j);
    disposeBoard (k);

}

void disorderTest (void) {

    int contentsA[9] = {1,2,3,4,5,6,7,8,BLANK};
    Board a = makeBoard (contentsA, 3);
    
    assert (disorder (a) == 0);
    
    int contentsB[9] = {BLANK,8,7,6,5,4,3,2,1};
    Board b = makeBoard (contentsB, 3);
    
    assert (disorder (b) == 28);
    
    int contentsC[9] = {1,8,2,7,BLANK,3,6,4,5};
    Board c = makeBoard (contentsC, 3);
    
    assert (disorder (c) == 12);

    int contentsD[9] = {1,2,3,4,5,6,7,8,BLANK};
    Board d = makeBoard (contentsD, 3);
    
    int contentsE[9] = {1,2,3,4,5,6,7,BLANK,8};
    Board e = makeBoard (contentsE, 3);
    
    assert (disorder (d) % 2 == disorder (e) % 2);
    
    disposeBoard (a);
    disposeBoard (b);
    disposeBoard (c);
    disposeBoard (d);
    disposeBoard (e);
    
}