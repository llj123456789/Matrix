#define  _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>

#include"matrix.h"

using namespace std;



int main()
{
	Matrix<int> m(3,3);
	//m.stdSetMatrix(3,3);
	vector<int> v={1,2,3};
	vector<int> v1={4,5,6};
	vector<int> v2={7,8,9};
	vectorSpaceInt vs= { v,v1,v2 };
	m.setMatrix(vs);
	m.stdPrintMatrix();
	Matrix<int> c;
	c = m;
	c.stdPrintMatrix();
	c *= c;
	c.stdPrintMatrix();

}