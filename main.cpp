#include <iostream>
#include <vector>
#include <stdexcept>


// class FastMatrix {
// 	pass;
// }



class Matrix {
private:
	std::vector<std::vector<double>> data;
	int rows;
	int cols;
public:
	Matrix(int r, int c):
		rows(r), cols(c), data(r, std::vector<double>(c)) {} // init
	Matrix(int r, int c, double val):
		rows(r), cols(c), data(r, std::vector<double>(c, val)) {} // init
	
	/*
	easy init of Matrix
	Matrix mat = {
		{1.0, 2.0, 3.0},
		{4.0, 5.0, 6.0}
	};
	*/
	
	Matrix(std::initializer_list<std::initializer_list<double>> init):
		rows(init.size()),
		cols(init.begin()->size()), // begin points to start of vector
		data()
	{
		data.reserve(rows); // allocate memory for (rows) number of vectors, prevents reallocation when you add rows and doesn't create new ones
		for (auto& row : init) { // & eliminates the need to copy each row, it's just a reference 
			if (static_cast<int>(row.size()) != cols)
				throw std::invalid_argument("Row length input inconsistent");

			data.emplace_back(row); // inplace
		}
	}

	// make specials
	static Matrix zeros(int r, int c) {
		return Matrix(r, c, 0.0);
	}

	static Matrix ones(int r, int c) {
		return Matrix(r, c, 1.0);
	}

	static Matrix filled(int r, int c, double val) {
		return Matrix(r, c, val);
	}

	static Matrix identity(int n) {
		Matrix m = zeros(n,n);
		for (int i = 0; i < n; ++i) {
			m(i, i) = 1.0;
		}
		return m;
	}



	// retrieve data

	double& operator()(int i, int j) {
		if (i<0 || i >= rows || j < 0 || j >= cols) throw std::out_of_range("Index"); // give error if user gives a non-existent entry
		return data[i][j];
	}

	const double& operator()(int i, int j) const { // so read-only matrices can be read
		if (i<0 || i >= rows || j < 0 || j >= cols) throw std::out_of_range("Index"); // give error if user gives a non-existent entry
		return data[i][j];
	}
		
	std::vector<double>& operator[](int i) {
		return data[i];
	}
	
	const std::vector<double>& operator[](int i) const {
		return data[i];
	}

	int nRows() const {
		return rows;
	}
	int nCols() const {
		return cols;
	}

	// Matrix operations
	// basic multiplication algorithm. O(n^3)
	Matrix multiply(const Matrix& m) const { // multiplication: must have an p x q * q x r, returns p x r. 
		if (cols != m.rows) throw std::invalid_argument("Inner dimension mismatch");
		Matrix res(rows, m.cols);
		for (int i=0; i<rows; i++) {
			for (int j=0; j<m.cols; ++j) {
				double sum = 0;
				for (int k=0; k < cols; ++k) {
					sum += (*this)(i,k) * m(k,j);
				}
				res(i,j) = sum;
			}
		}
		return res;
	}

	Matrix add(const Matrix& m) const {
		if ((cols != m.cols) || (rows != m.rows)) throw std::invalid_argument("Inner dimension mismatch");
		Matrix res {rows, cols};
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				res[i][j] = data[i][j] + m[i][j]; // if i were to use this, itd be (*this)[i][j], the * dereferences the pointer
			}

		}
		return res;

	}


	double mDot(const Matrix& m) const { // dot product of two 1-row, equal-cols matrices
	   if (rows != 1 || m.rows != 1 || cols != m.cols) throw std::invalid_argument("Dot requires two equal sized row vectors");
	   double res = 0.0;
	   for (int i=0; i < cols; i++) {
	  res += (*this)(0,i) * m(0,i);
	
	   }
	   return res;
	}
	
	// need to add addition, multiplication (addition*-1)
	
	// Print Matrix
	void print() const {
		for (int i=0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				std::cout << data[i][j] << ' ';
			}
			std::cout << '\n';
		}
	}
};

	Matrix operator*(const Matrix& A, const Matrix& B) {
		return A.multiply(B);
	}

	Matrix operator*(const Matrix& A, double scalar) { // this is something that can be vectorized
		int rows {A.nRows()};
		int cols {A.nCols()};
		Matrix result{rows, cols};

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				result(i, j) = A(i, j) * scalar;
			}
		}
	}



int main() {
	Matrix mat1 = {
		{1.0, 2.0, 3.0},
		{4.0, 5.0, 6.0}
	};
		
	Matrix mat2 = {
		{1.0, 2.0},
		{3.0, 4.0},
		{5.0, 6.0}
	};
	Matrix mat3 = {{1.0,2.0,3.0}};
	Matrix mat4 = {{4.0,5.0,6.0}};
	Matrix C = mat1.multiply(mat2);
	double dp = mat4.mDot(mat3);
	C.print();
	for (double val : C[0]) {
	std::cout << val << ' ';
	}
	std::cout << '\n';
	std::cout << C[0][1] << '\n';
	std::cout << dp;
		
	return 0;
}
