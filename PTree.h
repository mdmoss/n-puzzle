/*
 * PTree.h
 *
 * Matthew Moss, mdmo552
 * Thu13Harp, Tutor: Kitten Tofu
 * 21/10/2011
 *
 * A faster implementation of a set using a prefix tree
 *
 * This violates abstraction somewhat, as it queries states for 
 * information about their boards. It also uses boards to check for 
 * the existance of states. In this application, however, a 
 * substitute datatype could easily be used, and the speed is worth it.
 *
 * Also, constant time lookups are awesome for sets.
 *
 */

#ifndef PTREE_H
#define PTREE_H
 
#include <stdio.h>
#include <stdlib.h>

#include "Board.h"
#include "State.h"

#define TRUE 1
#define FALSE 0
 
typedef struct _pTree * PTree;
 
PTree newPTree (int boardSize);

void addToPTree (PTree p, State s);

// Returns either the State, or NULL for not present
State inPTree (PTree p, Board b);

void removeFromPTree (PTree p, Board b);

// Disposing a PTree also frees all cargo states
void disposePTree (PTree p);

// For debugging
void printPTree (PTree p);

#endif
