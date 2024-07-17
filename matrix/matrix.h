#pragma once
#define  _CRT_SECURE_NO_WARNINGS
#include<cstdarg>
#include<vector>
#include<stdexcept>

using namespace std;



//判断奇偶排列
bool isOddPermutation(int* a, int n);



//矩阵//Vector can be seen as a special matrix
template<class TYPE>
class Matrix
{
private:
	vector<vector<TYPE>> matrix;
	int row;
	int col;
	bool Blocked;//是否分块
	bool canInversed;//是否可逆

public:
	Matrix(int r=0, int c=0);//非分块矩阵初始化
	Matrix(int n, Matrix &a, ...);//分块矩阵初始化
	Matrix(const Matrix& m);//拷贝构造函数
	virtual ~Matrix();
//set
	bool stdSetMatrix(int row,int col);	//设置矩阵
	bool stdSetMatrix();//设置矩阵
	bool stdSetRow(int row);//设置行
	bool setRow(int r,vector<TYPE> a);//设置行
	bool stdSetCol(int col);//设置列
	bool setCol(int c,vector<TYPE> a);//设置列
	bool setElem(int r,int c,TYPE elem);//设置元素
	bool zeros(int row,int col);//设置为0矩阵
	bool zeros();//设置为0矩阵


	bool setMatrix(vector<vector<TYPE>> a);//设置矩阵//n为元素个数
	void stdPrintMatrix();//打印矩阵
	void printMatrix(fstream &f);//打印矩阵
//basic operation
	//basic algorithm operation
	Matrix operator+(const Matrix& m);
	Matrix operator-(const Matrix& m);
	Matrix operator*(const Matrix& m);
	Matrix operator*(const int& n);
	Matrix operator/(const int& n);
	Matrix operator/(const Matrix& m); //新定义矩阵除法 a/b=a*b^(-1)
	Matrix operator=(const Matrix& m);
	bool operator==(const Matrix& m);
	bool operator!=(const Matrix& m);
	Matrix operator+=(const Matrix& m);
	Matrix operator-=(const Matrix& m);
	Matrix operator*=(const Matrix& m);
	Matrix operator*=(const int& n);
	Matrix operator/=(const Matrix& m);
	Matrix operator/=(const int& n);
	vector<TYPE>& operator[](int i);//取列

	ostream & operator<<(ostream& os); // print matrix
	istream & operator>>(istream& is); // set matrix
	// 

//advanced operation

	//advanced algorithm operation
	Matrix power(int n);//幂次
	Matrix operator^(int n);//幂次
	Matrix operator^=(int n);//幂次

	//block operation
	//if CanBeBlocked, then
	//block operation
	Matrix Multiply_block(const Matrix& m);//运用分块矩阵乘法
	Matrix Add_block(const Matrix& m);//运用分块矩阵加法
	Matrix Subtract_block(const Matrix& m);//运用分块矩阵减法
	Matrix Transpose_block();//运用分块矩阵转置
	Matrix toNormal();//转化为非分块矩阵

	
	//judge
	//bolck judge
	bool isBlockDiagonal();//判断是否为分块对角矩阵
	bool isBlocked();//判断是否分块矩阵
	//basic judge
	bool isInversed();//是否可逆
	bool isSquare();//方阵
	bool isSymmetric();//对称
	bool isSkewSymmetric();//反对称
	bool isIdentity();//单位矩阵
	bool isUpperDiagonal();//上三角
	bool isLowerDiagonal();//下三角
	bool isDiagonal();//对角
	bool isScalar();//标量
	bool isZero();//零
	bool isEchelon();//阶梯
	bool Jordan();//约当//行最简形
	bool isOrthogonal();//正交//Orthogonal matrix
	bool iscolVector();//列向量
	bool isrowVector();//行向量

	//self calculate
	void swapEle(int r1,int c1,int r2,int c2);//交换元素
	void swapRow(int i,int j);//交换行
	void swapCol(int i,int j);//交换列
	void toTranspose();//转置
	void toEchelon();//阶梯形
	void toJordan();//约当形
	void toAdjordan();//伴随形
	void toDiagonal();//对角化
	void toBlocked(int r,int c);//分块化
	void stripRow(int r);//去行
	void stripCol(int c);//去列
	void addRow(int r,int n=1);//加行
	void addCol(int c,int n=1);//加列
	
