/*
 * PQ.c
 *
 * Matthew Moss, mdmo552
 * Thu13Harp, Tutor: Kitten Tofu
 * 4/10/2011
 * 
 * ADT for a priority queue, passing States min first
 *
 * Based on a dynamic heap implemetation
 *
 * The heap contains NUM_TIERS possible buckets of memory, increasing at 
 * an exponential rate. This will provide 2^(NUM_TIERS - 1) possible states.
 *
 * 64 is a nice number of tiers. They won't all be used, after all.
 * Also, that's enough to store all possible combinations of the
 * 15 puzzle 44,000 times over. Should be plenty ;)
 *
 * It would be possible to make this list expand as needed as well, but
 * a static length is much easier.
 *
 * This ADT is well abstracted, as it only queries states for information
 *
 * This is a really nice structure, actually. We get O(log n) operations,
 * with n < NUM_TIERS. This means that we can happily stuff ten times
 * the number of states we need to keep track of in, and just deal with
 * them as we need to, rather than searching and replacing them.
 *
 * The price paid is in the memory use. A more memory friendly option
 * would be a linearly searched LL approach. Slow...
 * 
 */

#include "PQ.h"

#define NUM_TIERS 64

struct _pQ {

    int bottomTier;
    int currentEnd;

    State *tier[NUM_TIERS];
};

static int withinBounds (PQ p, int tier, int pos);
static void swap (State * a, State * b);
static void checkMalloc (void * result);


PQ newPQ (void) {

    PQ new = malloc (sizeof (struct _pQ));
    checkMalloc (new);
    
    new->bottomTier = 0;
    new->currentEnd = 0;
    
    int i;
    for (i = 0; i < NUM_TIERS; i++) {
    
        new->tier[i] = NULL;
    }
    
    new->tier[new->bottomTier] = malloc (sizeof (State *)* (1 << new->bottomTier));
    checkMalloc (new->tier[new->bottomTier]);
    
    return new;
}

void addToPQ (PQ p, State s) {

    if (p->currentEnd >= (1 << p->bottomTier)) {
    
        // We're out of room. New tier time.
        p->bottomTier++;
        
        if (p->tier[p->bottomTier] == NULL) {
        
            p->tier[p->bottomTier] = malloc (sizeof (State *) * (1 << p->bottomTier));
            checkMalloc (p->tier[p->bottomTier]);   
        }
        p->currentEnd = 0;
    }

    p->tier[p->bottomTier][p->currentEnd] = s;

    int inspectTier = p->bottomTier;
    int inspectEnd = p->currentEnd;
    
    // Bubble up
    while (inspectTier > 0 && 
    getCost (p->tier[inspectTier][inspectEnd]) < 
                      getCost (p->tier[inspectTier-1][inspectEnd/2])) {
    
        swap (&p->tier[inspectTier][inspectEnd], 
                                &p->tier[inspectTier-1][inspectEnd/2]);
                                
        inspectTier--;
        inspectEnd = inspectEnd / 2;
    }

    p->currentEnd++;
}

State popPQ (PQ p) {
    
    State ret = p->tier[0][0];
    
    p->tier[0][0] = p->tier[p->bottomTier][p->currentEnd - 1];
    
    p->currentEnd--;
    
    // Second check is for empty PQ
    if (p->currentEnd < 1 && p->bottomTier > 0) {
    
        
        // Clean up empty tier
        if (p->bottomTier + 1 < NUM_TIERS &&
                                   p->tier[p->bottomTier + 1] != NULL) {
        
            free (p->tier[p->bottomTier + 1]);
            p->tier[p->bottomTier + 1] = NULL;
        }
        
    
        // Fix tier change alignment...
        p->bottomTier--;
        p->currentEnd = ((1 << (p->bottomTier)));
    }
    
    if (p->bottomTier > 0 || p->currentEnd > 0) {
        
        int inspectTier = 0;
        int inspectEnd = 0;
        
        // Cool, heap is the proper length and all. Bubble down.
        while ((withinBounds (p, inspectTier + 1, inspectEnd * 2) && 
                getCost (p->tier[inspectTier][inspectEnd]) > 
                getCost (p->tier[inspectTier + 1][inspectEnd * 2])) 
                ||
                (withinBounds (p, inspectTier + 1, inspectEnd * 2 + 1) &&
                getCost (p->tier[inspectTier][inspectEnd]) > 
                getCost (p->tier[inspectTier + 1][inspectEnd * 2 + 1]))) {
                
            if (!(withinBounds (p, inspectTier + 1, inspectEnd * 2 + 1)) ||
               (getCost (p->tier[inspectTier + 1][inspectEnd * 2]) < 
                getCost (p->tier[inspectTier + 1][inspectEnd * 2 + 1]))) {
                
                swap (&p->tier[inspectTier][inspectEnd], 
                                 &p->tier[inspectTier + 1][inspectEnd * 2]);
                
                inspectTier++;
                inspectEnd = inspectEnd * 2;
                
            } else {
            
                swap (&p->tier[inspectTier][inspectEnd], 
                             &p->tier[inspectTier + 1][inspectEnd * 2 + 1]);
            
                inspectTier++;
                inspectEnd = inspectEnd * 2 + 1;
            }
        }
    }
    return ret;
}

int isEmpty (PQ p) {

    return (p->bottomTier == 0 && p->currentEnd == 0);
}

void disposePQ (PQ p) {

    int i;
    for (i = 0; i < NUM_TIERS; i++) {
    
        if (p->tier[i] != NULL) {
        
            free (p->tier[i]);
        }
    }
    free (p);
}

static void swap (State * a, State * b) {

    State temp = *a;
    *a = *b;
    *b = temp;
}

static int withinBounds (PQ p, int tier, int pos) {

    int ret = FALSE;

    if (tier < p->bottomTier && pos < (1 << tier)) {
    
        ret = TRUE;
    } else if (tier == p->bottomTier && pos < p->currentEnd) {
    
        ret = TRUE;
    }

    return ret;
}

static void checkMalloc (void * result) {

    if (result == NULL) {
    
        fprintf (stderr, "Memory Error. Aborting\n");
        exit (EXIT_FAILURE);
    }
}