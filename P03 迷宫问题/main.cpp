#include"Maze.h"


int main()
{
	MazeProblem solution;

	int mazeType;
	cout << "请选择迷宫生成类型(1为生成随机迷宫，2为使用固定迷宫)：";
	cin >> mazeType;

	if (mazeType == 1)
	{
		solution.getRandomMaze();
		solution.FindPath();

	}
	else if (mazeType == 2)
	{
		solution.getStaticMaze();
		solution.FindPath();
	}
	else
		cout << "输入类型错误，程序退出..." << endl;

	return 0;
}
