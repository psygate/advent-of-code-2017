#include <vector>
#include <iostream>
#include <string>
#include <stdexcept>
#include <tuple>
#include <functional>
#include <climits>

using namespace std;

struct SumSpiral
{
	SumSpiral(const size_t size);
	SumSpiral(const SumSpiral& other);
	const size_t size;
	vector<vector<int>> matrix;
	const vector<int>& operator [](int x) const { return matrix[x]; }
	tuple<size_t, size_t> find(const int value) const;
	bool contains(int n) const;
	vector<tuple<int, int>> pathToOne(int n) const;
	tuple<size_t, size_t> minimum_neighbour(size_t x, size_t y) const;
	void set(size_t x, size_t y, int value);
	int localsum(const size_t x, const size_t y) const;

	friend ostream &operator<<(ostream &stream, SumSpiral ob);
};

SumSpiral::SumSpiral(const SumSpiral& other)
	: size(other.size), matrix(other.matrix)
{

}

int SumSpiral::localsum(const size_t x, const size_t y) const
{
	int sum = 0;
	for (int dx = -1; dx <= 1; dx++)
	{
		for (int dy = -1; dy <= 1; dy++)
		{
			if (dx == 0 && dy == 0 || (x == 0 && dx == -1) || (y == 0 && dy == -1) || (x == size - 1 && dx == 1) || (y == size - 1 && dy == 1)) continue;
			if (matrix[x + dx][y + dy] == -1) continue;
			sum += matrix[x + dx][y + dy];
		}
	}

	return sum;
}

SumSpiral::SumSpiral(const size_t size_half)
	: size(size_half * 2 + 1), matrix(size_half * 2 + 1, vector<int>(size_half * 2 + 1, -1))
{

	/*int **M;
	M = new int*[2 * N + 1];
	for (int i = 0; i<2 * N + 1; i++)
		M[i] = new int[2 * N + 1];
	*/
	int x, y, current, counter;

	matrix[size_half][size_half] = 1;
	x = size_half;
	y = size_half + 1;
	counter = 2;
	current = 2;

	for (int j = 0; j < size_half; j++, counter += 2)
	{
		for (int i = 0; i < counter; i++)
		{
			matrix[x][y] = localsum(x, y);
			x--;
			current++;
		}
		x++;
		y--;
		for (int i = 0; i < counter; i++)
		{
			matrix[x][y] = localsum(x, y);
			y--;
			current++;
		}
		y++;
		x++;
		for (int i = 0; i < counter; i++)
		{
			matrix[x][y] = localsum(x, y);
			x++;
			current++;
		}
		x--;
		y++;
		for (int i = 0; i < counter; i++)
		{
			matrix[x][y] = localsum(x, y);
			y++;
			current++;
		}
	}
};

bool SumSpiral::contains(int n) const
{
	for (size_t x = 0; x < matrix.size(); x++)
	{
		for (size_t y = 0; y < matrix[x].size(); y++)
		{
			if (matrix[x][y] == n)
			{
				return true;
			}
		}
	}

	return false;
}


ostream &operator<<(ostream &stream, SumSpiral s)
{
	stream << "Spiral:" << endl;
	for (size_t y = 0; y < s.size; y++)
	{
		for (size_t x = 0; x < s.size; x++)
		{
			stream << s[x][y] << " ";
		}
		stream << endl;
	}
	return stream;
}


tuple<size_t, size_t> SumSpiral::find(const int value) const
{
	for (size_t x = 0; x < size; x++)
	{
		for (size_t y = 0; y < size; y++)
		{
			if (matrix[x][y] == value)
			{
				return tuple<int, int>(x, y);
			}
		}
	}

	return tuple<int, int>(-1, -1);
}

tuple<size_t, size_t> SumSpiral::minimum_neighbour(size_t x, size_t y) const
{
	int value = INT_MAX;
	int minx = 0, miny = 0;
	int dx[] = { -1,0,1,0 }, dy[] = { 0,-1,0,1 };

	for (int i = 0; i < 4; i++)
	{
		if (x + dx[i] >= 0 && x + dx[i] < size && y + dy[i] >= 0 && y + dy[i] < size)
		{
			if (matrix[x + dx[i]][y + dy[i]] < value)
			{
				minx = x + dx[i];
				miny = y + dy[i];
				value = matrix[x + dx[i]][y + dy[i]];
			}
		}
	}

	return tuple<int, int>(minx, miny);
}

vector<tuple<int, int>> SumSpiral::pathToOne(int n) const
{
	vector<tuple<int, int>> out;
	if (n != 1)
	{
		int state = 0;
		size_t x, y;
		tie(x, y) = this->find(n);

		while (matrix[x][y] != 1)
		{
			tie(x, y) = minimum_neighbour(x, y);
			out.push_back(tuple<int, int>(x, y));
		}

	}

	return out;
}

void SumSpiral::set(size_t x, size_t y, int value)
{
	matrix[x][y] = value;
}


int main(int argc, char** argv) {
	if (argc != 2)
	{
		cerr << "Need atleast one argument (spiral size)." << endl;
		return -1;
	}

	int n;

	try
	{
		n = stoi(argv[1]);
	}
	catch (const exception &e)
	{
		cerr << "Argument 2 has to be a number." << endl;
		return -2;
	}

	size_t spiral_size = 301;
	SumSpiral spiral(spiral_size);

	int min = INT_MAX;
	for (size_t x = 0; x < spiral_size; x++)
	{
		for (size_t y = 0; y < spiral_size; y++)
		{
			if (spiral[x][y] < min && spiral[x][y] >= n)
			{
				min = spiral[x][y] ;
			}
		}
	}

	cout << min << endl;
}
