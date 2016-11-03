#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TILE_INIT 'X';
#define FILL_INIT '0';
#define INIT_INIT '_';

int tile_quadrants = 1;

//Tile structure with x-coordinate and y-coordinate
struct tile
{
    int x_coordinate;
    int y_coordinate;
};

//Function to calculate 2 raise to the power of number
int generate_two_raise_power(int n);
//Function to generate the tile at any random place
struct tile *generate_tile(int n);
//function to generate a board of the input size.
char **generate_board(int n,struct tile* tile);
//Function to print the output of the board
void print_board(char **board, int n);
//function to split the tile till we get a 2x2 board using recursive call.
void tromino_tile(char **tile, int x_start, int y_start, int index, int x_point, int y_point);


struct tile *generate_tile(int n)
{
    srand(time(NULL));
    struct tile *tile = malloc(sizeof(struct tile));
    tile->x_coordinate = rand()%n;
    tile->y_coordinate = rand()%n;
    return tile;
}

int generate_two_raise_power(int n)
{
    return pow(2,n);
}

char **generate_board(int n,struct tile* tile)
{
    int i,j;
    char** board = malloc(sizeof(char *)* n);
    
    for(i=0;i<n;i++)
    {
        board[i] = malloc(sizeof(char)*n);
    }
    
    printf("Generating Board \n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            //check if the index of the board is equal to the index of the tile and place a tile there if true.
            if(i == tile->x_coordinate && j==tile->y_coordinate)
            {
                board[i][j] = TILE_INIT;
                printf("%c\t",board[i][j]);
            }
            else
            {
                //initialize the value to $ for all positions of the board other than the tile.
                board[i][j] = INIT_INIT;
                printf("%c\t",board[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
    return board;
}

void print_board(char **board, int n)
{
    printf("Output using tromino tiling algorithm \n");
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(board[i][j] == 'X')
            {
                printf("%c\t",board[i][j]);
            }
            else
            {
                printf("%d\t",board[i][j]);
            }
        }
        printf("\n");
    }
}

void tromino_tile(char **tile, int x_start, int y_start, int index, int x_point, int y_point)
{
    int center = generate_two_raise_power(index)/2;
    
    int x_point_value_center_minus_one = x_start+center-1;
    int x_point_value_center = x_start+center;
    
    int y_point_value_center_minus_one = y_start+center-1;
    int y_point_value_center = y_start+center;
    
    int index_minus_one = index-1;
    
    if(index == 1){
        if(x_point <= x_point_value_center_minus_one){
            if(y_point <= y_point_value_center_minus_one){
                
                tile[x_point_value_center_minus_one][y_point_value_center] = tile_quadrants;
                tile[x_point_value_center][y_point_value_center_minus_one] = tile_quadrants;
                tile[x_point_value_center][y_point_value_center] = tile_quadrants;
                tile_quadrants++;
                
            }else if(y_point > y_point_value_center_minus_one){
                
                tile[x_point_value_center_minus_one][y_point_value_center_minus_one] = tile_quadrants;
                tile[x_point_value_center][y_point_value_center_minus_one] = tile_quadrants;
                tile[x_point_value_center][y_point_value_center] = tile_quadrants;
                tile_quadrants++;
                
            }
            
        }else if(x_point > x_point_value_center_minus_one){
            
            if(y_point <= y_point_value_center_minus_one){
                
                tile[x_point_value_center_minus_one][y_point_value_center_minus_one] = tile_quadrants;
                tile[x_point_value_center_minus_one][y_point_value_center] = tile_quadrants;
                tile[x_point_value_center][y_point_value_center] = tile_quadrants;
                tile_quadrants++;
                
            }else if(y_point > y_point_value_center_minus_one){
                
                tile[x_point_value_center_minus_one][y_point_value_center_minus_one] = tile_quadrants;
                tile[x_point_value_center_minus_one][y_point_value_center] = tile_quadrants;
                tile[x_point_value_center][y_point_value_center_minus_one] = tile_quadrants;
                tile_quadrants++;
                
            }
        }
        
    }else{
        
        if(x_point <= x_point_value_center_minus_one){
            
            if(y_point <= y_point_value_center_minus_one){
                tile[x_point_value_center_minus_one][y_point_value_center] = tile_quadrants;
                tile[x_point_value_center][y_point_value_center_minus_one] = tile_quadrants;
                tile[x_point_value_center][y_point_value_center] = tile_quadrants;
                
                tile_quadrants++;
                
                tromino_tile(tile,x_start,y_start, index_minus_one, x_point, y_point);
                tromino_tile(tile,x_start,y_point_value_center, index_minus_one, x_point_value_center_minus_one, y_point_value_center);
                tromino_tile(tile,x_point_value_center, y_start, index_minus_one, x_point_value_center, y_point_value_center_minus_one);
                tromino_tile(tile,x_point_value_center, y_point_value_center, index_minus_one, x_point_value_center, y_point_value_center);
                
            }else if(y_point > y_point_value_center_minus_one){
                
                tile[x_point_value_center_minus_one][y_point_value_center_minus_one] = tile_quadrants;
                tile[x_point_value_center][y_point_value_center_minus_one] = tile_quadrants;
                tile[x_point_value_center][y_point_value_center] = tile_quadrants;
                
                tile_quadrants++;
                
                tromino_tile(tile,x_start,y_start, index_minus_one, x_point_value_center_minus_one, y_point_value_center_minus_one);
                tromino_tile(tile,x_start,y_point_value_center, index_minus_one, x_point, y_point);
                tromino_tile(tile, x_point_value_center, y_start, index_minus_one, x_point_value_center, y_point_value_center_minus_one);
                tromino_tile(tile, x_point_value_center, y_point_value_center, index_minus_one, x_point_value_center, y_point_value_center);
                
            }
            
        }else if(x_point > x_point_value_center_minus_one){
            
            if(y_point <= y_point_value_center_minus_one){
                tile[x_point_value_center_minus_one][y_point_value_center_minus_one] = tile_quadrants;
                tile[x_point_value_center_minus_one][y_point_value_center] = tile_quadrants;
                tile[x_point_value_center][y_point_value_center] = tile_quadrants;
                
                tile_quadrants++;
                
                tromino_tile(tile, x_start,y_start, index_minus_one, x_point_value_center_minus_one, y_point_value_center_minus_one);
                tromino_tile(tile, x_start,y_point_value_center, index_minus_one, x_point_value_center_minus_one, y_point_value_center);
                tromino_tile(tile, x_point_value_center, y_start, index_minus_one, x_point, y_point);
                tromino_tile(tile, x_point_value_center, y_point_value_center, index_minus_one, x_point_value_center, y_point_value_center);
                
            }else if(y_point > y_point_value_center_minus_one){
                
                tile[x_point_value_center_minus_one][y_point_value_center_minus_one] = tile_quadrants;
                tile[x_point_value_center_minus_one][y_point_value_center] = tile_quadrants;
                tile[x_point_value_center][y_point_value_center_minus_one] = tile_quadrants;
                
                tile_quadrants++;
                
                tromino_tile(tile,x_start,y_start, index_minus_one, x_point_value_center_minus_one, y_point_value_center_minus_one);
                tromino_tile(tile,x_start,y_point_value_center, index_minus_one, x_point_value_center_minus_one, y_point_value_center);
                tromino_tile(tile, x_point_value_center, y_start, index_minus_one, x_point_value_center, y_point_value_center_minus_one);
                tromino_tile(tile, x_point_value_center, y_point_value_center, index_minus_one, x_point, y_point);
                
            }
        }
        
    }
}

int main(int argc,char* argv[])
{
    if(argc == 2)
    {
    int n = atoi(argv[1]);
    if(n < 1 || n > 6)
    {
        printf("Kindly provide the input between 1 and 6\n");
        exit(0);
    }
    
        struct tile *tile;
        int index = generate_two_raise_power(n);
        tile = generate_tile(index);
        printf("Size of Matrix : %d \n\n", index);
        
        printf("Printing the co-ordinates of Tile : [%d, %d] \n", tile->x_coordinate, tile->y_coordinate);
        
        char **board= generate_board(index,tile);
        tromino_tile(board, 0, 0, n, tile->x_coordinate, tile->y_coordinate);
        print_board(board, index);
    }
    else
    {
        printf("please enter only one argument.\n");
    }
    return 0;
}
