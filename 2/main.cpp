#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <climits>
#include <functional>


using namespace std;

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		cout << "Missing arguments." << endl;
		return -1;
	}

	vector<vector<int>> data;
	string line;
	string input_string(argv[1]);

	istringstream iss(input_string);
	
	while(getline(iss, line))
	{
		istringstream linestream(line);
		vector<int> linevec;

		while(linestream)
		{
			string num;
			linestream >> num;
			
			if(!num.empty())
			{
				linevec.push_back(stoi(num));
			}
		}

		data.push_back(linevec);
	}

	vector<int> sumvec(data.size());
	for(size_t row_index = 0; row_index < data.size(); row_index++)
	{
		int min = INT_MAX;
		int max = INT_MIN;

		for(size_t col_index = 0; col_index < data[row_index].size(); col_index++)
		{
			int value = data[row_index][col_index];

			if(value > max)
			{
				max = value;
			}

			if(value < min)
			{
				min = value;
			}
		}

		sumvec.push_back(max - min);
	}

	int sum = 0;
	for(auto& val : sumvec) sum+= val;
	cout << sum << endl;
}