	//get
	//basic get
	Matrix inverse();//逆矩阵
	Matrix adjoint();//伴随矩阵
	Matrix transpose();//转置矩阵
	TYPE getMinor(int r,int c);//取余子式
	TYPE getAlgebraic(int r,int c);//取代数余子式
	Matrix getRow(int i);//取行
	Matrix getCol(int i);//取列
	Matrix getDiagonal();//取对角线
	Matrix getUpperDiagonal();//取上三角,else default 0
	Matrix getLowerDiagonal();//取下三角,else default 0
	TYPE getElem(int r,int c);//取元素
	TYPE Det();//取行列式，递归法，行列式展开定理
	int Rank();//取秩
	

	TYPE Det_with_old();//取行列式//不同行不同列硬解//奇偶排列

	//block get
	Matrix getBlock(int r, int c);//取块
};

//













#define  _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<vector>
#include"matrix.h"

using namespace std;



template<class TYPE>
Matrix<TYPE>::Matrix(int row, int col)
{
	this->row = row;
	this->col = col;
	for (int i = 0; i < col; i++)
	{
		this->matrix.push_back(vector<TYPE>(row));
		for (int j = 0; j < row; j++)
		{
			this->matrix[i][j] = 0;
		}
	}
}

template<class TYPE>
Matrix<TYPE>::Matrix(const Matrix& m)
{
	this->row = m.row;
	this->col = m.col;
	for (int i = 0; i < col; i++)
	{
		this->matrix.push_back(vector<TYPE>(row));
		for (int j = 0; j < row; j++)
		{
			this->matrix[i][j] = 0;
		}
	}
	for (int i = 0; i < m.col; i++)
	{
		for (int j = 0; j < m.row; j++)
		{
			this->matrix[i][j] = m.matrix[i][j];
		}
	}
}
template<class TYPE>
Matrix<TYPE>::~Matrix()
{
	for (int i = 0; i < this->col; i++)
	{
		this->matrix[i].clear();
	}
	this->matrix.clear();
}

template<class TYPE>
bool Matrix<TYPE>::stdSetMatrix(int row, int col)
{
	for (int i = 0; i < this->col; i++)
	{
		this->matrix[i].clear();
	}
	this->matrix.clear();

	this->row = row;
	this->col = col;
	for (int i = 0; i < col; i++)
	{
		this->matrix.push_back(vector<TYPE>(row));
		for (int j = 0; j < row; j++)
		{
			this->matrix[i][j] = 0;
		}
	}
	cout << "please input the matrix(cordnig to row):" << endl;
	for (int i = 0; i < this->row; i++)
	{
		for (int j = 0; j < this->col; j++)
		{
			cin >> this->matrix[j][i];
		}
	}
	return true;
}

template<class TYPE>
bool Matrix<TYPE>::stdSetMatrix()
{
	cout << "please input the matrix(cordnig to row):" << endl;
	for (int i = 0; i < this->row; i++)
	{
		for (int j = 0; j < this->col; j++)
		{
			cin >> this->matrix[j][i];
		}
	}
	return true;
}

template<class TYPE>
bool Matrix<TYPE>::setMatrix(vector <vector<TYPE>> a)
{

	if (this->col != a.size() || this->row != a[0].size())
	{
		cout << "Do you want to change size of matrix? To adapt new(y/n)" << endl;
		char c;
		cin >> c;
		if (c == 'y' || c == 'Y')
		{
		}
		else
		{
			cout << "set matrix failed" << endl;
			return false;
		}
	}
	for (int i = 0; i < this->col; i++)
	{
		this->matrix[i].clear();
	}
	this->matrix.clear();
	for (int i = 0; i < col; i++)
	{
		this->matrix.push_back(vector<TYPE>(row));
		for (int j = 0; j < row; j++)
		{
			this->matrix[i][j] = 0;
		}
	}
	this->col = a.size();
	this->row = a[0].size();
	this->matrix = a;
	return true;
}
template<class TYPE>
bool Matrix<TYPE>::zeros(int row, int col)
{
	for (int i = 0; i < this->col; i++)
	{
		this->matrix[i].clear();
	}
	this->matrix.clear();
	this->row = row;
	this->col = col;
	for (int i = 0; i < this->col; i++)
	{
		for (int j = 0; j < this->row; j++)
		{
			this->matrix[i][j] = 0;
		}
	}
	return true;
}

