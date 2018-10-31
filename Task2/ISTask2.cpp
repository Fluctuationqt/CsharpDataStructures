// ISTask2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Board.hpp"

int main()
{
	/*
	Matrix m(3,true);
	m.print();
	m.moveElement(std::pair<int, int>(0, 0), std::pair<int, int>(2, 2));
	m.print();
	try {
		m.getElement(std::pair<int, int>(-1, 0));
	}
	catch (std::exception ex) {
		std::cout << ex.what()<<std::endl;
	}*/
	Board* b = new Board(3);
	auto moves = b->possibleMoves();
	for (int i = 0; i < 4; i++) {
		std::cout << std::endl;
		moves->at(i)->print();
	}
    return 0;
}

