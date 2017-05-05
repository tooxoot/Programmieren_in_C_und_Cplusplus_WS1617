# include <stdio.h>

int cube1 [3][2][4] = { {{1,2,3,4}}, {{2,3}, {4,6,8,10}}, {{3,4,5,6}, {6,8,10}} };
int cube2[2][3][3] = { {{9,8,7}, {6}, {5,4}}, {{3,2}, {1,2,3}, {4}} };

/**
* Takes a pointer to a 3-dimensional int-array and calculates the sum of all 2nd
* elements from the one dimensional int-arrays.
*
* @param pointer The int* that points to the first element of the 3-dimensional array.
* @param dim0 The the first dimension of the array (eg array[dim0][dim1][dim2]).
* @param dim0 The the second dimension of the array (eg array[dim0][dim1][dim2]).
* @param dim0 The the third dimension of the array (eg array[dim0][dim1][dim2]).
* @return The sum off all elemnts e = array[m][n][1] where m < dim0 and n < dim1.
*/
int sum2nd (int* pointer, const int dim0, const int dim1, int dim2){
  int returnSum = 0;
  int* currentPointer = pointer;
  while (currentPointer < pointer + dim2 * dim1 * dim0 ) {
    currentPointer += 1;
    returnSum += *(currentPointer);
    currentPointer += dim0;
  }
 return returnSum;
}

/**
*Prints out the sum of the 2nd elements of cube1 and cube2 implemented above.  
*/
int main(int argc, char const *argv[]) {
  printf("%d\n", sum2nd(&cube1[0][0][0],3,2,4) );
  printf("%d\n", sum2nd(&cube2[0][0][0],2,3,3) );
  return 0;
}
