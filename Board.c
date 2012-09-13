/*
 * Board.c
 *
 * Matthew Moss, mdmo552
 * Thu13Harp, Tutor: Kitten Tofu
 * 1/10/2011
 *
 * ADT for an nxn puzzle board
 *
 */
 
#include "Board.h"

struct _board {

    int edgeLength;
    int * state;  
};

static Board newBoard (int edgeLength);
static void setBoard (Board b, int * state);
static int shiftCost (int startX, int startY, int destX, int destY);
static void swapBoardPos (Board b, int p1X, int p1Y, int p2X, int p2Y);
static void checkMalloc (void * result);

static Board newBoard (int edgeLength) {

    Board b = malloc (sizeof (struct _board));
    checkMalloc (b);

    b->edgeLength = edgeLength;
    
    b->state = malloc (sizeof (int) * (edgeLength * edgeLength));
    checkMalloc (b->state);
    
    memset (b->state, 0, sizeof (int) * (edgeLength * edgeLength));
    
    return b;
}

static void setBoard (Board b, int * state) { // Array of length b^2

    int i;
    for (i = 0; i < b->edgeLength * b->edgeLength; i++) {
    
        b->state[i] = state[i];
    }
}

Board makeBoard (int * state, int edgeLength) {

    Board b = newBoard (edgeLength);
    setBoard (b, state);
    return b;
}

Board copyBoard (Board original) {

    Board copy = newBoard (original->edgeLength);
    setBoard (copy, original->state);
    return copy;
}

int getPos (Board b, int pos) {

    return b->state[pos];
}

int compareBoards (Board a, Board b) {

    int result = FALSE;
    if (a->edgeLength == b->edgeLength) {
        
        result = TRUE;
        int i;
        for (i = 0; i < (b->edgeLength * b->edgeLength) - 1 && result != FALSE; i++) {
        
            if (a->state[i] != b->state[i]) {
            
                result = FALSE;
            }
        }
    }
    return result;
}

void printBoard (Board b) {

    int i;
    for (i = 0; i < b->edgeLength * b->edgeLength; i++) {
    
        if (b->state[i] == BLANK) {
        
            printf ("b ");
        
        } else {
    
            printf ("%d ", b->state[i]);
        }
    }
    printf ("\n");
}

void printAsGrid (Board b) {

    printf (" ");
    
    int p;
    for (p = 0; p < b->edgeLength; p++) {
        printf ("---");
    }
    
    printf ("\n");

    int i, j;
    
    for (i = 0; i < b->edgeLength; i++) {
    
        printf ("|");
    
        for (j = 0; j < b->edgeLength; j++) {
        
            if (b->state[i*b->edgeLength + j] == BLANK) {
            
                printf ("   ");
            
            } else {
        
                printf ("%2d ", b->state[i*b->edgeLength + j]);
            }
        }
        
        printf ("|\n");
    }
    
    printf (" ");
    
    for (p = 0; p < b->edgeLength; p++) {
        printf ("---");
    }
    
    printf ("\n");
}

void disposeBoard (Board b) {

    if (b != NULL && b->state != NULL) {
    
        free (b->state);
        free (b);
    }
}

int manhattanCost (Board current, Board goal) {

    int totalCost = 0;

    int i, j;
    for (i = 0; i < current->edgeLength; i++) {
    
        for (j = 0; j < current->edgeLength; j++) {
        
            // For each x,y position in input
            int currentPos = j + (i * current->edgeLength);

            // If it's not the blank tile
            if (current->state[currentPos] != BLANK) {
            
                // Find the corresponding position in the goal
                int goalPos = 0;
                
                while (goal->state[goalPos] != current->state[currentPos]) {
                
                    goalPos++;
                }
                
                // Find the x,y reference of the goal position
                int goalX = goalPos % goal->edgeLength;
                int goalY = goalPos / goal->edgeLength;
                 
                // x,y position found
                // Adjust to equal current position
                totalCost += shiftCost (j, i, goalX, goalY);
            }
        }
    }

    return totalCost;
}

static int shiftCost (int startX, int startY, int destX, int destY) {

    int cost = abs (startX - destX) + abs (startY - destY);

    return cost;
}

int outOfPlaceCost (Board check, Board goal) {
    
    int cost = 0;
    
    int i;
    for (i = 0; i < (check->edgeLength * check->edgeLength); i++) {
    
        if (check->state[i] != BLANK &&
            check->state[i] != goal->state[i]) {
        
            cost++;
        }   
    }
 
    return cost;
}

int disorder (Board b) {

    int * matrix = b->state;
    int dimension = b->edgeLength;

    int disorder = 0;

    int i, j;
    for (i = 0; i < (dimension * dimension); i++) {
    
        for (j = (i + 1); j < (dimension * dimension); j++) {
        
            if (matrix[j] < matrix[i] && 
                matrix[i] != BLANK && 
                matrix[j] != BLANK) {
            
                disorder++;
            }
        }
    }
    
    // Even edged boards include row number of the blank in the disorder
    if (b->edgeLength % 2 == 0) {
    
        // Find the location of the blank square
        int blankIndex = 0;
        while (matrix[blankIndex] != BLANK) {

            blankIndex++;
        }

        disorder += (blankIndex / dimension + 1);
    }
    
    return disorder;
}

int permute (Board b, Board * result) {

    // Find the blank
    int bLoc = 0;
    
    while (b->state[bLoc] != BLANK) {
        bLoc++;
    }
    
    int bY = bLoc / b->edgeLength;
    int bX = bLoc % b->edgeLength;

    int generated = 0;
    Board new;
    
    // Check the four change possibilities
    if (bX > 0) {
        // Make a move to the left
        new = copyBoard (b);
        swapBoardPos (new, bX, bY, bX-1, bY);
        result[generated] = new;   
        generated++;
    }
    
    if (bX < b->edgeLength - 1) {
        // Make a move to the right
        new = copyBoard (b);
        swapBoardPos (new, bX, bY, bX+1, bY);
        result[generated] = new;
        generated++;
    }
    
    if (bY > 0) {
        // Move a move up
        new = copyBoard (b);
        swapBoardPos (new, bX, bY, bX, bY-1);
        result[generated] = new;        
        generated++;
    }
    
    if (bY < b->edgeLength - 1) {
        // Make a move down
        new = copyBoard (b);
        swapBoardPos (new, bX, bY, bX, bY+1);
        result[generated] = new;    
        generated++;
    }
    
    // Return the number of legal permutions
    return generated;
}

static void swapBoardPos (Board b, int p1X, int p1Y, int p2X, int p2Y) { 
    
    int p1Pos = (p1Y * b->edgeLength) + p1X;
    int p2Pos = (p2Y * b->edgeLength) + p2X;
    
    int temp = b->state[p1Pos];
    b->state[p1Pos] = b->state[p2Pos];
    b->state[p2Pos] = temp;
}

static void checkMalloc (void * result) {

    if (result == NULL) {
    
        fprintf (stderr, "Memory Error. Aborting\n");
        exit (EXIT_FAILURE);
    }
}
