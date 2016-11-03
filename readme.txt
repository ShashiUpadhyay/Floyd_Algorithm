1. To compile the program type 'make' in the command line once in the proper folder.

2. To run the strassen's multiplication matrix, enter './strassen_algo <any number of the order of 2^k eg 2,4,8 etc>
For example: ./strassen_algo 4.	
This will produce a random matrix of size 4x4.

3. To run the tromino tiling algorithm, enter './tromino_algo <any number from 1 to 6>
For example:  ./tromino_algo 2.	
This will produce a matrix with a hole at a random index within the 4x4 matrix.
X - represents the hole
1 - represents the respective hole created

4. To run the Floyd's algorithm, enter ./floyd_algo <(filename which has the size and values of the input matrix)
For example: ./floyd_algo floydfile.txt
floydfile.txt will contain the matrix data separated by comma
for example:
0,1,500,1,5
9,0,3,2,500
500,500,0,4,500
500,500,2,0,3
3,500,500,500,0

This will produce the adjacency matrix,distance matrix and the path from each node to it's destination.
