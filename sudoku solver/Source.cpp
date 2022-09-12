#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>


using namespace std;
using ull = unsigned long long;
using ll = long long;
int INF = 2000000000;

int M = 1000000007;
int N = 9;

int startrow, startcol;


int count(int row, int col, vector<vector<int>>& grid, vector<int>& choice, int n)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (grid[row + i][col + j] == -1)
				choice[n] += 1;
		}
	}
	return 0;
}

int check(int row, int col, vector<vector<int>>& grid, int n)
{
	//check row
	for (int i = 0; i < N; ++i)
	{
		if (grid[i][col] == n)
			return 0;
	}

	//check column 
	for (int i = 0; i < N; ++i)
	{
		if (grid[row][i] == n)
			return 0;
	}

	//check box 
	int rowinit = row - row % 3;
	int colinit = col - col % 3;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (grid[rowinit + i][colinit + j] == n)
				return 0;
		}
	}

	return 1;
}

int solve(int row, int col, vector<vector<int>>& grid)
{
	
	if (col == N)
	{
		row += 1;
		row = row % N;
		col = 0;
	}

	if (row == startrow && col == startcol) return 1;



	if (grid[row][col] > 0)
	{
		return solve(row, col + 1, grid);
	}

	for (int i = 1; i <= N; ++i)
	{
		if (check(row, col, grid, i))
		{
			grid[row][col] = i;
			int temp = solve(row, col + 1, grid);
			if (temp == 1) return 1;
		}
		grid[row][col] = -1;
	}
	return 0;
}

int sudoku(int row, int col, vector<vector<int>>& grid)
{

	if (grid[row][col] > 0)
	{
		return solve(row, col + 1, grid);
	}

	for (int i = 1; i <= N; ++i)
	{
		if (check(row, col, grid, i))
		{
			grid[row][col] = i;
			int temp = solve(row, col + 1, grid);
			if (temp == 1) return 1;
		}
		grid[row][col] = -1;
	}
	return 0;
}

int main() {
	cin.sync_with_stdio(0);
	cin.tie(0);

	
	vector<vector<int>> grid(N, vector<int>(N));

	string s;
	for (int i = 0; i < N; ++i)
	{
		cin >> s;
		for (int j = 0; j < N; ++j)
		{
			if (s[j] == '.')
			{
				grid[i][j] = -1;
			}
			else grid[i][j] = int(s[j]) - int('0');
		}
	}

	vector<int> choice(N, 0);
	count(0, 0, grid, choice, 0);
	count(0, 3, grid, choice, 1);
	count(0, 6, grid, choice, 2);

	count(3, 0, grid, choice, 3);
	count(3, 3, grid, choice, 4);
	count(3, 6, grid, choice, 5);

	count(6, 0, grid, choice, 6);
	count(6, 3, grid, choice, 7);
	count(6, 6, grid, choice, 8);


	int m = 10;
	int index = -1;

	for (int i = 0; i < 9; ++i)
	{
		if (choice[i] < m)
		{
			m = choice[i];
			index = i;
		}
	}

	vector<pair<int, int>> vec = { {0,0}, {0,3}, {0, 6}, {3,0}, {3, 3}, {3, 6}, {6,0}, {6,3}, {6,6} };


	startrow = vec[index].first;
	startcol = vec[index].second;

	sudoku(startrow, startcol, grid);

	for (int i = 0; i < N; ++i)
	{
		string s;
		for (int j = 0; j < N; ++j)
		{
			cout << grid[i][j];
		}
		cout << '\n';
	}
}