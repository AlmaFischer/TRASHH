	for(size_t i = 0;i < Posible_path.size();i++){
		
		std::cout <<"("<< Posible_path[i].first<<" "<<Posible_path[i].second<<")";
	}


    std::vector<std::pair<int,int>> Maze::solve_s(int f1, int c1,int f2,int c2){
	std::vector<std::pair<int,int>> Posible_path;
		if(!inRange(f1,c1)||!inRange(f2,c2)){ //Modificar para que inicio sea la primera linea
		std::cout<<"Coordenadas no estan en laberinto"<<std::endl;
		return Posible_path;
	}
	std::stack<std::pair<int,int>> stack;
	stack.push(std::make_pair(f1,c1));
	while(!stack.empty()){
		int i = stack.top().first;
		int j = stack.top().second;
		if(i==f2 && j==c2){
			while (!stack.empty()){
				Posible_path.push_back(stack.top());
				stack.pop();
			}
			return Posible_path;
		}
		grid[i][j]=-1;
		bool moved = false;

		shuffle_dir();
		int dx = 0;
		int dy = 0;
	for(int k = 0; k <  4; k++){
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
		int i_next = i + dy;
		int j_next = j + dx;

		if(inRange(i_next,j_next)&& grid[i_next][j_next]==0){
			stack.push(std::make_pair(i_next,j_next));
			moved=true;
			break;
		}

	}

	if (!moved) {
		stack.pop();
	}
	}
	return Posible_path;
}
