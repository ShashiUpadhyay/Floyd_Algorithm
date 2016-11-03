    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    #include <math.h>
    #include <string.h>

    /* Minimum number of vertices */
    #define MAX_EDGE_WEIGHT 500
    #define buffer_size 500

    int** memory_allocate(int size);
    void print_matrix(int **matrix_graph, int size);
    void floyd_algorithm(int **matrix_graph, int vertices);
    void free_allocated_memory(int **a, int size);
    void print_shortest(int **print_matrix, int start_node, int end_node);

    int main (int argc,char *argv[]){
    if(argc != 2) /* argc should be 2 for correct execution */
    {
        /* We print argv[0] assuming it is the program name */
        printf("usage: %s filename",argv[0]);
    }else{
        // Assume argv[1] is a filename to open
        FILE *file = fopen(argv[1],"r");
        /* fopen returns 0, the NULL pointer, on failure */
        if (!file){
            printf("Couldn't open %s for reading\n",argv[1]);
            return 0;
        }else{
            char vertices;
            /*
             Read one character at a time from file, halts at EOF, which indicates the end of the file. Note that the idiom of "assign
             to a variable, check the value" used below works because the assignment statement evaluates to the value assigned.
             */
            int matrix_count;matrix_count=0;
            int matrix_size; matrix_size=0;
            int *matrix_content;
            char line_buffer[buffer_size];
            matrix_content = (int *)malloc(MAX_EDGE_WEIGHT);
            int **adjacency_matrix = memory_allocate(MAX_EDGE_WEIGHT + 1);
            char *filedata;
            filedata = (char *) malloc(60);
            int i=0,j=0;
            while(fgets(line_buffer,buffer_size,file)!=NULL){
                filedata=strtok(line_buffer,",");
                while(filedata!=NULL){
                    adjacency_matrix[i][j]=atoi(filedata);
                    j++;
                    filedata=strtok(NULL,",");
                }
                i++; j=0;
                matrix_size++;
            }
            printf("Size of Matrix is as follows: %d \n\n", matrix_size);
            
            printf("\n-----------------------------------\n");
            printf("Given Weighted Matrix is as follows :\n");
            printf("-------------------------------------\n");
            print_matrix(adjacency_matrix, matrix_size);
            
            floyd_algorithm(adjacency_matrix, matrix_size);
            printf("\n----------------------------- \n");
            printf("Adjacency Matrix is as follows :\n");
            printf("------------------------------- \n");
            print_matrix(adjacency_matrix, matrix_size);
            free_allocated_memory(adjacency_matrix, matrix_size);
        }
        fclose(file);
    }
    return 0;
    }

    //function to print the matrix.
    void print_matrix(int **matrix_graph, int size)
    {
    int i,j;
    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            printf("%d\t", matrix_graph[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    }

    //Function to allocate memory to matrix.
    int** memory_allocate(int size)
    {
        int **matrix, i;
        matrix = (int **)calloc(size, sizeof(int *));
        if(matrix == NULL){
            printf("Error in memory allocation \n");
                exit(0);
        }
        for(i = 0; i < size; i++){
                matrix[i] = (int *)calloc(size, sizeof(int));
                if(matrix[i] == NULL)
                {
                    printf("Error in memory allocation \n");
                        exit(0);
                }
        }
        return matrix;
    }

    //function to print the shortest path from the source to destination.
    void print_shortest(int **print_matrix, int start, int end)
    {
        if(print_matrix[start][end] != MAX_EDGE_WEIGHT){
                print_shortest(print_matrix, start, print_matrix[start][end]);
                printf("%d->", print_matrix[start][end]);
                print_shortest(print_matrix, print_matrix[start][end], end);
        }
    }

    //function to calculate the shortest path between all the nodes, using Floyd's algorithm.
    void floyd_algorithm(int **matrix_graph, int vertices)
    {
    int i,j,k;
    int **distance_matrix = memory_allocate(vertices);
    int **print_distance = memory_allocate(vertices + 1);

    //code to initializing the distance matrix and print_distance with the values of the matrix_graph.
    for(i = 0; i < vertices; i++){
        for(j = 0; j < vertices; j++){
            distance_matrix[i][j] = matrix_graph[i][j];
            print_distance[i][j] = MAX_EDGE_WEIGHT;
        }
    }

    for(k = 0; k < vertices; k++){
        for(i = 0; i < vertices; i++){
            for(j = 0; j < vertices; j++){
                if(distance_matrix[i][j] > (distance_matrix[i][k]+distance_matrix[k][j])){
                    distance_matrix[i][j] = distance_matrix[i][k] + distance_matrix[k][j];
                    print_distance[i][j] = k;
                }
            }
        }
    }
    printf("\n----------------\n");
    printf("Distance Matrix : \n");
    printf("------------------\n");
    //Code to print the value of the distance matrix
    print_matrix(distance_matrix, vertices);
    printf("\n-----------------------------------------------\n");
    printf("Src\tDest\tDistance\tPath \n");
    printf("-------------------------------------------------\n");

    //Code to navigate the traced nodes to reach from starting source to destination.
    for(i = 0; i < vertices; i++){
        //loop to show the shortest path between all pairs of the matrix.
        for(j = 0; j < vertices; j++){
            int start_node = i;
            int end_node = j;
            printf("%d\t %d\t %d\t\t", start_node, end_node, distance_matrix[i][j]);
            printf("Node %d->", start_node);
            print_shortest(print_distance, start_node, end_node);
            printf("%d \n", end_node);
        }
    }
    free_allocated_memory(print_distance, vertices);
    }

    void free_allocated_memory(int **array, int size){
    int i;
    for(i = 0; i < size; i++){
        free(array[i]);
    }
    free(array);
    }

