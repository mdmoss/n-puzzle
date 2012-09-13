#include <stdio.h>
#include <assert.h>

#include "PQ.h"

int main (int argc, char * argv[]) {
    
    int a1[4] = {1,2,3,BLANK};
    int a2[4] = {1,2,BLANK,3};
    
    Board b1 = makeBoard (a1, 2);
    Board b2 = makeBoard (a2, 2);

    State s1 = makeState (b1, NO_PARENT, 23, 42);
    State s2 = makeState (b2, s1, 1, 1);
    
    PQ testPQ = newPQ();
    
    addToPQ (testPQ, s1);
    addToPQ (testPQ, s1);
    addToPQ (testPQ, s1);
    addToPQ (testPQ, s1);
    addToPQ (testPQ, s1);
    addToPQ (testPQ, s1);
    addToPQ (testPQ, s1);
    addToPQ (testPQ, s1);
    addToPQ (testPQ, s1);
    addToPQ (testPQ, s1);
    addToPQ (testPQ, s1);
    addToPQ (testPQ, s1);
    addToPQ (testPQ, s2);
    assert (popPQ (testPQ) == s2);
    assert (popPQ (testPQ) == s1);
    disposePQ (testPQ);
    
    testPQ = newPQ();
    
    assert (isEmpty (testPQ) == TRUE);

    addToPQ (testPQ, s1);
    addToPQ (testPQ, s2);
    addToPQ (testPQ, s1);
    addToPQ (testPQ, s1);
    addToPQ (testPQ, s1);
    addToPQ (testPQ, s1);
    addToPQ (testPQ, s1);
    addToPQ (testPQ, s1);
    assert (isEmpty (testPQ) == FALSE);
    
    assert (popPQ (testPQ) == s2);
    assert (popPQ (testPQ) == s1);
    assert (popPQ (testPQ) == s1);
    assert (popPQ (testPQ) == s1);
    assert (popPQ (testPQ) == s1);
    
    assert (isEmpty (testPQ) == FALSE);
    
    assert (popPQ (testPQ) == s1);
    assert (popPQ (testPQ) == s1);
    assert (popPQ (testPQ) == s1);
    
    assert (isEmpty (testPQ) == TRUE);

    disposePQ (testPQ);

    disposeState (s1);
    disposeState (s2);
    
    // Begin PQ stress test
    
    State all[100];
    
    PQ stress = newPQ();
    
    int i;
    for (i = 0; i < 100; i++) {
    
        all[i] = makeState (b1, NO_PARENT, i, i);
        addToPQ (stress, all[i]);
    }
    
    for (i = 0; i < 100; i++) {\
    
        assert (popPQ (stress) == all[i]);
    
    }

    printf ("PQ ADT passed all tests\n");
    
    return 0;
}
