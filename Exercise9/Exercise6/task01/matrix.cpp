
// Include definition of class Matrix in matrix.hpp.


/**
* Overloads the << operator to print the Matrix' elements to the given ostream.
* Attention: Throws no Exception if the referenced Matrix is not properly allocated!
*
* @return Areference to the given referenced ostream.
*/
std::ostream& operator<<(std::ostream& os, const Matrix& matrix){
  for (int i = 0; i < matrix.getRow(); i++) {
    for (int j = 0; j < matrix.getCol(); j++) {
      os << matrix.getMatrix()[i][j] << "\t";
    }
    os << std::endl;
  }
  return os;
}

/**
 * Following are the member functions from the Matrix class.
 * For descriptions see the matrix.hpp headerfile.
 */

Matrix::Matrix(const float row, const float col){
  if(row < 1 || col < 1){
    throw new MatrixException((char*)("Unsupported matrix dimensions"));
  }
  this->row = row;
  this->col = col;
  this->matrix = new float*[(int)row];
  for (int i = 0; i < row; i++){
    this->matrix[i] = new float[(int)col];
    for (int j = 0; j < col; j++)
      this->matrix[i][j] = 0;
  }
}
Matrix::Matrix(float mat[5][5]) : Matrix(5, 5){
  for (int i = 0; i < this->row; i++)
    for (int j = 0; j < this->col; j++)
      this->matrix[i][j] = mat[i][j];
}

Matrix::Matrix(const Matrix& copiedMatrix){
  copy(copiedMatrix);
}
Matrix& Matrix::operator=(const Matrix& copiedMatrix){
  copy(copiedMatrix);
  return *this;
}
void Matrix::copy(const Matrix& copiedMatrix){
  if( this == &copiedMatrix) return;
  try{
    this->checkAllocation();
    this->~Matrix();
  }catch(std::exception* e){}
  memcpy( &(this->row), &(copiedMatrix.row), sizeof(copiedMatrix.row) );
  memcpy( &(this->col), &(copiedMatrix.col), sizeof(copiedMatrix.col) );
  this->matrix = new float*[this->row];
  for (int i = 0; i < row; i++){
    this->matrix[i] = new float[this->col];
    for (int j = 0; j < this->col; j++) {
      memcpy( &(this->matrix[i][j]), &(copiedMatrix.matrix[i][j]), sizeof(copiedMatrix.matrix[i][j]) );
    }
  }
}

Matrix::Matrix(Matrix&& movedMatrix){
 move(movedMatrix);
}
Matrix& Matrix::operator=(Matrix&& movedMatrix){
  move(movedMatrix);
  return *this;
}
void Matrix::move(Matrix& movedMatrix){
  movedMatrix.checkAllocation();
  if( this == &movedMatrix) return;
  this->row = movedMatrix.row;
  movedMatrix.row = 0;
  this->col = movedMatrix.col;
  movedMatrix.col = 0;
  this->matrix = movedMatrix.matrix;
  movedMatrix.matrix = NULL;
}


Matrix::~Matrix(){
  for (int i = 0; i < this->row; i++)
    delete[] this->matrix[i];
  delete[] this->matrix;

}


void Matrix::fill() {
  this->checkAllocation();
  for (int i = 0; i < this->row; i++)
    for (int j = 0; j < this->col; j++)
      this->matrix[i][j] = i+j;
}


void Matrix::addValue(const float value, const int row, const int col){
  this->checkAllocation();
  if(row < 0 || col < 0 || row >= this->row || col >= this->col){
    throw new MatrixException((char*)("Unsupported matrix dimensions"));
  }
  this->matrix[row][col] += value;
}