template<class TYPE>
bool Matrix<TYPE>::zeros()
{

	for (int i = 0; i < this->col; i++)
	{
		for (int j = 0; j < this->row; j++)
		{
			this->matrix[i][j] = 0;
		}
	}
	return true;
}

template<class TYPE>
void Matrix<TYPE>::stdPrintMatrix()
{
	for (int j = 0; j < this->row; j++)
	{
		for (int i = 0; i < this->col; i++)
		{
			std::cout << this->matrix[i][j] << " ";
		}
		std::cout << endl;
	}
}
template<class TYPE>
void Matrix<TYPE>::printMatrix(fstream& f)
{
	if (f.fail())
	{
		cout << "open file failed" << endl;
		return;
	}
	for (int j = 0; j < this->row; j++)
	{
		for (int i = 0; i < this->col; i++)
		{
			f << this->matrix[i][j] << " ";
		}
		f << endl;
	}
}

template<class TYPE>
Matrix<TYPE> Matrix<TYPE>::operator+(const Matrix<TYPE>& m)
{
	Matrix<TYPE> temp(this->row, this->col);
	if (this->row != m.row || this->col != m.col)
	{
		cout << "the two matrix can not add" << endl;
		return temp;
	}
	for (int i = 0; i < this->col; i++)
	{
		for (int j = 0; j < this->row; j++)
		{
			temp.matrix[i][j] = this->matrix[i][j] + m.matrix[i][j];
		}
	}
	return temp;
}

template<class TYPE>
Matrix<TYPE> Matrix<TYPE>::operator-(const Matrix<TYPE>& m)
{
	Matrix<TYPE> temp(this->row, this->col);
	if (this->row != m.row || this->col != m.col)
	{
		cout << "the two matrix can not sub" << endl;
		return temp;
	}
	for (int i = 0; i < this->col; i++)
	{
		for (int j = 0; j < this->row; j++)
		{
			temp.matrix[i][j] = this->matrix[i][j] - m.matrix[i][j];
		}
	}
	return temp;
}

template<class TYPE>
Matrix<TYPE> Matrix<TYPE>::operator*(const Matrix<TYPE>& m)
{
	Matrix<TYPE> temp(this->row, m.col);
	if (this->col != m.row)
	{
		cout << "the two matrix can not mul" << endl;
		return temp;
	}
	for (int k = 0; k < m.col; k++)
		for (int i = 0; i < this->row; i++)
		{
			for (int j = 0; j < this->col; j++) //this->col==m.row
			{
				temp[k][i] += this->matrix[j][i] * m.matrix[k][j];
			}
		}
	return temp;
}

template<class TYPE>
Matrix<TYPE> Matrix<TYPE>::operator*(const int& a)
{
	Matrix<TYPE> temp(this->row, this->col);
	for (int i = 0; i < this->col; i++)
	{
		for (int j = 0; j < this->row; j++)
		{
			temp.matrix[i][j] = this->matrix[i][j] * a;
		}
	}
	return temp;
}

template<class TYPE>
Matrix<TYPE> Matrix<TYPE>::operator/(const int& a)
{
	Matrix<TYPE> temp(this->row, this->col);
	for (int i = 0; i < this->col; i++)
	{
		for (int j = 0; j < this->row; j++)
		{
			temp.matrix[i][j] = this->matrix[i][j] / a;
		}
	}
	return temp;
}

template<class TYPE>
Matrix<TYPE> Matrix<TYPE>::operator/(const Matrix<TYPE>& m)
{
	Matrix<TYPE> temp(this->row, this->col);
	if (m.row != m.col)
	{
		cout << "the matrix can not be inversed" << endl;
		return temp;
	}
	temp = (*this) * m.inverse();
	return temp;
}

template<class TYPE>
Matrix<TYPE> Matrix<TYPE>::operator=(const Matrix<TYPE>& m)
{
	for (int i = 0; i < this->col; i++)
	{
		this->matrix[i].clear();
	}
	this->matrix.clear();
	this->row = m.row;
	this->col = m.col;
	for (int i = 0; i < col; i++)
	{
		this->matrix.push_back(vector<TYPE>(row));
		for (int j = 0; j < row; j++)
		{
			this->matrix[i][j] = 0;
		}
	}
	for (int i = 0; i < m.col; i++)
	{
		for (int j = 0; j < m.row; j++)
		{
			this->matrix[i][j] = m.matrix[i][j];
		}
	}
	return *this;
}

