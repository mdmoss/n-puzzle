#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "Puzzle.h"

void twoByTwoTestManhat (void);
void twoByTwoTestOOP (void);

int main (int argc, char * argv[]) {

    twoByTwoTestManhat();
    twoByTwoTestOOP();

    printf ("Puzzle ADT passed all tests\n");
    
    return EXIT_SUCCESS;
}

void twoByTwoTestManhat (void) {

    int goal[4] = {1,2,3,BLANK};
    int pos6[4] = {1,2,BLANK,3};
    int pos5[4] = {BLANK,2,1,3};
    int pos4[4] = {2,BLANK,1,3};
    int pos3[4] = {2,3,1,BLANK};
    int pos2[4] = {2,3,BLANK,1};
    int pos1[4] = {BLANK,3,2,1};

    Puzzle a = newPuzzle (goal, goal, 4, 'm');
    Puzzle b = newPuzzle (pos6, goal, 4, 'm');
    Puzzle c = newPuzzle (pos5, goal, 4, 'm');
    Puzzle d = newPuzzle (pos4, goal, 4, 'm');
    Puzzle e = newPuzzle (pos3, goal, 4, 'm');
    Puzzle f = newPuzzle (pos2, goal, 4, 'm');
    Puzzle g = newPuzzle (pos1, goal, 4, 'm');
    
    assert (solveable (a));
    assert (solveable (b));
    assert (solveable (c));
    assert (solveable (d));
    assert (solveable (e));
    assert (solveable (f));
    assert (solveable (g));
    
    solve (a);
    solve (b);
    solve (c);
    solve (d);
    solve (e);
    solve (f);
    solve (g);
    
    assert (solutionLength (a) == 0);
    assert (solutionLength (b) == 1);
    assert (solutionLength (c) == 2);
    assert (solutionLength (d) == 3);
    assert (solutionLength (e) == 4);
    assert (solutionLength (f) == 5);
    assert (solutionLength (g) == 6);
    
    disposePuzzle (a);
    disposePuzzle (b);
    disposePuzzle (c);
    disposePuzzle (d);
    disposePuzzle (e);
    disposePuzzle (f);
    disposePuzzle (g);
}

void twoByTwoTestOOP (void) {

    int goal[4] = {1,2,3,BLANK};
    int pos6[4] = {1,2,BLANK,3};
    int pos5[4] = {BLANK,2,1,3};
    int pos4[4] = {2,BLANK,1,3};
    int pos3[4] = {2,3,1,BLANK};
    int pos2[4] = {2,3,BLANK,1};
    int pos1[4] = {BLANK,3,2,1};

    Puzzle a = newPuzzle (goal, goal, 4, 'p');
    Puzzle b = newPuzzle (pos6, goal, 4, 'p');
    Puzzle c = newPuzzle (pos5, goal, 4, 'p');
    Puzzle d = newPuzzle (pos4, goal, 4, 'p');
    Puzzle e = newPuzzle (pos3, goal, 4, 'p');
    Puzzle f = newPuzzle (pos2, goal, 4, 'p');
    Puzzle g = newPuzzle (pos1, goal, 4, 'p');
    
    assert (solveable (a));
    assert (solveable (b));
    assert (solveable (c));
    assert (solveable (d));
    assert (solveable (e));
    assert (solveable (f));
    assert (solveable (g));
    
    solve (a);
    solve (b);
    solve (c);
    solve (d);
    solve (e);
    solve (f);
    solve (g);
    
    assert (solutionLength (a) == 0);
    assert (solutionLength (b) == 1);
    assert (solutionLength (c) == 2);
    assert (solutionLength (d) == 3);
    assert (solutionLength (e) == 4);
    assert (solutionLength (f) == 5);
    assert (solutionLength (g) == 6);
    
    disposePuzzle (a);
    disposePuzzle (b);
    disposePuzzle (c);
    disposePuzzle (d);
    disposePuzzle (e);
    disposePuzzle (f);
    disposePuzzle (g);
}