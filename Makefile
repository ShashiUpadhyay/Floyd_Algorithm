all:strassen_algo tromino_algo floyd_algo

strassen_algo:strassen_algo.c
	gcc strassen_algo.c -lm -o strassen_algo

tromino_algo:tromino_algo.c
	gcc tromino_algo.c -lm -o tromino_algo

floyd_algo:floyd_algo.c
	gcc floyd_algo.c -lm -o floyd_algo

clean:
	rm -rf *.o -f strassen_algo tromino_algo floyd_algo

