#include "maze/maze.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

#include <vector>
#include <stack>
#include <queue>

namespace maze{

const unsigned char Maze::WALL  = '@';
const unsigned char Maze::EMPTY = '-';
const unsigned char Maze::VISITED = '*';
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
			}else{//modificado
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
std::stack<std::pair<int, int>> Maze::solve_s(int f1, int c1, int f2, int c2) {
    std::stack<std::pair<int, int>> stack;
    std::vector<std::vector<uchar>> gridCopy(height, std::vector<uchar>(width, 0)); //Copiamos Grid
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            gridCopy[i][j] = grid[i][j];
        }
    }

    if (!inRange(f1, c1) || !inRange(f2, c2)) {
        std::cout << "Coordenadas no estan en el laberinto" << std::endl;
        return stack;
    }

    stack.push(std::make_pair(f1, c1));
    gridCopy[f1][c1] = 2;

    while (!stack.empty()) {
        int i = stack.top().first;
        int j = stack.top().second;

        if (i == f2 && j == c2) {
            return stack; // Return the stack containing the path
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

            if (inRange(i_next, j_next) && gridCopy[i_next][j_next] == 0) {
                stack.push(std::make_pair(i_next, j_next));
                gridCopy[i_next][j_next] = 1;
                moved = true;
                break;
            }
        }

        if (!moved) {
            gridCopy[i][j] = 1;
            stack.pop();
        }

        if (stack.empty()) {
            std::cout << "No Solution Found" << std::endl;
            return stack;
        }
    }


    return stack;
}

void Maze::printPaths(const std::stack<std::pair<int, int>>& pathStack) {
	std::stack<std::pair<int, int>> pathStackCopy = pathStack;
	std::cout << "Camino Stack:" << std::endl;
    while (!pathStackCopy.empty()) {
        std::pair<int, int> element = pathStackCopy.top();
        pathStackCopy.pop();
        std::cout << "(" << element.first << ", " << element.second << ") ";
    }
    std::cout << std::endl;
    char LIMIT = '=';
    std::cout << " Maze ( " << height << " x " << width << " ) " << std::endl;
    std::cout << " ";
    for (int j = 0; j < width; j++) {
        std::cout << LIMIT;
    }
    std::cout << " ";
    std::cout << std::endl;

    std::stack<std::pair<int, int>> reversedPathStack = pathStack;
    std::vector<std::pair<int, int>> path;

    while (!reversedPathStack.empty()) {
        path.push_back(reversedPathStack.top());
        reversedPathStack.pop();
    }

    for (int i = 0; i < height; i++) {
        std::cout << "|";
        for (int j = 0; j < width; j++) {
            if (grid[i][j] == 0) {
                bool isOnPath = false;
                for (const auto& point : path) {
                    if (point.first == i && point.second == j) {
                        isOnPath = true;
                        break;
                    }
                }
                if (isOnPath) {
                    std::cout << "\x1b[31m"<<VISITED<<"\x1b[0m";
                } else {
                    std::cout << EMPTY;
                }
            } else if (grid[i][j] == 1) {
                std::cout << WALL;
            } else {
                std::cout << "\x1b[31m"<<VISITED<<"\x1b[0m";
            }
        }
        std::cout << "|";
        std::cout << std::endl;
    }

    std::cout << " ";
    for (int j = 0; j < width; j++) {
        std::cout << LIMIT;
    }
    std::cout << " ";
    std::cout << std::endl;
}



std::queue<std::pair<int, int>> Maze::solve_q(int f1, int c1, int f2, int c2) {
    std::queue<std::pair<int, int>> queue;
    std::vector<std::vector<uchar>> gridCopy(height, std::vector<uchar>(width, 0));
    std::vector<std::vector<std::pair<int, int>>> parent(height, std::vector<std::pair<int, int>>(width, {-1, -1}));

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            gridCopy[i][j] = grid[i][j];
        }
    }

    if (!inRange(f1, c1) || !inRange(f2, c2)) {
        std::cout << "Coordenadas no estan en el laberinto" << std::endl;
        return queue;
    }

    queue.push(std::make_pair(f1, c1));
    gridCopy[f1][c1] = 1;

    while (!queue.empty()) {
        int i = queue.front().first;
        int j = queue.front().second;
        queue.pop();

        if (i == f2 && j == c2) {
            std::queue<std::pair<int, int>> path;
            while (i != f1 || j != c1) {
                path.push(std::make_pair(i, j));
                auto parent_coords = parent[i][j];
                i = parent_coords.first;
                j = parent_coords.second;
            }
            path.push(std::make_pair(f1, c1));
            return path;
        }

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

            if (inRange(i_next, j_next) && gridCopy[i_next][j_next] == 0) {
                queue.push(std::make_pair(i_next, j_next));
                gridCopy[i_next][j_next] = 1;
                parent[i_next][j_next] = {i, j};
            }
        }
    }

    std::cout << "No Solution Found" << std::endl;
    return queue;
}


void Maze::printPathq(const std::queue<std::pair<int, int>>& pathQueue) {
	std::queue<std::pair<int, int>> pathQueueCopy1 = pathQueue;
	std::cout << "Camino queue:" << std::endl;
    while (!pathQueueCopy1.empty()) {
        std::pair<int, int> element = pathQueueCopy1.front();
        pathQueueCopy1.pop();
        std::cout << "(" << element.first << ", " << element.second << ") ";
    }
    std::cout << std::endl;




    char LIMIT = '=';
    std::cout << " Maze ( " << height << " x " << width << " ) " << std::endl;
    std::cout << " ";
    for (int j = 0; j < width; j++) {
        std::cout << LIMIT;
    }
    std::cout << " ";
    std::cout << std::endl;

    std::queue<std::pair<int, int>> pathQueueCopy = pathQueue;
    std::vector<std::pair<int, int>> path;

    while (!pathQueueCopy.empty()) {
        path.push_back(pathQueueCopy.front());
        pathQueueCopy.pop();
    }

    for (int i = 0; i < height; i++) {
        std::cout << "|";
        for (int j = 0; j < width; j++) {
            if (grid[i][j] == 0) {
                bool isOnPath = false;
                for (const auto& point : path) {
                    if (point.first == i && point.second == j) {
                        isOnPath = true;
                        break;
                    }
                }
                if (isOnPath) {
                    std::cout << "\x1b[31m"<<VISITED<<"\x1b[0m";
                } else {
                    std::cout << EMPTY;
                }
            } else if (grid[i][j] == 1) {
                std::cout << WALL;
            } else {
                std::cout <<"\x1b[31m"<<VISITED<<"\x1b[0m";
            }
        }
        std::cout << "|";
        std::cout << std::endl;
    }

    std::cout << " ";
    for (int j = 0; j < width; j++) {
        std::cout << LIMIT;
    }
    std::cout << " ";
    std::cout << std::endl;
}




}
