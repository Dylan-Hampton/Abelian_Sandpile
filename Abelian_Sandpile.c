#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//Note: make sure to create README file with names and turn in a MakeFile

//Declarations
void simulate(int row, int col);
void topple(int row, int col);
void printModel();

//Globals
int model[23][23];

int main(int argc, char *argv[])
{
	//getting any user input
        int fps = 60;
	int i = 1;
	if (argc > 1) {
          if(strcmp(argv[i],"--fps") == 0) //check for fps
            {
              fps = atoi(argv[i+1]);
	      i = 3;
            }
	}
	
	while (i + 2 < argc) {
		model[atoi(argv[i])][atoi(argv[i + 1])] = atoi(argv[i + 2]);
		i += 3;
	}

	while(1)
	{
	  simulate(11,11); //check for topple   11,11 is center
	  printModel();
	  model[11][11]++; //add 1 to center pile
	  usleep(1000000 / fps);
	}
}

void simulate(int row, int col)
{
	if(model[row][col] > 8)
	{
	  topple(row,col);
	}
}

void topple(int row, int col)
{
  model[row][col] -= 9;

	for(int r = -1; r <= 1; r++) //if not a sink and is on the model, check if any other piles topple
	{
	  for(int c = -1; c <= 1; c++)
	    {
	      if(model[row + r][col + c] != -1 &&
		 (row + r) >= 0 && (col + c) >= 0) 
		 {
		   model[row + r][col + c]++;
		   simulate(row + r, col + c);
		 }
	    }
	}
}

void printModel()
{
	for(int r = 0; r < 23; r++)
	{
	  for(int c = 0; c < 23; c++)
	    {
	      if(model[r][c] == -1)
		{
		  printf("# ");
		}

		else
		{
		  printf("%d ", model[r][c]);
		}
	    }
	  printf("\n");
	}
	printf("\n");
}




