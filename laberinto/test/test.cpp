#include <iostream>
#include "maze/maze.hpp"
int main(int nargs, char** vargs){
	maze::Maze laberinto(101,101);
	laberinto.print();
	std::stack<std::pair<int, int>> a = laberinto.solve_s(0,0,20,50);
	laberinto.printPaths(a);
	std::queue<std::pair<int, int>> b = laberinto.solve_q(0,0,20,50);
	laberinto.printPathq(b);
	return 0;
}