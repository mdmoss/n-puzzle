/*
 * puzzleClient.c
 *
 * Matthew Moss, mdmo552
 * Thu13Harp, Tutor: Kitten Tofu
 * 4/10/2011
 *
 * Implements the A* algorithm on an nxn puzzle board
 *
 */

#include "puzzleClient.h"

int getUserInput (int * buffer);
int isLegal (int * state, int edgeLength);

int main (int argc, char * argv[]) {

    char prefix;
    char heuristic;

    // Check for valid CL argument                           Check:
    if (argc != 2 ||                                           // Number
       (sscanf (argv[1], "%c%c", &prefix, &heuristic) != 2) || // Format
       (prefix != '-') ||                                      // Content
       (heuristic != 'm' && heuristic != 'p')) {

        fprintf (stderr, "Usage: %s [-m|-p]\n", argv[0]);
        exit (EXIT_FAILURE);
    }

    // Biggest allowable input: 16 square puzzle * 2 = 32
    int * input = malloc (sizeof (int) * 32);

    int readLength = getUserInput (input);
    // Input now contains two back to back puzzles of length pos / 2


    if (readLength % 2 != 0 || readLength == 0) {
        fprintf (stderr, "Invalid puzzles. Aborting\n");
        exit (EXIT_FAILURE);
    }

    int puzzleLength = readLength / 2;

    int * start = &input[0];
    int * goal = &input[puzzleLength];

    if (!(isLegal (start, puzzleLength) && isLegal (goal, puzzleLength))) {

        fprintf (stderr, "Invalid puzzles. Aborting\n");
        exit (EXIT_FAILURE);
    }

    Puzzle p = newPuzzle (start, goal, puzzleLength, heuristic);
    printPuzzleInfo (p);

    if (solveable (p)) {

        printf ("solution\n");
        int expansions = solve (p);
        printSolution (p);
        printf ("expanded: %d\n", expansions);

    } else {

        printf ("no solution\n");
    }

    free (input);
    disposePuzzle (p);
    return EXIT_SUCCESS;
}

int getUserInput (int * buffer) {

    int pos = 0;

    char readChar;
    int readNum = 20;
    int blanksSeen = 0;

    readChar = getc (stdin);
    while (readChar != EOF && pos < 32) {

        if (readChar == 'b') {

            buffer[pos] = BLANK_TILE;
            blanksSeen++;
            pos++;

        } else if (readChar >= '0' && readChar <= '9') {

            ungetc (readChar, stdin);
            scanf ("%d", &readNum);
            buffer[pos] = readNum;
            pos++;

        } else if (readChar != ' ' && readChar != '\n') {

            fprintf (stderr, "Invalid Input. Aborting\n");
            exit (EXIT_FAILURE);

        }

        readChar = getc(stdin);
    }
    return pos;
}

int isLegal (int * state, int length) {

    int ret = TRUE;

    int * seen = malloc (sizeof (int) * length);
    if (seen == NULL) {

        fprintf (stderr, "Memory Error. Aborting\n");
        exit (EXIT_FAILURE);
    }
    memset (seen, 0, (length * sizeof (int)));

    int i;
    for (i = 0; i < length; i++) {

        if (state[i] == BLANK) {

            seen[BLANK_CHECK_POS]++;

        } else if (state[i] > 0 && state[i] < length) {

            seen[state[i]]++;
        }
    }

    for (i = 0; i < length; i++) {

        if (seen[i] != 1) {

            ret = FALSE;
        }

    }
    printf ("\n");
    free (seen);
    return ret;
}
