/**
 * Classe Maze
 */
#include <stack>
#include <queue>
namespace maze {
	typedef unsigned char uchar;


	class Maze{
	private:
		uchar**  grid;
		int width;
		int height;
		int dir[4];
		void shuffle_dir();
		void delete_maze();
		void visit(int i, int j);
	public:
		static const unsigned char WALL;
		static const unsigned char EMPTY;
		static const unsigned char VISITED;
		static const int NORTH;
		static const int SOUTH;
		static const int EAST;
		static const int WEST;
		Maze(int h, int  w);
		void generate_maze(int h, int w);
		void reset_maze(int h, int w);
		bool inRange(int i, int j);
		void print();
		std::stack<std::pair<int, int>> solve_s(int f1,int c1,int f2,int c2); //Solver con pila
		void printPaths(const std::stack<std::pair<int, int>>& path);
		std::queue<std::pair<int, int>> solve_q(int f1, int c1, int f2, int c2);
		void printPathq(const std::queue<std::pair<int, int>>& pathQueue);


	};
}
