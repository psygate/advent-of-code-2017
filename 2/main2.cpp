#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <climits>
#include <functional>
#include <tuple>

using namespace std;



template<typename T>
tuple<int, int> select_divisible(const vector<T>& input)
{
	for(size_t i = 0; i < input.size(); i++)
	{
		for(size_t j = 0; j < input.size(); j++) 
		{
			if(i == j) continue;
			else if(input[i] % input[j] == 0)
			{
				return tuple<int, int>(input[i], input[j]);
			}
		}
	}
}

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
	
	//Reduce the list by selecting only divisible numbers.
	
	for(size_t row_index = 0; row_index < data.size(); row_index++)
	{
		vector<int> divisible;
		int a,b;
		tie(a,b) = select_divisible(data[row_index]);
		data[row_index].clear();
		data[row_index].push_back(a);
		data[row_index].push_back(b);
	}
	
	vector<int> sumvec(data.size());
	for(size_t row_index = 0; row_index < data.size(); row_index++)
	{
		int a = data[row_index][0], b = data[row_index][1];
		int max, min;
		if(a > b) {max = a; min = b;} else {max = b; min = a;}
		sumvec.push_back(max / min);
	}

	int sum = 0;
	for(auto& val : sumvec) sum+= val;
	cout << sum << endl;
}
