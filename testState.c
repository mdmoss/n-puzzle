/*
 * testState.c
 *
 * Matthew Moss, mdmo552
 * Thu13Harp, Tutor: Kitten Tofu
 * 21/10/2011
 * 
 * Tester for a state ADT
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "State.h"
#include "Board.h"

int main (int argc, char * argv[]) {

    int a1[4] = {1,2,3,BLANK};
    int a2[4] = {1,2,BLANK,3};
    
    Board b1 = makeBoard (a1, 2);
    Board b2 = makeBoard (a2, 2);

    State s1 = makeState (b1, NO_PARENT, 23, 42);
    State s2 = makeState (b2, s1, 24, 50);
    
    assert (getCostFromStart (s2) == 24);
    assert (getHeuristicCost (s2) == 50);
    
    State r1 = generateSolution (s2);
    
    assert (compareBoards (getBoard (r1), b1) == 1);
    
    State r2 = getNext (r1);
    
    assert (getNext (r2) == NULL);
    
    assert (compareBoards (getBoard (r2), b2) == 1);
    
    disposeSolution (r1);
    
    disposeState (s1);
    disposeState (s2);
    
    printf ("State ADT passed all tests\n");
    
    return EXIT_SUCCESS;
}