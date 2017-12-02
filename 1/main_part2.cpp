#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		cerr << "Arg 2 has to be the sum to calculate.";
	}

	string ndata(argv[1]);

	vector<char> data;

	for(size_t i = 0; i < ndata.size(); i++)
	{
		data.push_back(ndata[i]);
	}

	if (data.size() < 2)
	{
		cout << 0 << endl;
	}

	int32_t sum = 0;
	for (size_t i = 0; i < data.size(); i++)
	{
		if (data[i] == data[(i + data.size() / 2) % data.size()])
		{
			sum += (data[i] - '0');
		}
	}

	cout << sum << endl;
}