float Matrix::computeDeterminant() const {
  this->checkAllocation();
  if(this->row != this->col){
    throw new MatrixException((char*)("Unsupported matrix dimensions"));
    return 0;
  }
  float ** m = this->matrix;
  float sum = 0;
  if(this->row == 1) return this->matrix[0][0];
  for (int i = 0; i < this->row; i++) {
    Matrix temp = this->getMinor(i,0);
    sum += pow(-1, i) * this->matrix[i][0] * temp.computeDeterminant();
  }
  return sum;
}
Matrix Matrix::getMinor(const int row, const int col) const{
  this->checkAllocation();
  if(row < 0 || col < 0 || row >= this->row || col >= this->col){
    throw new MatrixException((char*)("Unsupported matrix dimensions"));
  }
  Matrix returnMatrix(this->row - 1, this->col - 1);
  float* vals = new float[returnMatrix.getRow() * returnMatrix.getCol()];
  int k = 0;

  for (int i = 0; i < this->row; i++)
    for (int j = 0; j < this->col; j++)
      if(i != row && j != col){
        vals[k] = this->matrix[i][j];
        k++;
      }

  for (int i = 0; i < returnMatrix.getRow(); i++)
    for (int j = 0; j < returnMatrix.getCol(); j++)
      returnMatrix.addValue(vals[i * returnMatrix.getRow()+ j], i, j);
  return std::move(returnMatrix);
}


Matrix operator+(const float f, const Matrix& matrix){
  matrix.checkAllocation();
  Matrix returnMatrix(matrix.getRow(),matrix.getCol());
  for (int i = 0; i < matrix.getRow(); i++)
    for(int j = 0; j < matrix.getCol(); j++)
      if(i == j){
        returnMatrix.addValue( matrix.getMatrix()[i][j] + f, i, j);
      }else{
        returnMatrix.addValue( matrix.getMatrix()[i][j], i, j);
      }
  return std::move(returnMatrix);
};
Matrix operator+(const Matrix& matrix, const float f){
  return f + matrix;
}
Matrix& Matrix::operator+= (const float f){
  this->checkAllocation();
  for (int i = 0; i < std::min(this->row, this->col); i++)
    this->matrix[i][i] += f;
}
Matrix operator-(const Matrix& matrix, const float f){
  matrix.checkAllocation();
  return (-f) + matrix;
}
Matrix operator-(const float f, const Matrix& matrix){
  matrix.checkAllocation();
  return f + (-1.0f) * matrix;
}
Matrix& Matrix::operator-=(const float f){
  this->checkAllocation();
  for (int i = 0; i < std::min(this->row, this->col); i++)
    this->matrix[i][i] -= f;
}
Matrix operator*(const float f, const Matrix& matrix){
  matrix.checkAllocation();
  Matrix returnMatrix(matrix.getRow(),matrix.getCol());
  for (int i = 0; i < matrix.getRow(); i++)
    for(int j = 0; j < matrix.getCol(); j++)
        returnMatrix.addValue( matrix.getMatrix()[i][j] * f, i, j);
  return std::move(returnMatrix);
}
Matrix operator*(const Matrix& matrix, const float f){
  return f * matrix;
}
Matrix& Matrix::operator*=(const float f){
  this->checkAllocation();
  for (int i = 0; i < this->row; i++)
    for (int j = 0; j < this->col; j++)
      this->matrix[i][j] *= f;
}

Matrix operator+(const Matrix& matrix1, const Matrix& matrix2){
  matrix1.checkAllocation();
  matrix2.checkAllocation();
  if(matrix1.getRow() != matrix2.getRow() || matrix1.getCol() != matrix2.getCol()){
    throw new MatrixException((char*)("Unsupported matrix dimensions"));
  }

  Matrix returnMatrix(matrix1.getRow(),matrix1.getCol());
  for (int i = 0; i < matrix1.getRow(); i++)
    for(int j = 0; j < matrix1.getCol(); j++)
        returnMatrix.addValue( matrix1.getMatrix()[i][j] + matrix2.getMatrix()[i][j], i, j);
  return std::move(returnMatrix);
}
Matrix& Matrix::operator+=(const Matrix& matrix2){
  this->checkAllocation();
  matrix2.checkAllocation();
  if(this->getRow() != matrix2.getRow() || this->getCol() != matrix2.getCol()){
    throw new MatrixException((char*)("Unsupported matrix dimensions"));
  }

  for (int i = 0; i < this->getRow(); i++)
    for(int j = 0; j < this->getCol(); j++)
      this->matrix[i][j]+= matrix2.getMatrix()[i][j];
}
Matrix operator-(const Matrix& matrix1, const Matrix& matrix2){
  matrix1.checkAllocation();
  matrix2.checkAllocation();
  if(matrix1.getRow() != matrix2.getRow() || matrix1.getCol() != matrix2.getCol()){
    throw new MatrixException((char*)("Unsupported matrix dimensions"));
  }

  Matrix returnMatrix(matrix1.getRow(),matrix1.getCol());
  for (int i = 0; i < matrix1.getRow(); i++)
    for(int j = 0; j < matrix1.getCol(); j++)
        returnMatrix.addValue( matrix1.getMatrix()[i][j] - matrix2.getMatrix()[i][j], i, j);
  return std::move(returnMatrix);
}
Matrix& Matrix::operator-=(const Matrix& matrix2){
  this->checkAllocation();
  matrix2.checkAllocation();
  if(this->getRow() != matrix2.getRow() || this->getCol() != matrix2.getCol()){
    throw new MatrixException((char*)("Unsupported matrix dimensions"));
  }

  for (int i = 0; i < this->getRow(); i++)
    for(int j = 0; j < this->getCol(); j++)
      this->matrix[i][j]-= matrix2.getMatrix()[i][j];
}
Matrix operator*(const Matrix& matrix1, const Matrix& matrix2){
  matrix1.checkAllocation();
  matrix2.checkAllocation();
  if(matrix1.getCol() != matrix2.getRow()){
    throw new MatrixException((char*)("Unsupported matrix dimensions"));
  }

  Matrix returnMatrix(matrix1.getRow(),matrix2.getCol());
  for (int i = 0; i < matrix1.getRow(); i++)
    for(int j = 0; j < matrix2.getCol(); j++)
      for(int k = 0; k < matrix1.getCol(); k++)
        returnMatrix.addValue( matrix1.getMatrix()[i][k] * matrix2.getMatrix()[k][j], i, j);
  return std::move(returnMatrix);
}


