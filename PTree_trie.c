/*
 * PTree.c
 *
 * Matthew Moss, mdmo552
 * Thu13Harp, Tutor: Kitten Tofu
 * 21/10/2011
 *
 * A faster implementation of a set using a prefix tree
 *
 */

#include "PTree.h"

#define SPARE 0

typedef struct _node {

    State endPoint;
    struct _node ** next;

} * Node;
 
typedef struct _pTree {

    struct _node * root;
    int boardSize;

} pTree;

static Node newNode (int boardSize);
static void disposeNode (Node n, int boardSize);
static void printNode (Node n, int boardSize, int depth);

static void checkMalloc (void * result);

PTree newPTree (int boardSize) {

    PTree p = malloc (sizeof (pTree));
    checkMalloc (p);
    p->boardSize = boardSize;
    p->root = newNode (boardSize);

    return p;
}

void addToPTree (PTree p, State s) {

    Node check = p->root;
    
    Board read = getBoard (s);
    
    int i; 
    for (i = 0; i < p->boardSize; i++) {
    
        int contents = getPos (read, i);
    
        if (contents == BLANK) {
        
            // Correction for unspecified blank square value
            contents = SPARE;
        }
    
        if (check->next[contents] == NULL) {
        
            check->next[contents] = newNode (p->boardSize);
        }
        
        check = check->next[contents];
    }
    
    check->endPoint = s;
}

State inPTree (PTree p, Board b) {

    Node check = p->root;

    int nope = FALSE;
    
    int i;
    for (i = 0; i < p->boardSize && !nope; i++) {
    
        int contents = getPos (b, i);
    
        if (contents == BLANK) {
        
            // Correction for unspecified value blank square
            contents = SPARE;
        }
    
        if (check->next[contents] == NULL) {
        
            nope = TRUE;
        
        } else {
        
            check = check->next[contents];
        }
    }
    
    // Any present board will result in a state existing here
    // Any invalid will progress < required moves, and check->endpoint
    // will be NULL.
    return check->endPoint;
}

void printPTree (PTree p) {

    printNode (p->root, p->boardSize, 0);

}

void removeFromPTree (PTree p, Board b) {

    Node check = p->root;

    int nope = 0;
    
    int i;
    for (i = 0; i < p->boardSize && !nope; i++) {
    
        int contents = getPos (b, i);
    
        if (contents == BLANK) {
        
            // Correction for unspecified blank square value
            contents = SPARE;
        }
    
        if (check->next[contents] == NULL) {
        
            nope = 1;
        
        } else {
        
            check = check->next[contents];
        
        }
    }
    
    if (!nope) {
    
        check->endPoint = NULL;
    }
}

static void printNode (Node n, int boardSize, int depth) {

    if (n != NULL) {
    
        if (n->endPoint == NULL) {
        
            int i;
            for (i = 0; i < boardSize; i++) {
            
                int j;
                for (j = 0; j < depth; j++) {
                
                    printf ("\t");
                
                }
            
                printf ("%d-->\n", i);
                printNode (n->next[i], boardSize, depth + 1);
            }
            
        } else {
        
            int j;
            for (j = 0; j < depth; j++) {
            
                printf ("\t");
            
            }
        
            printBoard (getBoard (n->endPoint));
        }
    }
}

void disposePTree (PTree p) {

    disposeNode (p->root, p->boardSize);
    free (p);
}

static void disposeNode (Node n, int boardSize) {

    if (n != NULL) {
    
        int i;
        
        if (n->endPoint == NULL) {
            for (i = 0; i < boardSize; i++) {
        
                disposeNode (n->next[i], boardSize);
            }
        }
        
        free (n->next);
        
        if (n->endPoint != NULL) {
        
            disposeState (n->endPoint);
        }
        
        free (n);
    }
}

static Node newNode (int boardSize) {

    Node new = malloc (sizeof (struct _node));
    checkMalloc (new);

    new->next = malloc (sizeof (Node) * boardSize);
    checkMalloc (new->next);
    
    int i;
    for (i = 0; i < boardSize; i++) {
    
        new->next[i] = NULL;
    }
    
    new->endPoint = NULL;
    
    return new;
}

static void checkMalloc (void * result) {

    if (result == NULL) {
    
        fprintf (stderr, "Memory Error. Aborting\n");
        exit (EXIT_FAILURE);
    }
}
