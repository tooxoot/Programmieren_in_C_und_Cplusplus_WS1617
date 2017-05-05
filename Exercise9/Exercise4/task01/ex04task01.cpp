#include <iostream>

/*
* Replaces the macro with the maximum of the two parameters x and y.
*/
#define MAXM( x, y )  ( x > y ? x : y )

/*
* Returns the maximum of the two integers x and y as an integer.
*
* @param x The first int.
* @param y The second int.
* @return The maximum of x and y as an int.
*/
int maxf(const int x,const int y){
  std::cout << "In maxf(int)"<< std::endl;
  if (x > y)
    return x;
  else
    return y;
}

/*
* Returns the maximum of the two doubles x and y as a double.
*
* @param x The first double.
* @param y The second double.
* @return The maximum of x and y as an double.
*/
double maxf(const double x,const double y){
  std::cout << "In maxf(double)"<< std::endl;
  if (x > y)
    return x;
  else
    return y;
}

int main(void) {
  int a = 10, b = 20;
  std::cout << "MAXM1 = " << MAXM(a,b)      << std::endl;
  std::cout << "MAXM2 = " << MAXM(a,b+0.2)  << std::endl;
  std::cout << "MAXM3 = " << MAXM(a,b++)    << std::endl;
  std::cout << "maxf1 = " << maxf(a,b)      << std::endl;
  // what's the problem with the following line?
  //std::cout << "maxf = " << maxf(a,b+0.2) << std::endl;
  std::cout << "maxf2 = " << maxf(a+0.1,b+0.2)  << std::endl;
  std::cout << "maxf3 = " << maxf(a,b++)        << std::endl;
  std::cout << "a = " << a << ", b = " << b     << std::endl;
}