Matrix Matrix::computeInverse() const {
  this->checkAllocation();
  float det = this->computeDeterminant();
  if(this->row != this->col || this->row > 3 || this->row < 2 ) throw new MatrixException((char*)("Unsupported matrix dimensions"));
  if( det == 0 ) throw new MatrixException((char*)"Determinant is 0!");

  Matrix returnMatrix(this->row,this->col);

  if(this->row == 2){
    returnMatrix.addValue(this->matrix[1][1], 0, 0);
    returnMatrix.addValue(-(this->matrix[1][0]), 1, 0);
    returnMatrix.addValue(-(this->matrix[0][1]), 0, 1);
    returnMatrix.addValue(this->matrix[0][0], 1, 1);
  }else{
    returnMatrix.addValue(this->matrix[1][1] * this->matrix[2][2] + this->matrix[1][2] * this->matrix[2][1], 0, 0);
    returnMatrix.addValue(this->matrix[1][2] * this->matrix[2][0] + this->matrix[1][0] * this->matrix[2][0], 1, 0);
    returnMatrix.addValue(this->matrix[1][0] * this->matrix[2][1] + this->matrix[1][1] * this->matrix[2][2], 2, 0);

    returnMatrix.addValue(this->matrix[0][2] * this->matrix[2][1] + this->matrix[0][1] * this->matrix[2][2], 0, 1);
    returnMatrix.addValue(this->matrix[0][0] * this->matrix[2][2] + this->matrix[0][2] * this->matrix[2][0], 1, 1);
    returnMatrix.addValue(this->matrix[0][1] * this->matrix[2][0] + this->matrix[0][0] * this->matrix[2][1], 2, 1);

    returnMatrix.addValue(this->matrix[0][1] * this->matrix[1][2] + this->matrix[0][2] * this->matrix[1][1], 0, 2);
    returnMatrix.addValue(this->matrix[0][2] * this->matrix[1][0] + this->matrix[0][0] * this->matrix[1][2], 1, 2);
    returnMatrix.addValue(this->matrix[0][0] * this->matrix[1][1] + this->matrix[0][1] * this->matrix[1][0], 2, 2);
  }

  return (1/det) * returnMatrix;
}


Matrix Matrix::divideMatrices(const Matrix& divisor) const{
  this->checkAllocation();
  divisor.checkAllocation();
  try{
    return *this * divisor.computeInverse();
  }catch(std::exception* e){
    throw new MatrixException((char*)"No unique solution");
  }
}



float** Matrix::getMatrix() const {return this->matrix;}
int Matrix::getRow() const {return this->row;}
int Matrix::getCol() const {return this->col;}


void Matrix::checkAllocation() const{
  if(this->row == 0 || this->col == 0 || this->matrix == NULL)
    throw new MatrixException((char*)("Matrix not allocated"));
}