template<class TYPE>
vector<TYPE>& Matrix<TYPE>::operator[](int i)
{
	return this->matrix[i];
}

template<class TYPE>
ostream& Matrix<TYPE>::operator<<(ostream& os)
{
	for (int j = 0; j < this->row; j++)
	{
		for (int i = 0; i < this->col; i++)
		{
			os << this->matrix[i][j] << " ";
		}
		os << endl;
	}
	return os;
}

template<class TYPE>
istream& Matrix<TYPE>::operator>>(istream& is)
{
	for (int j = 0; j < this->row; j++)
	{
		for (int i = 0; i < this->col; i++)
		{
			is >> this->matrix[i][j];
		}
	}
	return is;
}

template<class TYPE>
bool Matrix<TYPE>::operator==(const Matrix<TYPE>& m)
{
	if (this->row != m.row || this->col != m.col)
	{
		return false;
	}
	for (int i = 0; i < this->col; i++)
	{
		for (int j = 0; j < this->row; j++)
		{
			if (this->matrix[i][j] != m.matrix[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

template<class TYPE>
bool Matrix<TYPE>::operator!=(const Matrix<TYPE>& m)
{
	if (this->row != m.row || this->col != m.col)
	{
		return true;
	}
	for (int i = 0; i < this->col; i++)
	{
		for (int j = 0; j < this->row; j++)
		{
			if (this->matrix[i][j] != m.matrix[i][j])
			{
				return true;
			}
		}
	}
	return false;
}

template<class TYPE>
Matrix<TYPE> Matrix<TYPE>::operator+=(const Matrix<TYPE>& m)
{
	if (this->row != m.row || this->col != m.col)
	{
		cout << "the two matrix can not add" << endl;
		return *this;
	}
	for (int i = 0; i < this->col; i++)
	{
		for (int j = 0; j < this->row; j++)
		{
			this->matrix[i][j] += m.matrix[i][j];
		}
	}
	return *this;
}

template<class TYPE>
Matrix<TYPE> Matrix<TYPE>::operator-=(const Matrix<TYPE>& m)
{
	if (this->row != m.row || this->col != m.col)
	{
		cout << "the two matrix can not sub" << endl;
		return *this;
	}
	for (int i = 0; i < this->col; i++)
	{
		for (int j = 0; j < this->row; j++)
		{
			this->matrix[i][j] -= m.matrix[i][j];
		}
	}
	return *this;
}

template<class TYPE>
Matrix<TYPE> Matrix<TYPE>::operator*=(const Matrix<TYPE>& m)
{
	if (this->col != m.row)
	{
		cout << "the two matrix can not mul" << endl;
		return *this;
	}
	Matrix<TYPE> temp(this->row, m.col);
	for (int k = 0; k < m.col; k++)
		for (int i = 0; i < this->row; i++)
		{
			for (int j = 0; j < this->col; j++) //this->col==m.row
			{
				temp[k][i] += this->matrix[j][i] * m.matrix[k][j];
			}
		}
	*this = temp;
	return *this;
}

template<class TYPE>
Matrix<TYPE> Matrix<TYPE>::operator*=(const int& a)
{
	for (int i = 0; i < this->col; i++)
	{
		for (int j = 0; j < this->row; j++)
		{
			this->matrix[i][j] *= a;
		}
	}
	return *this;
}

template<class TYPE>
Matrix<TYPE> Matrix<TYPE>::operator/=(const Matrix<TYPE>& m)
{
	if (m.isSquare()==false)
	{
		cout << "the matrix can not be inversed" << endl;
		return *this;
	}
	
	*this = (*this) * m.inverse();
	

	return *this;
}

template<class TYPE>
Matrix<TYPE> Matrix<TYPE>::operator/=(const int& a)
{
	for (int i = 0; i < this->col; i++)
	{
		for (int j = 0; j < this->row; j++)
		{
			this->matrix[i][j] /= a;
		}
	}
	return *this;
}

template<class TYPE>
Matrix<TYPE> Matrix<TYPE>::power(int n)
{
	Matrix<TYPE> temp(this->row, this->col);
	if (temp.isSquare()==false)
	{
		cout << "the matrix can not power" << endl;
		return temp;
	}
	if (n == 0)
	{
		for (int i = 0; i < this->col; i++)
		{
			for (int j = 0; j < this->row; j++)
			{
				if (i == j)
				{
					temp.matrix[i][j] = 1;
				}
				else
				{
					temp.matrix[i][j] = 0;
				}
			}
		}
		return temp;
	}
	if (n < 0)
	{
		temp = this->inverse();
		n = -n;
	}
	else
	{
		temp = *this;
	}
	for (int i = 1; i < n; i++)
	{
		temp *= (*this);
	}
	return temp;
}

template<class TYPE>
Matrix<TYPE> Matrix<TYPE>::operator^(int n)
{
	return power(n);
}

template<class TYPE>
Matrix<TYPE> Matrix<TYPE>::operator^=(int n)
{
	*this = power(n);
	return *this;
}


template<class TYPE>
bool Matrix<TYPE>::stdSetRow(int row)
{
	if (row < 0)
	{
		cout << "row can not be negative" << endl;
		return false;
	}
	if (row >= this->row)
	{
		cout << "row is out of range" << endl;
		return false;
	}
	for (int i = 0; i < this->col; i++)
	{
		std::cin >> this->matrix[i][row];
	}
	return true;
}

template<class TYPE>
bool Matrix<TYPE>::stdSetCol(int col)
{
	if (col < 0)
	{
		cout << "col can not be negative" << endl;
		return false;
	}
	if (col >= this->col)
	{
		cout << "col is out of range" << endl;
		return false;
	}
	for (int i = 0; i < this->row; i++)
	{
		std::cin >> this->matrix[col][i];
	}
	return true;
}

template<class TYPE>
bool Matrix<TYPE>::setRow(int row, vector<TYPE> a)
{
	if (row < 0)
	{
		cout << "row can not be negative" << endl;
		return false;
	}
	if (row >= this->row)
	{
		cout << "row is out of range" << endl;
		return false;
	}
	if (a.size() != this->col)
	{
		cout << "the size of vector is not equal to the col of matrix" << endl;
		return false;
	}
	for (int i = 0; i < this->col; i++)
	{
		this->matrix[i][row] = a[i];
	}
	return true;
}

template<class TYPE>
bool Matrix<TYPE>::setCol(int col, vector<TYPE> a)
{
	if (col < 0)
	{
		cout << "col can not be negative" << endl;
		return false;
	}
	if (col >= this->col)
	{
		cout << "col is out of range" << endl;
		return false;
	}
	if (a.size() != this->row)
	{
		cout << "the size of vector is not equal to the row of matrix" << endl;
		return false;
	}
	for(int i=0;i<this->row;i++)
	{
		this->matrix[col][i] = a[i];
	}
	return true;
}	


template<class TYPE>
bool Matrix<TYPE>::setElem(int r, int c, TYPE e)
{
	if (r < 0 || c < 0)
	{
		cout << "row or col can not be negative" << endl;
		return false;
	}
	if (r >= this->row || c >= this->col)
	{
		cout << "row or col is out of range" << endl;
		return false;
	}
	this->matrix[c][r] = e;
	return true;
}

template<class TYPE>
bool Matrix<TYPE>::isSquare()
{
	if (this->row == this->col)
	{
		return true;
	}
	return false;
}


typedef Matrix<int> MatrixInt;
typedef Matrix<double> MatrixDouble;
typedef Matrix<float> MatrixFloat;
typedef Matrix<char> MatrixChar;
typedef Matrix<string> MatrixString;
typedef Matrix<bool> MatrixBool;


typedef vector<int> vectorInt;
typedef vector<double> vectorDouble;
typedef vector<float> vectorFloat;
typedef vector<char> vectorChar;
typedef vector<string> vectorString;
typedef vector<bool> vectorBool;

typedef vector<vector<int>> vectorSpaceInt;
typedef vector<vector<double>> vectorSpaceDouble;
typedef vector<vector<float>> vectorSpaceFloat;
typedef vector<vector<char>> vectorSpaceChar;
typedef vector<vector<string>> vectorSpaceString;
typedef vector<vector<bool>> vectorSpaceBool;

