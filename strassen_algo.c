#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int matrix_root(int root);
void print_matrix_content(int **array, int size_array);
int **crop_matrix(int **matrix, int start_row, int start_col, int diminish);
int **compose_new_matrix(int **a, int **b, int **c, int **d, int diminish);
int **standard_matrix_multiplication(int **a, int **b, int diminish);
int **strassen_algo_multiplication(int **matrix1, int **matrix2, int n);
int **matrix_addition(int **a, int **b, int diminish);
int **matrix_subtraction(int **a, int **b, int diminish);
void create_matrix(int **matrix, int size);

int main(int argc, char *arg[])
{
    int **first_matrix;
    int **second_matrix;
    int **result_matrix;
    
    srand(time(NULL));
    int i;
    if(argc != 2)
    {
        fprintf(stderr, "Kindly provide only numbers as input value.\n");
    }
    else
    {
        int size = atoi(arg[1]);
        if(matrix_root(size) == 0 || size == 1)
        {
            fprintf(stderr," Matrix size should be power of 2. \n");
            exit(0);
        }
        
        first_matrix = (int **)calloc(size, sizeof(int*));
        second_matrix = (int **)calloc(size, sizeof(int*));
        result_matrix = (int **)calloc(size, sizeof(int*));
        for(i = 0; i < size; i++)
        {
            first_matrix[i] = (int *) calloc(size, sizeof(int));
            second_matrix[i] = (int *) calloc(size,sizeof(int));
            result_matrix[i] = (int *) calloc(size,sizeof(int));
        }
        
        create_matrix(first_matrix,size);
        create_matrix(second_matrix,size);
        printf("Matrix 1: \n");
        print_matrix_content(first_matrix,size);
        
        printf("Matrix 2: \n");
        print_matrix_content(second_matrix,size);
        
        printf("Output of Matrix Multiplication using Strassen's Matrix Multiplication\n");
        result_matrix = strassen_algo_multiplication(first_matrix, second_matrix, size);
        print_matrix_content(result_matrix, size);
        
        printf("Output of Matrix Multiplication using Standard Matrix Algorithm\n");
        int ** regular_matrix = standard_matrix_multiplication(first_matrix,second_matrix, size);
        print_matrix_content(regular_matrix, size);
    }
    return 1;
}

//function to print the matrix.
void print_matrix_content(int **array, int size_array)
{
	int i,j;
	for(i = 0; i < size_array; i++)
	{
		for(j = 0; j < size_array; j++)
		{
			printf("%4d\t", array[i][j]);
		}
		printf("\n");
	}
    printf("\n");
}


//Function to crop_matrix larger matrix into sub matrices.
int** crop_matrix(int **matrix, int start_row, int start_col, int diminish)
{
	int **temp, i,j;
	temp = (int **)calloc(diminish, sizeof(int*));
	for(i = 0; i < diminish; i++)
	{
		temp[i] = (int *) calloc(diminish, sizeof(int));
	}

	for(i = start_row; i < start_row + diminish; i++)
	{
		for(j = start_col; j < start_col + diminish; j++)
		{
			temp[i-start_row][j - start_col] = matrix[i][j];
		}
	}
	return temp;
}

//function to add 2 matrices
int** matrix_addition(int **a, int **b, int diminish)
{
	int i,j;
	int **temp = (int **)calloc(diminish, sizeof(int*));
	for(i = 0; i < diminish; i++)
	{
		temp[i] = (int *) calloc(diminish, sizeof(int));
	}
	for(i = 0; i < diminish; i++)
	{
		for(j = 0; j < diminish; j++)
		{
			temp[i][j] = a[i][j] + b[i][j];
		}
	}
	return temp;
}

//function to subtract 2 matrix
int** matrix_subtraction(int **a, int **b, int diminish)
{
	int i,j;
	int **temp = (int **)calloc(diminish, sizeof(int*));
	for(i = 0; i < diminish; i++)
	{
		temp[i] = (int *) calloc(diminish, sizeof(int));
	}
	for(i = 0; i < diminish; i++)
	{
		for(j = 0; j < diminish; j++)
		{
			temp[i][j] = a[i][j] - b[i][j];
		}
	}
	return temp;
}

//function to generate the large matrix from smaller sub matrices.
int** compose_new_matrix(int **a, int **b, int **c, int **d, int diminish)
{
	int i,j;
	int **temp = (int **)calloc(diminish, sizeof(int*));
	for(i = 0; i < diminish; i++)
	{
		temp[i] = (int *) calloc(diminish, sizeof(int));
	}
	for(i = 0; i < diminish; i++)
	{
		for(j = 0; j < diminish; j++)
		{
			if(i >= diminish/2)
			{
				if(j >= diminish/2)
				{
					temp[i][j] = d[i-diminish/2][j - diminish/2];

				}
				else
				{				
					temp[i][j] = c[i-diminish/2][j];
				}

			}
			else
			{
				if(j >= diminish/2)
				{
					temp[i][j] = b[i][j - diminish/2];
				}
				else
				{
					temp[i][j] = a[i][j];
				}
			}
		}
	}
	return temp;
}

