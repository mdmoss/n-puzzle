/*
 * PQ.h
 *
 * Matthew Moss, mdmo552
 * Thu13Harp, Tutor: Kitten Tofu
 * 4/10/2011
 * 
 * ADT for a priority queue, passing States min first
 *
 */

#ifndef PQ_H
#define PQ_H

#include <stdio.h>
#include <stdlib.h>

#include "Board.h"
#include "State.h"

#define TRUE 1
#define FALSE 0

typedef struct _pQ * PQ;

PQ newPQ (void);

void addToPQ (PQ p, State s);
int isEmpty (PQ p);
void removeFromPQ (PQ p, Board b);
State popPQ (PQ p);

void disposePQ (PQ p);

#endif
