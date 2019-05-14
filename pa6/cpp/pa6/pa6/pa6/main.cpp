#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

template <typename T>
vector<vector<T>> encodeMultiply(vector<vector<T>>& cgm, vector<T> bits)
{
	vector<vector<T>> result(8);

	for (auto&& i : result)
	{
		i.push_back(0);
	}

	if (cgm.size() == bits.size())
	{
		result[0][0] = 0;
		for (int i = 0; i < cgm.size(); i++)
		{
			vector<T> current = cgm[i];
			for (int j = 0; j < current.size(); j++)
			{
				result[j + 1][0] += bits[i] * current[j];
				result[j + 1][0] %= 2;
			}
		}
	}
	return result;
}

template <typename T>
vector<vector<T>> decodeMultiply(vector<vector<T>>& pcm, vector<T> bits)
{
	vector<vector<T>> result(3);

	for (auto&& i : result)
	{
		i.push_back(0);
	}

	if (pcm.size() == bits.size())
	{
		for (int i = 0; i < pcm.size(); i++)
		{
			vector<T> current = pcm[i];
			for (int j = 0; j < current.size(); j++)
			{
				result[j][0] += bits[i] * current[j];
				result[j][0] %= 2;
			}
		}
	}
	return result;
}

int binaryToDecimal(int n)
{
	int num = n;
	int dec_value = 0;

	// Initializing base value to 1, i.e 2^0 
	int base = 1;

	int temp = num;
	while (temp) {
		int last_digit = temp % 10;
		temp = temp / 10;

		dec_value += last_digit * base;

		base = base * 2;
	}

	return dec_value;
}

string toBinary(int number)
{
	string result;
	string fourBitResult;
	while (number != 0)
	{
		result = (number % 2 == 0 ? "0" : "1") + result;
		number /= 2;
	}

	int size = 0;
	int filler = 0;
	if (result.size() < 4)
	{
		vector<char> char_vect{};
		size = result.size();
		filler = 4 - size;

		for (int i = 0; i < filler; i++)
		{
			//char_vect.push_back(0);
			fourBitResult.push_back('0');
		}

		for (int i = 0; i < result.size(); i++)
		{
			fourBitResult.push_back(result[i]);
		}

	}

	return fourBitResult;
}

void encodeFile(string file_name)
{
	vector<vector<int>> CGM = {
		vector<int>{1, 1, 1, 0, 0, 0, 0},
		vector<int>{1, 0, 0, 1, 1, 0, 0},
		vector<int>{0, 1, 0, 1, 0, 1, 0},
		vector<int>{1, 1, 0, 1, 0, 0, 1}
	};

	string line = " ";

	char letter = ' ';

	string output_file = file_name + ".encoded";

	ifstream inputFile{ file_name };
	ofstream outputFile{ output_file };

	if (inputFile.is_open())
	{

		while (getline(inputFile, line))
		{
			for (auto ch : line)
			{
				vector<vector<int>> low_vect;
				vector<vector<int>> high_vect;
				vector<vector<int>> low_vect_mult;
				vector<vector<int>> high_vect_mult;
				vector<int> singleItemLow{};
				vector<int> singleItemHigh{};

				letter = ch;
				short low = (0b1111) & letter;
				short high = (0b1111) & (letter >> 4);

				string low_binary = toBinary(low);
				string high_binary = toBinary(high);


				// creates vectors from binary strings
				for (auto ch : low_binary)
				{
					string letter = " ";
					letter.push_back(ch);
					singleItemLow.push_back(stoi(letter));
				}


				for (auto ch : high_binary)
				{
					string letter = " ";
					letter.push_back(ch);
					singleItemHigh.push_back(stoi(letter));
				}

				low_vect_mult = encodeMultiply(CGM, singleItemLow);
				high_vect_mult = encodeMultiply(CGM, singleItemHigh);

				for (int i = 0; i < 8; i++)
				{
					int bit = 0;
					bit = low_vect_mult[i][0];

					outputFile << bit;
				}
				outputFile << '\n';
				for (int i = 0; i < 8; i++)
				{
					int bit = 0;
					bit = high_vect_mult[i][0];

					outputFile << bit;
				}
				outputFile << '\n';
			}
		}
	}
	outputFile.close();
	inputFile.close();
}

void decodeFile(string file_name)
{
	vector<vector<int>> PCM =
	{
		vector<int>{1, 0, 1, 0, 1, 0, 1},
		vector<int>{0, 1, 1, 0, 0, 1, 1},
		vector<int>{0, 0, 0, 1, 1, 1, 1},
	};

	string line;
	string outputfile = file_name + ".decoded";
	int num = 0;
	char low = ' ';
	char high = ' ';
	vector<int> string_vect;
	vector<vector<int>> result;

	ifstream inputFile{ file_name };
	ofstream outputFile{ outputfile };

	if (inputFile.is_open())
	{
		int flag = 1;
		while (getline(inputFile, line))
		{
			for (auto ch : line)
			{
				string letter = "";
				letter.push_back(ch);
				string_vect.push_back(stoi(letter));
			}
			result = decodeMultiply(PCM, string_vect);

			for (int i = 0; i < result.size(); i++)
			{
				if (result[i][0] == 1)
				{
					cout << "We have detected an error";
					int binary = stoi(line);
					
					//Places a marker at the placement of the error
					int error_place = 0;
					error_place = binaryToDecimal(binary);

					int j = 1;
					for (auto ch : line)
					{
						if (j == error_place)
						{
							//flip the bit for error correction
							if (ch == '0')
							{
								line[j] = '1';
							}
							if (ch == '1')
							{
								line[j] == '0';
							}
						}
					}

				}
			}

			//Convert the line of binary back into characters
			if (flag % 2 == 1)
			{
				char low = ' ';
				int low_temp = 0;

				low_temp = binaryToDecimal(stoi(line));
				low = low_temp;
			}
			if (flag % 2 == 0)
			{
				char high = ' ';
				int high_temp = 0;

				high_temp = binaryToDecimal(stoi(line));
				high = high_temp;

				//From your lecture code
				char converted = '\0';
				converted = high << 4;
				converted = converted | low;

				outputFile << converted;
			}
			flag++;
		}
		outputFile.close();
		inputFile.close();
	}
	
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
	return 0;
}
