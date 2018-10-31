#include "Matrix.hpp"
using namespace std;
class Board {
private:
	std::pair<int, int> m_hole;
	Matrix* m_field;
	
	std::pair<Matrix*, std::pair<int,int>> Move(std::pair<int, int> to) {
		Matrix* newField = new Matrix(*m_field);
		std::pair<int, int> from = m_hole;
		newField->moveElement(from, to); // throws exception if outside bounds
		return std::pair<Matrix*, std::pair<int,int>>(newField, to);
	}

public:
	Board(int n) {
		m_field = new Matrix(n);
		std::pair<int, int> curPos;
		for (int y = 0; y < n; y++) {
			for (int x = 0; x < n; x++) {
				curPos.second = y;
				curPos.first = x;
				if (m_field->getElement(curPos) == 0) {
					m_hole = curPos;
					break;
				}
			}
		}
	}

	Board(Matrix* field, std::pair<int, int> hole) {
		m_field = field;
		m_hole = hole;
	}

	vector<Board*>* possibleMoves() {
		vector<Board*>* result = new vector<Board*>();
		
		// left move
		
		try {
			 std::pair<int, int> to(m_hole.first + 1, m_hole.second);
			 auto data = Move(to);
			 result->push_back(new Board(data.first, data.second));
		}
		catch (std::invalid_argument ex) {}

		// right move
		try {
			std::pair<int, int> to(m_hole.first - 1, m_hole.second);
			auto data = Move(to);
			result->push_back(new Board(data.first, data.second));
		}
		catch (std::invalid_argument ex){}

		// up move
		try {
			std::pair<int, int> to(m_hole.first, m_hole.second - 1);
			auto data = Move(to);
			result->push_back(new Board(data.first, data.second));
		}
		catch (std::invalid_argument ex) {}

		// down move
		try {
			std::pair<int, int> to(m_hole.first, m_hole.second + 1);
			auto data = Move(to);
			result->push_back(new Board(data.first, data.second));
		}
		catch (std::invalid_argument ex) {}
		
		return result;
	}

	Matrix* getField() {
		return m_field;
	}

	pair<int, int> getHole() {
		return m_hole;
	}

	void print() {
		m_field->print();
	}
	
};