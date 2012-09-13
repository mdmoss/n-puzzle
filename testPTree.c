/*
 * testPTree.c
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

#include "Board.h"
#include "State.h"
#include "PTree.h"

int main (int argc, char * argv[]) {

    int a1[4] = {1,2,3,BLANK};
    int a2[4] = {1,2,BLANK,3};
    
    Board b1 = makeBoard (a1, 2);
    Board b2 = makeBoard (a2, 2);

    State s1 = makeState (b1, NO_PARENT, 23, 42);
    State s2 = makeState (b2, s1, 24, 50);

    PTree p = newPTree (4);
    
    assert (inPTree (p, b1) == NULL);
    
    addToPTree (p, s1);
    
    assert (inPTree (p, b1) == s1);
    
    assert (inPTree (p, b2) == NULL);
    
    addToPTree (p, s2);
    
    assert (inPTree (p, b2) == s2);
    
    disposePTree (p);
    
    printf ("PTree ADT passed all tests\n");
    
    return EXIT_SUCCESS;
}