//function to calculate the value matrix multiplication using standard matrix multiplication algorithm.
int** standard_matrix_multiplication(int ** a, int **b, int diminish)
{
	int i,j,k;
	int **temp = (int **)calloc(diminish, sizeof(int*));
	for(i = 0; i < diminish; i++)
	{
		temp[i] = (int *) calloc(diminish, sizeof(int));
	}
	for(i = 0; i < diminish; i++)
	{
		for(j = 0; j < diminish; j++)
		{
			for(k = 0; k < diminish; k++)
			{
				temp[i][j] = temp[i][j] + a[i][k] * b[k][j];
			}
		}
	}
	return temp;
}

//function to calculate the VALUE of matrix multiplication through Strassen's technique.
int** strassen_algo_multiplication(int **matrix1, int **matrix2, int n)
{
    int **a11, **a12, **a21, **a22;
    int **b11, **b12, **b21, **b22;
    
    a11 = crop_matrix(matrix1,(n-n),(n-n),n/2); // top left
    a12 = crop_matrix(matrix1,(n-n),(n-n/2),n/2); // top right
    a21 = crop_matrix(matrix1,(n-n/2),(n-n),n/2); // bottom left
    a22 = crop_matrix(matrix1,(n-n/2),(n-n/2),n/2); // bottom right
    
    b11 = crop_matrix(matrix2,(n-n),(n-n),n/2); // top left
    b12 = crop_matrix(matrix2,(n-n),(n-n/2),n/2); // top right
    b21 = crop_matrix(matrix2,(n-n/2),(n-n),n/2); // bottom left
    b22 = crop_matrix(matrix2,(n-n/2),(n-n/2),n/2); // bottom right
    
	if( n == 2)
	{
        int q1, q2, q3, q4, q5, q6, q7;
        int c1, c2, c3, c4;
        int *temp1,*temp2, *temp3, *temp4;
        
        // Calculating q1 to q7:
		q1 = (a11[0][0] + a22[0][0]) * (b11[0][0] + b22[0][0]);
		q2 = (a21[0][0] + a22[0][0]) * b11[0][0];
		q3 =  a11[0][0] * (b12[0][0] - b22[0][0]);
		q4 =  a22[0][0] * (b21[0][0] - b11[0][0]);
		q5 = (a11[0][0] + a12[0][0]) * b22[0][0];
		q6 = (a21[0][0] - a11[0][0]) * (b11[0][0] + b12[0][0]);
		q7 = (a12[0][0] - a22[0][0]) * (b21[0][0] + b22[0][0]);

		c1 = q1 + q4 + q7 - q5;
		c2 = q3 + q5;
		c3 = q2 + q4;
		c4 = q1 + q3 + q6 - q2;
        
		temp1 = &c1;
		temp2 = &c2;
		temp3 = &c3;
		temp4 = &c4;
        
        // Combining the results obtained in a single matrix:
		return compose_new_matrix(&temp1,&temp2,&temp3,&temp4,n);
	}
	else
	{
        int **q1, **q2, **q3, **q4, **q5, **q6, **q7;
        int **c1, **c2, **c3, **c4;
        
        // Calculating q1 to q7:
		q1 = strassen_algo_multiplication(matrix_addition(a11, a22, n/2), matrix_addition(b11, b22, n/2), n/2);
		q2 = strassen_algo_multiplication(matrix_addition(a21, a22, n/2), b11, n/2);
		q3 = strassen_algo_multiplication(a11, matrix_subtraction(b12, b22, n/2), n/2);
		q4 = strassen_algo_multiplication(a22, matrix_subtraction(b21, b11, n/2), n/2);
		q5 = strassen_algo_multiplication(matrix_addition(a11, a12, n/2), b22, n/2);
		q6 = strassen_algo_multiplication(matrix_subtraction(a21, a11, n/2), matrix_addition(b11, b12, n/2), n/2);
		q7 = strassen_algo_multiplication(matrix_subtraction(a12, a22, n/2), matrix_addition(b21, b22, n/2), n/2);

		c1 = matrix_subtraction(matrix_addition(matrix_addition(q1, q4, n/2), q7, n/2), q5, n/2);
		c2 = matrix_addition(q3, q5, n/2);
		c3 = matrix_addition(q2, q4, n/2);
        c4 = matrix_subtraction(matrix_addition(matrix_addition(q1, q3, n/2), q6, n/2), q2, n/2);

        // Combining the results obtained in a single matrix:
		return compose_new_matrix(c1, c2, c3, c4, n);
	}
}

//function to generate a random matrix
void create_matrix(int **matrix, int size)
{
    int max, min; max = 10, min = -10;
	int i,j;
	for(i = 0; i < size; i++)
	{
		for(j = 0; j< size; j++)
		{
			matrix[i][j] = rand()%(max-min+1) + min;
		}
	}
}

//function to check the power of the matrix.
int matrix_root(int n)
{
	while((n % 2) == 0 && n > 1)
	{
		n = n/2;
	}
	return (n == 1);
}


