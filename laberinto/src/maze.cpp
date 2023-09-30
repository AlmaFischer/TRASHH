#include "maze/maze.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

#include <vector>
#include <stack>
#include <queue>

namespace maze{

const unsigned char Maze::WALL  = 'X';
const unsigned char Maze::EMPTY = '-';
const unsigned char Maze::VISITED = 'O';
const int Maze::NORTH= 0;
const int Maze::SOUTH= 1;
const int Maze::EAST= 2;
const int Maze::WEST= 3;
Maze::Maze(int h, int w):
		height(h),
		width(w),
		grid(nullptr){
	dir[0] = NORTH; //1
	dir[1] = SOUTH; //2
	dir[2] = EAST;  //3
	dir[3] = WEST;  //4
	std::srand(time(0));
	generate_maze(h, w);

}

void Maze::reset_maze(int h, int w){
	delete_maze();
	height = h;
	width= w;
	grid = new uchar*[height];
	for (int i = 0; i < height; i++){
		grid[i] = new uchar[width];
		for (int j = 0; j < width; j++){
			grid[i][j] = 1;
		}
	}
}

void Maze::generate_maze(int h, int w){
	reset_maze(h, w);
	visit(0,0);
}

void Maze::delete_maze(){
	if (grid != nullptr){
		for (int i = 0; i < height; i++){
			delete[] grid[i];
		}
		delete[] grid;
	}
}

void Maze::shuffle_dir(){
	for (int i = 0; i < 4; i++){
		int r = std::rand() & 3;
		int aux = dir[r];
		dir[r] = dir[i];
		dir[i] = aux;
	 }
}
bool Maze::inRange(int i, int j){
	return ((i >= 0) && (i< height) && (j >= 0) && (j< width));
}

void Maze::visit(int i, int j){

	int dx  = 0;
	int dy = 0;
	int i_next = 0;
	int j_next = 0;
	grid[i][j] = 0;
	shuffle_dir();
	//std::cout << dir[0] << " " << dir[1] << " " << dir[2] << " "<< dir[3] << std::endl;
	for(int k = 0; k <  4; k++){
		//std::cout << dir[k] << std::endl;
		if (dir[k] == NORTH){
			dy = -1;
			dx = 0;
		}
		else if (dir[k] == SOUTH){
			dy = 1;
			dx = 0;
		}
		else if (dir[k] == EAST){
			dy = 0;
			dx = 1;
		}
		else if (dir[k] == WEST){
			dy = 0;
			dx = -1;
		}
		i_next = i + (dy<<1);
		j_next = j + (dx<<1);
		if (inRange(i_next, j_next) && grid[i_next][j_next] == 1){
			grid[i_next - dy][j_next - dx] = 0;
			visit(i_next, j_next);

		}
	}
}

void Maze::print(){
	char LIMIT = '=';
	std::cout << " Maze ( "<< height << " x " << width << " ) " << std::endl;
	std::cout << " ";
	for (int j = 0; j < width; j++){
		std::cout << LIMIT;
	}
	std::cout << " ";
	std::cout << std::endl;
	for (int i = 0; i < height; i++){
		std::cout << "|";
		for (int j = 0; j < width; j++){
			if (grid[i][j] == 0) {
				std::cout << EMPTY;
			}else if(grid[i][j]==-1){//modificado
				std::cout << VISITED;
			}else if(grid[i][j]==1){
				std::cout << WALL;
			}
		}
		std::cout << "|";
		std::cout << std::endl;
	}
	std::cout << " ";
	for (int j = 0; j < width; j++){
		std::cout << LIMIT;
	}
	std::cout << " ";
	std::cout << std::endl;
}
std::vector<std::pair<int, int>> Maze::solve_s(int f1, int c1, int f2, int c2) {
    std::vector<std::pair<int, int>> Possible_path;
    if (!inRange(f1, c1) || !inRange(f2, c2)) {
        std::cout << "Coordenadas no estan en laberinto" << std::endl;
        return Possible_path;
    }

    std::stack<std::pair<int, int>> stack;
    stack.push(std::make_pair(f1, c1));

    while (!stack.empty()) {
        int i = stack.top().first;
        int j = stack.top().second;

        if (i == f2 && j == c2) {
            // Found the destination, reconstruct the path
            while (!stack.empty()) {
                Possible_path.push_back(stack.top());
                stack.pop();
            }
            //std::reverse(Possible_path.begin(), Possible_path.end()); // Reverse to get the correct order
            return Possible_path;
        }

        bool moved = false;
        shuffle_dir();

        for (int k = 0; k < 4; k++) {
            int dx = 0;
            int dy = 0;

            if (dir[k] == NORTH) {
                dy = -1;
                dx = 0;
            } else if (dir[k] == SOUTH) {
                dy = 1;
                dx = 0;
            } else if (dir[k] == EAST) {
                dy = 0;
                dx = 1;
            } else if (dir[k] == WEST) {
                dy = 0;
                dx = -1;
            }

            int i_next = i + dy;
            int j_next = j + dx;

            if (inRange(i_next, j_next) && grid[i_next][j_next] == 0) {
				std::cout<<"IN"<<dir[k]<<std::endl;
                stack.push(std::make_pair(i_next, j_next));
                moved = true;
                grid[i_next][j_next] = Maze::VISITED; // Mark the cell as visited
				std::cout<<stack.top().first<<","<<stack.top().second<<std::endl;
                break;
            }else{std::cout<<"OUT"<<dir[k]<<std::endl;}
        }
		std::cout<<std::endl;

        if (!moved) {
            // If no valid move is possible, backtrack
            stack.pop();
        }
    }

    // If no path is found, Possible_path will be empty
    return Possible_path;
}


}
