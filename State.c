/*
 * State.c
 *
 * Matthew Moss, mdmo552
 * Thu13Harp, Tutor: Kitten Tofu
 * 21/10/2011
 *
 * ADT to store a State, containing a board and distance cost, for use
 * by A* and Queues
 *
 */

#include "State.h"
 
typedef struct _state {

    Board layout;
    struct _state * parent; // For solution finding
    int costFromStart;
    int heuristicCost;
    int expanded;
    
    struct _state * next; // For solution pathing and closed set

} state;

static void checkMalloc (void * result);

State makeState (Board layout, State parent, int costFromStart,
                        int heuristicCost) {

    State newState = malloc (sizeof (struct _state));
    checkMalloc (newState);
    
    newState->layout = layout;
    newState->parent = parent;
    newState->costFromStart = costFromStart;
    newState->heuristicCost = heuristicCost;
    newState->expanded = FALSE;
    return newState;
}

Board getBoard (State s) {

    return s->layout;
}

State generateSolution (State end) {

    State solution = makeState (copyBoard(end->layout), NO_PARENT, 
    end->costFromStart, end->heuristicCost);
    
    solution->next = NULL;

    State prevState;

    while (end->parent != NULL) {

        prevState = makeState (copyBoard (end->parent->layout), 
                               NO_PARENT, 
                               end->parent->costFromStart, 
                               end->parent->heuristicCost);

        prevState->next = solution;
        solution = prevState;

        end = end->parent;
    }

    return solution;
}

State getNext (State s) {

    return s->next;
}

int getCostFromStart (State s) {

    return s->costFromStart;
}

void setCostFromStart (State s, int cost) {

    s->costFromStart = cost;
}

int getHeuristicCost (State s) {

    return s->heuristicCost;
}

int getCost (State s) {

    return s->costFromStart + s->heuristicCost;
}

void setParent (State s, State newP) {

    s->parent = newP;
}

void markExpanded (State s) {

    s->expanded = TRUE;
}

int beenExpanded (State s) {

    return s->expanded;
}

void disposeState (State s) {

    disposeBoard (s->layout);
    free (s);
}

void disposeSolution (State s) {

    while (s != NULL) {
    
        State toGo = s;
        s = s->next;
        disposeState (toGo);
    }
}

static void checkMalloc (void * result) {

    if (result == NULL) {
    
        fprintf (stderr, "Memory Error. Aborting\n");
        exit (EXIT_FAILURE);
    }
}
