#include <stdio.h>
#include <stdlib.h>

void rotate(char matrix[10][10])
{
  for (int i = 0; i < 5; i++)
    {
      for (int j = i; j < 9 - i; j++)
	{
	  int temp = matrix[j][9 - i];
	  matrix[j][9 - i] = matrix[i][j];
	  int temp1 = matrix[9 - i][9 - j];
	  matrix[9 - i][9 - j] = temp;
	  temp = matrix[9 - j][i];
	  matrix[9 - j][i] = temp1;
	  matrix[i][j] = temp;
	}
    }
}
