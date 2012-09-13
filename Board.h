/*
 * Board.h
 *
 * Matthew Moss, mdmo552
 * Thu13Harp, Tutor: Kitten Tofu
 * 1/10/2011
 *
 * ADT for an nxn puzzle board
 *
 */

#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define TRUE 1
#define FALSE 0

#define BLANK -1

typedef struct _board *Board;

// state: array of length edgeLength^2 containing board contents
Board makeBoard (int * state, int edgeLength);
Board copyBoard (Board original);

int compareBoards (Board a, Board b);

// Treating board as a 1d array, numbered horizontally
// Used for prefix tree
int getPos (Board b, int pos);

void printBoard (Board b);

// Not needed, but useful for development
void printAsGrid (Board b); 

void disposeBoard (Board b);

int manhattanCost (Board check, Board goal);
int outOfPlaceCost (Board check, Board goal);

int disorder (Board b);

// Returns 0-4, indicating the number of Board permutions in result
int permute (Board b, Board * result);

#endif
