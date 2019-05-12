#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "StringSplitter.h"
using namespace std;

template <typename T>
vector<vector<T>> multiply(vector<vector<T>>& a, vector<vector<T>>& b)
{
	//ensure proper matrix dimensions
	vector<vector<T>> product{};
	if (a.size() == 0 || a[0].size() != b.size())
	{
		return product;
	}

	//resize result matrix
	product.resize(a.size());
	for (auto& row : product)
	{
		row.resize(b[0].size());
	}

	for (int i = 0; i < a[0].size(); i++)
	{
		for (int j = 0; j < b.size(); j++)
		{
			for (int k = 0; k < b.size(); k++)
			{
				product[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	return product;
}

void encodeFile(string file_name)
{
	vector<vector<int>> cgm =
	{
	  vector<int>{1, 1, 0, 1},
	  vector<int>{1, 0, 1, 1},
	  vector<int>{1, 0, 0, 0},
	  vector<int>{0, 1, 1, 1},
	  vector<int>{0, 1, 0, 0},
	  vector<int>{0, 0, 1, 0},
	  vector<int>{0, 0, 0, 1},
	};

	ifstream encode_file;
	string line = " ";
	char sample = ' ';
	vector<vector<int>> low_matrix;
	vector<vector<int>> high_matrix;
	encode_file.open( file_name );

	if (encode_file.is_open())
	{
		while (getline(encode_file, line))
		{
			for (auto ch : line)
			{
				sample = ch;
				short low,b = (0b1111) & sample;
				short high,b = (0b1111) & (sample >> 4);
				cout << "Hello";

			}
		}
		encode_file.close();
	}



}

void decodeFile(string file_name)
{
	vector<vector<bool>> pcm =
	{
	  vector<bool>{1, 0, 1, 0, 1, 0, 1},
	  vector<bool>{0, 1, 1, 0, 0, 1, 1},
	  vector<bool>{0, 0, 0, 1, 1, 1, 1},
	};



}

int main()
{
	// Outputs messages to either encode or decode
	string code_option = "";
	cout << "<encode / decode>?: ";
	cin >> code_option;

	//Output to retreive a file
	string file_name = "";
	cout << "Enter a file name: ";
	cin >> file_name;


   if (code_option == "encode")
   {
      //encode ABC.txt to ABC.txt.coded
      encodeFile(file_name);
      cout << "File encoded." << endl;
   }
   else if (code_option == "decode")
   {
      //decode ABC.txt.coded to ABC.decoded.txt
      decodeFile(file_name);
      cout << "File decoded." << endl;
   }
   else
   {
      cout << "Unexpected command." << endl;
   }

}