/*
 * Puzzle.h
 *
 * Matthew Moss, mdmo552
 * Thu13Harp, Tutor: Kitten Tofu
 * 4/10/2011
 *
 * ADT for an nxn puzzle.
 *
 * As this is the central ADT of the puzzle, and the most complex, I
 * will include this here. I have violated the style guide by including
 * headers within headers. From what I have seen, though, this is fairly
 * common practice and the most familiar way of laying out a program.
 *
 */

#ifndef PUZZLE_H
#define PUZZLE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Board.h"
#include "PQ.h"
#include "PTree.h"

#define BLANK_TILE -1

#define TRUE 1
#define FALSE 0

#define MANHATTAN m
#define OOP p

typedef struct _puzzle *Puzzle;

Puzzle newPuzzle (int * start, int * goal, int length, char heuristic);
void printPuzzleInfo (Puzzle p);

int solveable (Puzzle p);

// Solves the puzzle using the A* algorithm. Must be called before 
// solutionLength or printSolution
int solve (Puzzle p);

// For testing purposes
int solutionLength (Puzzle p);

void printSolution (Puzzle p);

void disposePuzzle (Puzzle p);

#endif
