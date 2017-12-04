#include <vector>
#include <iostream>
#include <string>
#include <stdexcept>
#include <tuple>
#include <functional>
#include <climits>

using namespace std;

struct Spiral
{
	Spiral(const size_t size);
	Spiral(const Spiral& other);
	const size_t size;
	vector<vector<int>> matrix;
	const vector<int>& operator [](int x) const { return matrix[x]; }
	tuple<size_t, size_t> find(const int value) const;
	bool contains(int n) const;
	vector<tuple<int, int>> pathToOne(int n) const;
	tuple<size_t, size_t> minimum_neighbour(size_t x, size_t y) const;

	friend ostream &operator<<(ostream &stream, Spiral ob);
};

Spiral::Spiral(const Spiral& other)
	: size(other.size), matrix(other.matrix)
{

}

Spiral::Spiral(const size_t size_half)
	: size(size_half * 2 + 1), matrix(size_half * 2 + 1, vector<int>(size_half * 2 + 1))
{

	/*int **M;
	M = new int*[2 * N + 1];
	for (int i = 0; i<2 * N + 1; i++)
		M[i] = new int[2 * N + 1];
	*/
	int r, c, current, counter;

	matrix[size_half][size_half] = 1;
	r = size_half;
	c = size_half + 1;
	counter = 2;
	current = 2;

	for (int j = 0; j < size_half; j++, counter += 2)
	{
		for (int i = 0; i < counter; i++)
			matrix[r--][c] = current++;
		r++;
		c--;
		for (int i = 0; i < counter; i++)
			matrix[r][c--] = current++;
		c++;
		r++;
		for (int i = 0; i < counter; i++)
			matrix[r++][c] = current++;
		r--;
		c++;
		for (int i = 0; i < counter; i++)
			matrix[r][c++] = current++;
	}
};

bool Spiral::contains(int n) const
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


ostream &operator<<(ostream &stream, Spiral s)
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


tuple<size_t, size_t> Spiral::find(const int value) const
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

tuple<size_t, size_t> Spiral::minimum_neighbour(size_t x, size_t y) const
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

vector<tuple<int, int>> Spiral::pathToOne(int n) const
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
			cout << "Minimum: " << x << ", " << y << " - " << matrix[x][y] << endl;
		}

	}

	return out;
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
	while (true)
	{
		Spiral spiral(spiral_size);
		if (spiral.contains(n))
		{
			cout << spiral_size << endl;
			vector<tuple<int, int>> path{ spiral.pathToOne(n) };
			cout << path.size() << endl;
			break;
		}

		spiral_size++;
	}
}
