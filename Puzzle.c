/*
 * Puzzle.c
 *
 * Matthew Moss, mdmo552
 * Thu13Harp, Tutor: Kitten Tofu
 * 4/10/2011
 *
 * ADT for an nxn puzzle.
 *
 * Note: Instead of open and closed sets, this implementation stores
 * an "expanded" status implicitly in a state. This is more efficient
 * than constantly looking up past states in an open set.
 *
 */
 
#include "Puzzle.h"

struct _puzzle {

    int length;
    int edgeLength;
    Board start;
    Board goal;
    char heuristic;
    
    State solution;
};

static int getHCost (Board current, Board goal, char heuristic);
static void handleMemoryError (void);

Puzzle newPuzzle (int * start, int * goal, int length, char heuristic) {

    Puzzle p = malloc (sizeof (struct _puzzle));
    if (p == NULL) {
        handleMemoryError();
    }
    
    p->length = length;
    p->edgeLength = sqrt (length);
    p->heuristic = heuristic;
    
    p->start = makeBoard (start, p->edgeLength);
    p->goal = makeBoard (goal, p->edgeLength); 
    
    p->solution = NULL;
    
    return p;
}

void printPuzzleInfo (Puzzle p) {

    printf ("start: ");
    printBoard (p->start);
    printf ("goal: ");
    printBoard (p->goal);
    
    if (p->heuristic == 'm') {
        printf ("manhattan\n");
    } else if (p->heuristic == 'p') {
        printf ("outofplace\n");
    }
}

int solveable (Puzzle p) {

    int ret = TRUE;
    
    if (disorder (p->start) % 2 != disorder (p->goal) % 2) {
    
        ret = FALSE;
    }

    return ret;
}

int solve (Puzzle p) {

    // Set of states and ordering
    PTree set = newPTree (p->length);
    PQ order = newPQ();

    // Starting state
    int firstH = getHCost (p->start, p->goal, p->heuristic);
    State check = makeState (copyBoard (p->start), NO_PARENT, 0, firstH);
    
    addToPTree (set, check);

    // And let the A* begin. We'll need these later
    int expansions = 0;
    Board * newBoard = malloc (sizeof (Board) * 4);

    while (!(compareBoards (getBoard (check), p->goal))) {
    
        State oldLoc = inPTree (set, getBoard (check));
        
        if (getCost (check) < getCost (oldLoc) || 
                                             !(beenExpanded (oldLoc))) {
        
            // Expand it, get the new boards
            int numNew = permute (getBoard (check), newBoard);
            expansions++;
            
            int i;
            for (i = 0; i < numNew; i++) {      
            
                State inSet = inPTree (set, newBoard[i]);
                if (inSet == NULL) {
                    
                    // Wow, new board. Coolio.
                    int hCost = getHCost (newBoard[i], p->goal, p->heuristic);
                    
                    State new = makeState (newBoard[i], check, 
                                   getCostFromStart (check) + 1, hCost);
                    
                    addToPTree (set, new);
                    addToPQ (order, new);
                    
                } else {
                
                    // Check the new cost
                    int newCost = getCostFromStart (check) + 1;
                
                    if (getCostFromStart (inSet) > newCost) {
                        // Again, here is cheaper. Yay
                        
                        setCostFromStart (inSet, newCost);
                        setParent (inSet, check);
                        addToPQ (order, inSet);
                        
                    }
                    // We don't need the board, though :(
                    disposeBoard (newBoard[i]);
                }
            }
            markExpanded (check);
        }
        
        check = popPQ (order);
    }

    // Awesome, we're golden. Checkstate gives us a solution
    p->solution = generateSolution (check);
    
    // Clean up time
    free (newBoard);
    disposePTree (set);
    disposePQ (order);

    return expansions;
}

int solutionLength (Puzzle p) {

    int solutionLength = 0;
    
    State count = p->solution;
    
    while (count != NULL) {
    
        count = getNext(count);
        solutionLength++;
    }

    return solutionLength - 1;
}

void printSolution (Puzzle p) {

    State nextStep = p->solution;

    while (nextStep != NULL) {
    
        printf ("%d + %d: ", getCostFromStart (nextStep), 
                             getHeuristicCost (nextStep));
    
        printBoard (getBoard (nextStep));
        nextStep = getNext (nextStep);
    }
}

void disposePuzzle (Puzzle p) {

    disposeBoard (p->start);
    p->start = NULL;
    disposeBoard (p->goal);
    p->goal = NULL;
    
    // Free the generated solution
    disposeSolution (p->solution);
    p->solution = NULL;
    
    free (p);
}

static int getHCost (Board current, Board goal, char heuristic) {

    int ret;

    if (heuristic == 'm') {

        ret = manhattanCost (current, goal);
        
    } else {

        ret = outOfPlaceCost (current, goal);
    }
    
    return ret;
}

static void handleMemoryError (void) {

    fprintf (stderr, "Memory Error. Aborting\n");
    exit (EXIT_FAILURE);
}
