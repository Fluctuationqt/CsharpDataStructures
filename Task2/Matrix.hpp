#include <vector>
#include <iostream>
class Matrix {
private:
	std::vector<std::vector<int>*>* m_matrix;

public:
	Matrix() {
		
	}

	Matrix(int n) {
		m_matrix = new std::vector<std::vector<int>*>(n);
		int temp;
		for (int y = 0; y < n; y++) {
			m_matrix->at(y) = new std::vector<int>(n);
			for (int x = 0; x < n; x++) {
				std::cout << "[" << y << "][" << x << "]=";
				std::cin >> temp;
				m_matrix->at(y)->at(x) = temp;
			}
		}
	}

	Matrix(int n, bool isSolved) {
		m_matrix = new std::vector<std::vector<int>*>(n);
		int i = 1;
		for (int y = 0; y < n; y++) {
			m_matrix->at(y) = new std::vector<int>(n);
			for (int x = 0; x < n; x++) {
				m_matrix->at(y)->at(x) = (i % (n*n) == 0) ? 0 : i++;
				std::cout << i % (n*n) << std::endl;
			}
		}
	}

	Matrix(Matrix& other) {
		m_matrix = new std::vector<std::vector<int>*>(other.getSize());
		for (int y = 0; y < other.getSize(); y++) {
			m_matrix->at(y) = new std::vector<int>(other.getSize());
			for (int x = 0; x < other.getSize(); x++) {
				m_matrix->at(y)->at(x) = other.getElement(std::pair<int, int>(x, y));
			}
		}
	}

	// Moves matrix element from x, y --> to x, y
	void moveElement(std::pair<int, int> from, std::pair<int, int> to) {
		if (!inMatrix(from) || !inMatrix(to)) {
			throw std::invalid_argument("Position argument outside of matrix bounds");
		}

		std::swap(m_matrix->at(to.second)->at(to.first),
			m_matrix->at(from.second)->at(from.first));
	}
	
	int getElement(std::pair<int,int> pos) {
		if (!inMatrix(pos)) {
			throw std::invalid_argument("Position argument outside of matrix bounds");
		}

		return m_matrix->at(pos.second)->at(pos.first);
	}

	std::vector<std::vector<int>*>* getData() {
		return m_matrix;
	}

	int getSize() {
		return m_matrix->size();
	}

	bool inMatrix(std::pair<int, int> pos) {
		bool y = (pos.second >= 0) && (pos.second < m_matrix->size());
		bool x = (pos.first >= 0) && (pos.first < m_matrix->size());
		return y && x;
	}
	
	/// TODO: CHECK IF DESTRUCTION NEEDS LOOKING INSIDE Y VECTOR
	~Matrix() {
		for (int i = 0; i < m_matrix->size(); i++) {
			delete m_matrix->at(i);
		}
		delete m_matrix;
	}
	
	void print() {
		for (int y = 0; y < m_matrix->size(); y++) {
			std::vector<int>* row = m_matrix->at(y);
			for (int x = 0; x < m_matrix->size(); x++) {
				std::cout << row->at(x) << " ";
			}
			std::cout << std::endl;
		}
	}
};