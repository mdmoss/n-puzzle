# Matthew Moss, mdmo552
# Thu13Harp, Tutor: Kitten Tofu
# 21/10/2011

puzzle: Board.c Board.h State.c State.h PTree.c PTree.h PQ.c PQ.h Puzzle.c Puzzle.h puzzleClient.c puzzleClient.h
	gcc -Wall -Werror -lm -o puzzle puzzleClient.c Puzzle.c PQ.c PTree.c State.c Board.c

test: Board.c Board.h testBoard.c State.c State.h testState.c PTree.c PTree.h testPTree.c PQ.c PQ.h testPQ.c Puzzle.c Puzzle.h testPuzzle.c
	gcc -Wall -Werror -g -o testBoard testBoard.c Board.c
	gcc -Wall -Werror -g -o testState testState.c State.c Board.c
	gcc -Wall -Werror -g -o testPTree testPTree.c PTree.c State.c Board.c
	gcc -Wall -Werror -g -o testPQ testPQ.c PQ.c State.c Board.c
	gcc -Wall -Werror -g -lm -o testPuzzle testPuzzle.c Puzzle.c PQ.c PTree.c State.c Board.c
	./testBoard
	./testState
	./testPTree
	./testPQ
	./testPuzzle

valgrind: FORCE
	make debug
	valgrind ./puzzle_debug -m < challenge.in

debug: FORCE
	gcc -Wall -Werror -lm -g -o puzzle_debug puzzleClient.c Puzzle.c PQ.c PTree.c State.c Board.c

profile: FORCE
	gcc -Wall -Werror -lm -g -pg -o puzzle_prof puzzleClient.c Puzzle.c PQ.c PTree.c State.c Board.c
	./puzzle_prof -p < worstcase.in
	gprof ./puzzle_prof gmon.out > profile
	rm puzzle_prof gmon.out

fast: Board.c Board.h State.c State.h PTree.c PTree.h PQ.c PQ.h Puzzle.c Puzzle.h puzzleClient.c puzzleClient.h
	gcc -Wall -Werror -lm -O3 -o puzzle_fast puzzleClient.c Puzzle.c PQ.c PTree.c State.c Board.c

clean: FORCE
	rm -f a.out testBoard testState testPTree testPQ testPuzzle puzzle
	clear

FORCE:
