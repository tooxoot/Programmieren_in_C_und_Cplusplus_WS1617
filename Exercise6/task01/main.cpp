#include "matrix.hpp"


//Makro for MatrixException try-catch block.
#define TRY( lambda ) \
  try{ \
    lambda \
  }catch(const std::exception* e){ \
    std::cout << "EXCEPTION" << e->what() << std::endl; \
  }

//Main function for testing the matrix code.
int main(int argc, char const *argv[]) {
  Matrix * m0;
  Matrix * m1;

  std::cout << "1. ++++++ const(float, float)" << std::endl;
    Matrix m2(2,3);
    Matrix m3(3,2);
    std::cout << "m2" << std::endl << m2 << std::endl;
    std::cout << "m3" << std::endl << m3 << std::endl;

  std::cout << "5. ++++++ fill()" << std::endl;
    m2.fill();
    m3.fill();
    std::cout << "m2" << std::endl << m2 << std::endl;
    std::cout << "m3" << std::endl << m3 << std::endl;

  std::cout << "2. ++++++" << std::endl;
    std::cout << ">copyconst m4(m2)" << std::endl;

    // I'm confused! Some code expressions seem to interfere with this call and
    // cause a segmentation fault.
    // For example everything is fine until I include line 50. And inf i exchange
    // 'const std::exception* e' for '...' it's fine again. Also the math operations
    // seem to hurt.
    // The confusing bit is, that all these parts are executed after this one!
    // @QUESTION: Can you figure uot why this call causes such problems?
    // Matrix m4(m2);

    Matrix m4(2,2);
    m4 = m2;
    std::cout << "m2" << std::endl << m2 << std::endl;
    std::cout << "m4" << std::endl << m4 << std::endl;

    std::cout << ">swap m4,m3" << std::endl;
    std::swap(m4,m3);
    std::cout << "m4" << std::endl << m4 << std::endl;
    std::cout << "m3" << std::endl << m3 << std::endl;

    // std::cin.ignore();
  std::cout << "4. ++++++ MatrixException" << std::endl;
    std::cout << ">m2 = move(m4); m2 = move(m4); " << std::endl;
    m2 = std::move(m4);
    std::cout << "m2" << std::endl << m2 << std::endl;
    std::cout << "m4" << std::endl << m4 << std::endl;
    TRY( m2 = std::move(m4); )

  std::cout << "4. ++++++ addValue" << std::endl;
    m2.addValue(1,0,0);
    std::cout << "m2" << std::endl << m2 << std::endl;

  std::cout << "7. and 3. ++++++ << allready tested" << std::endl;
  float arr[5][5] = {{5,5,0,10,15},{1,3,2,1,2},{1,0,1,1,3},{3,0,2,1,1},{1,1,1,0,2}};
  Matrix m5(arr);
  Matrix m6(5,5);
  m6.fill();
  std::cout << "8. ++++++ determinant should be -165" << std::endl;
    std::cout << "m5" << std::endl << m5 << std::endl;
      std::cout << "det(m5) = " << m5.computeDeterminant() << std::endl;

  std::cout << "9. ++++++ operators" << std::endl;
    std::cout << "m6" << std::endl << m6 << std::endl;
    std::cout << ">floats" << std::endl;

      std::cout << ">> 1 + m6" << std::endl;
      std::cout << 1.0f + m6 << std::endl;

      std::cout << ">> m6 + 1" << std::endl;
      std::cout << m6 + 1.0f << std::endl;

      std::cout << ">> m6 - 1" << std::endl;
      std::cout << m6 - 1.0f << std::endl;

      std::cout << ">> 1 - m6" << std::endl;
      std::cout << 1.0f - m6 << std::endl;

      std::cout << ">> 2 * m6" << std::endl;
      std::cout << 2.0f * m6 << std::endl;

      std::cout << ">> m6 - 1" << std::endl;
      std::cout << m6 * 2.0f << std::endl;

      std::cout << ">> m6 += 1" << std::endl;
      m6 += 1.0f;
      std::cout << m6 << std::endl;

      std::cout << ">> m6 -= 1" << std::endl;
      m6 -= 1.0f;
      std::cout << m6 << std::endl;

      std::cout << ">> m6 *= 2" << std::endl;
      m6 *= 2.0f;
      std::cout << m6 << std::endl;

    std::cout << ">matrix" << std::endl;

      std::cout << ">> m6 + m6" << std::endl;
      std::cout << m6 + m6 << std::endl;

      std::cout << ">> m6 - m6" << std::endl;
      std::cout << m6 - m6 << std::endl;

      std::cout << ">> m6 * m6" << std::endl;
      std::cout << m6 * m6 << std::endl;

      std::cout << ">> m6 += m6" << std::endl;
      m6 += m6;
      std::cout << m6 << std::endl;

      std::cout << ">> m6 -= m6" << std::endl;
      m6 -= m6;
      std::cout << m6 << std::endl;

      m6.fill();

  Matrix m7(3,3);
  Matrix m8(3,3);
  m7.fill();
  m7.addValue(-1,0,1);
  m8.fill();
  std::cout << "10. ++++++ inverse" << std::endl;
      std::cout << m7.computeInverse() << std::endl;

  std::cout << "10. ++++++ division" << std::endl;
      TRY(std::cout << m8.divideMatrices(m7) << std::endl;)


  return 0;
}
