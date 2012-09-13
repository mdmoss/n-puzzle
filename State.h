/*
 * State.h
 *
 * Matthew Moss, mdmo552
 * Thu13Harp, Tutor: Kitten Tofu
 * 21/10/2011
 *
 * ADT to store a State, containing a board and distance cost, for use
 * by A* and Queues
 *
 */

#ifndef STATE_H
#define STATE_H
 
#include <stdlib.h>

#include "Board.h"

#define NO_PARENT NULL
 
typedef struct _state *State;

State makeState (Board layout, State parent, 
                                  int costFromStart, int heuristicCost);       

// Neccesary updaters for A*
void setCostFromStart (State s, int cost);
int getCostFromStart (State s);
int getHeuristicCost (State s);
int getCost (State s);
void setParent (State s, State newP);

void markExpanded (State s);
int beenExpanded (State s);

// Allows use of Prefix Tree, but could easily be replaced
Board getBoard (State s);

void disposeState (State s);

// Returns a LL of States. Call getNext until getNext == NULL for 
// ordered solution. Don't forget to dispose.
State generateSolution (State end);
State getNext (State s);
void disposeSolution (State s);  

#endif
