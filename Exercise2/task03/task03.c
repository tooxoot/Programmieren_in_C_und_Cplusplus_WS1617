
char  input[100];
int   argumentA;
char  operator;
int   argumentB;
int   result;

/**
* Scans the input searching for argumentA, argumentB and operator as defined above.
* If exactly these three arguments are found and the operator is valid (=,-,*,/)
* the operations result is calculated.
*
* @return 0 if the input was valid and the result was successfully calculated.
*         -1 if the input contained more or less than the three argument described above.
*         -2 if the scan was valid but a devision by zero appeared.
*         -3 if the scan was valid but the operator was not (valid operators: =,-,*,/).
*/
int evaluateInput(){
  int NumberOfScannedArgument = sscanf(input, "%d %c %d %c", &argumentA, &operator, &argumentB, &operator);
  if ( NumberOfScannedArgument != 3 ) return -1;

  switch (operator) {
   case '+':
    result = argumentA + argumentB;
    break;
   case '-':
    result = argumentA - argumentB;
    break;
   case '*':
    result = argumentA * argumentB;
    break;
   case '/':
    if ( argumentB == 0 ) return -2;
    result = argumentA / argumentB;
    break;
   default:
    return -3;
 }

 return 0;
}


/**
* Loops while fgets could successfully read from the standard input and the user
* does not enter "0\n".
* The Loop evaluates the user's input as described above and in case of a success
* prints out the equation.
*
* @return 0
*/
int main (void) {

  while ( printf("Enter <int> <op> <int>, single '0' to exit: ") && fgets(input, 100, stdin) ) {
    if( input[0] == '0' && input[1] == '\n' ){
      printf("Goodbye\n" );
      break;
    }
    if(evaluateInput() != 0) {
      printf("invalid input\n" );
    } else {
      printf("%d %c %d = %d\n", argumentA, operator, argumentB, result );
    }
  }

  return 0;
}
