#include <iostream>
#include <vector>
#include <stdexcept>

class Matrix {
private:
	std::vector<std::vector<double>> data;
	int rows;
	int cols;
public:
	Matrix(int r, int c):
		rows(r), cols(c), data(r, std::vector<double>(c)) {} // init

	// easy init of Matrix
	/*
	Matrix mat = {
	    {1.0, 2.0, 3.0},
	    {4.0, 5.0, 6.0}
	};
	*/
	Matrix(std::initializer_list<std::initializer_list<double>> init):
		rows(init.size()),
		cols(init.begin()->size()),
		data()
	{
		data.reserve(rows);
		for (auto& row : init) {
			if (static_cast<int>(row.size()) != cols)
				throw std::invalid_argument("Row length input inconsistent");

			data.emplace_back(row);
		}
	}

	double& operator()(int i, int j) {
		if (i<0 || i >= rows || j < 0 || j >= cols) throw std::out_of_range("Index"); // give error if user gives a non-existent entry
		return data[i][j];
	}

	const double& operator()(int i, int j) const { // so read-only matrices can be read
		if (i<0 || i >= rows || j < 0 || j >= cols) throw std::out_of_range("Index"); // give error if user gives a non-existent entry
		return data[i][j];
	}
	
	std::vector<double>& operator[](int i) { // retrieval with indices
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
    	double mDot(const Matrix& m) const { // dot product of two 1-row, equal-cols matrices
	        if (rows != 1 || m.rows != 1 || cols != m.cols) throw std::invalid_argument("Dot requires two equal sized row vectors");
	        double res = 0.0;
	        for (int i=0; i < cols; i++) {
	            res += (*this)(0,i) * m(0,i);
        }
        return res;
    }
    // need to add addition, subtraction (addition*-1)
    
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
    
    Matrix C = mat1.multiply(mat2);
	C.print();
	return 0;
}
