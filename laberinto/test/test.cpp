#include <iostream>
#include "maze/maze.hpp"
int main(int nargs, char** vargs){
	maze::Maze laberinto(10,10);
	laberinto.print();
	laberinto.solve_s(0,0,9,9);
	laberinto.print();

	return 0;
}