#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <stdbool.h>
#include <math.h>

using namespace std;

template <int rows, int columns>
struct matrix {
	float values[columns][rows];
	
	typedef float column_type[rows];
	
	column_type& operator[](int i) {
		//return (values[i/rows][i%columns]);
		return values[i];
	}
	
	template<int r>
	float operator*(const matrix<r,1>& o) const {
		float dp = 0;
		int i;
		for (i = 0; i < r; i++) {
			dp += values[i][0]*o.values[i][0];
		}
		return dp;
	}
	
	matrix<rows,columns> unitvector() const {
		// find magnitude
		float n = 0;
		int i;
		for (i = 0; i < rows; i++) {
			n += values[0][i]*values[0][i];
		}
		n = sqrt(n);
	
		matrix<rows,columns> unit;
		for (i = 0; i < rows; i++) {
			unit.values[0][i] = values[0][i]/n;
		}
		return unit;
	}
	
	const float magnitude() {
		float n = 0;
		int i;
		for (i = 0; i < rows; i++) {
			n += values[0][i]*values[0][i];
		}
		return sqrt(n);
	}
			
	
//	template<int r, int c>
	matrix<rows,columns> operator*(const float& o) const {
		matrix<rows,columns> n;
		int ir, ic;
		for (ir = 0; ir < columns; ir++) {
			for (ic = 0; ic < rows; ic++) {
				n.values[ir][ic] = values[ir][ic] * o;
			}
		}
		return n;
	}
	
	template<int r, int c>
	matrix<r,c> operator+(const matrix<r,c>& o) const {
		matrix<r,c> n;// = zeromatrix<r,c>();
		int ir, ic;
		for (ir = 0; ir < r; ir++) {
			for (ic = 0; ic < c; ic++) {
				n.values[ic][ir] = values[ic][ir] + o.values[ic][ir];
			}
		}
		return n;
	}
	
	matrix<columns,rows> operator-() const {
		matrix<columns,rows> n;
		int ir, ic;
		for (ic = 0; ic < columns; ic++) {
			for (ir = 0; ir < rows; ir++) {
				n.values[ic][ir] = -values[ic][ir];
			}
		}
		return n;
	}

	matrix<columns,rows> operator-(const matrix<columns,rows>& o) const {
		matrix<columns,rows> n;
		int ir, ic;
		for (ic = 0; ic < columns; ic++) {
			for (ir = 0; ir < rows; ir++) {
				n.values[ic][ir] = values[ic][ir]-o.values[ic][ir];
			}
		}
		return n;
	}
	
	float* openglmatrix() {
		float* o = new float[rows*columns];
		int i,ii;
		for (i = 0; i < columns; i++) {
			for (ii = 0; ii < rows; ii++) {
				o[i*rows + ii] = values[i][ii];
			}
		}
		return o;
	}
};

template<int m1r,int m1c,int m2c>
matrix<m1r,m2c> multiplymatrices(
	const matrix<m1r, m1c>& m1,
	const matrix<m1c, m2c>& m2) {
	struct matrix<m1r,m2c> m3;
	int i, ii, iii;
	for (i = 0; i < m1r; i++) {
		for (ii = 0; ii < m2c; ii++) {
			m3.values[ii][i] = 0;
			for (iii = 0; iii < m1c; iii++) {
				m3.values[ii][i] += m1.values[iii][i]*m2.values[ii][iii];
			}
		}
	}
	return m3;
}

template<int mr,int mc>
matrix<mr,mc> zeromatrix() {
	struct matrix<mr, mc> m;
	int i, ii;
	for (i = 0; i < mr; i++) {
		for (ii = 0; ii < mc; ii++) {
			m.values[ii][i] = 0;
		}
	}
	return m;
}

template<int s,int>
matrix<s,s> identitymatrix() {
	struct matrix<s, s> m;
	int i, ii;
	for (i = 0; i < s; i++) {
		for (ii = 0; ii < s; ii++) {
			m.values[ii][i] = (i==ii)?1:0;
		}
	}
	return m;
}

template<int mr, int mc>
void printmatrix(const struct matrix<mr, mc> m) {
	int i, ii;
	for (i = 0; i < mr; i++) {
		for (ii = 0; ii < mc; ii++) {
			cout << m.values[ii][i] << " ";
		}
		cout << endl;
	}
}

matrix<4,1> multiplyquaternions(matrix<4,1> a, matrix<4,1> b);
matrix<3,1> rotatevectorbyquaternion(matrix<3,1> v, matrix<4,1> q);
matrix<4,1> quaternioncougate(matrix<4,1> a);
matrix<4,1> quaternionfromaxis(matrix<3,1> v, float angle);
matrix<4,4> quaterniontomatrix(matrix<4,1> q);
matrix<4,1> slowquaternionrotation(matrix<4,1> q, float m);

struct ray {
	matrix<3,1> start, direction;
};

#endif
