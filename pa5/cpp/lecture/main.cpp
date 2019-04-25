#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

unordered_map<string, int> generateDictionary(string file_name)
{
	unordered_map<string, int> Dictionary;

	string line;
	ifstream myfile(file_name);

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			Dictionary.emplace(line, 1);
		}
		myfile.close();
	}
	return Dictionary;
}

vector<string> parseGivenText(string fix_file)
{
	vector<string> fixing_file;

	string line;
	ifstream myfile(fix_file);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			string word = "";
			int counter = 1;
			line.push_back(' ');

			for (auto x : line)
			{
				//if the current space is a ' ' then push the last word onto the vector
				counter = counter + 1;
				if (x == ' ')
				{
					//push word onto string vector
					fixing_file.push_back(word);
					word = "";

					//If there was puncuation then push it onto the vector
					if (line[counter - 3] == ',')
					{
						fixing_file.push_back(",");
					}
					if (line[counter - 3] == '.')
					{
						fixing_file.push_back(".");
					}
					if (line[counter - 3] == '!')
					{
						fixing_file.push_back("!");
					}
					if (line[counter - 3] == '?')
					{
						fixing_file.push_back("?");
					}
				}
				else
				{
					//Push the next character onto the word string
					if (x != ',' && x != '.' && x != '!' && x != '?')
					{
						word = word + x;
					}
				}
			}
			fixing_file.push_back("\n");
		}
		myfile.close();
		fixing_file.pop_back();
	}
	return fixing_file;
}

int calculateEditDistance(const string& first, const string& second)
{
   vector<vector<int>> matrix{};

   //build result matrix
   matrix.resize(first.length() + 1);
   for (auto& row : matrix)
   {
      row.resize(second.length() + 1);
   }

   //fill in first row  
   for (int i = 0; i < matrix[0].size(); i++)
   {
      matrix[0][i] = i;
   }

   //fill in first column
   for (int i = 0; i < matrix.size(); i++)
   {
      matrix[i][0] = i;
   }

   //compute rest of matrix
   for (int i = 1; i < matrix.size(); i++)
   {
      for (int j = 1; j < matrix[i].size(); j++)
      {
         //find least cost of our 3 choices
         int top_cost = matrix[i - 1][j] + 1;
         int left_cost = matrix[i][j - 1] + 1;
         int diagonal_cost = matrix[i - 1][j - 1];

         //add 1 if characters are not the same
         if (first[i - 1] != second[j - 1])
         {
            diagonal_cost++;
         }

         int best_choice = min(top_cost, min(left_cost, diagonal_cost));

         //store result in current cell
         matrix[i][j] = best_choice;
      }
   }

   return matrix[matrix.size() - 1][matrix[0].size() - 1];
}

vector<string> calculateBestOption(unordered_map<string, int> dictionary, string inputted)
{
	vector<string> best_options;
	unordered_map<int, vector<string>> edit_distances{};
	int best_int;
	string file_name;
	string file_line;
		
	file_name = inputted + ".dat";
	ifstream myfile(file_name.c_str());
	
	if (myfile.is_open())
	{
		while (getline(myfile, file_line))
		{
			best_options.push_back(file_line);
		}
		myfile.close();
		return best_options;
	}
	else
	{
		best_options.push_back("None of the words below are correct.");
		for (auto word : dictionary)
		{
			best_int = calculateEditDistance(word.first, inputted);
			edit_distances[best_int].push_back(word.first);
		}

		int counter = 1;
		for (int i = 1; i < 100; i++)
		{
			for (int j = 1; j <= edit_distances[i].size(); j++)
			{
				if (best_options.size() < 10)
				{
					counter++;
					string result = (edit_distances[i][j - 1]);
					best_options.push_back(result);
				}
			}
		}
		return best_options;
	}
}


int main(void)
{

	//Ask for a file to be read and a file to save the new text to.
	string first_file;
	string dest_file;

	cout << "Input a file you want corrected: ";
	cin >> first_file;
	cout << "Input destination file: ";
	cin >> dest_file;

	//Set dictionary
	unordered_map<string, int> dictionary;
    dictionary = generateDictionary("words.txt");

	//Get parsed inputted strings
	vector<string> bad_text;
	bad_text = parseGivenText(first_file);

	//This vector holds the corrected string
	vector<string> corrected;

	//Compare inputted strings to the dictionary

	// best_list is going to look like this, each line its own index in the vector
	// ex. 1. none of these
	//	   2. This
	//     3. That

	for (int i = 0; i < bad_text.size(); i++)
	{
		vector<string> best_list{};

		if (dictionary.find(bad_text[i]) == dictionary.end())
		{
			//if word isnt in dictionary
			if (bad_text[i] == "," || bad_text[i] == "." || bad_text[i] == "!" || bad_text[i] == "?" || bad_text[i] == "\n")
			{
				corrected.push_back(bad_text[i]);
			}
			else
			{
				best_list = calculateBestOption(dictionary, bad_text[i]);

				cout << "Unknown word: " << bad_text[i] << endl;
				cout << "Corrected word: " << endl;

				int number_list = 0;
				for (auto x : best_list)
				{
					number_list++;
					cout << number_list << ". "<< x << endl;
				}


				int choice;
				cout << "Enter correct word by corresponding number: ";
				cin >> choice;
				cout << endl;

				if (choice == 1)
				{
					string correct;
					cout << "Enter correct word: ";
					cin >> correct;
					cout << endl;
					corrected.push_back(correct);
					
					ofstream myfile;
					myfile.open(bad_text[i] + ".dat");

					for (int i = 0; i <= best_list.size() - 1; i++)
					{
						if (i == 1)
						{
							myfile << correct << endl;
							if (correct != best_list[i])
							{
								myfile << best_list[i] << endl;
							}
						}
						else
						{
							if (correct != best_list[i])
							{
								myfile << best_list[i] << endl;
							}
						}
					}

					myfile.close();

				}
				else
				{
					corrected.push_back(best_list[choice - 1]);

					ofstream myfile;
					myfile.open(bad_text[i] + ".dat");

					for (int i = 0; i <= best_list.size() - 1; i++)
					{
						if (i == 1)
						{
							myfile << best_list[choice-1] << endl;
							if (best_list[i] != best_list[choice - 1])
							{
								myfile << best_list[i] << endl;
							}
						}
						else
						{
							if (best_list[i] != best_list[choice - 1])
							{
								myfile << best_list[i] << endl;
							}
						}
					}

					myfile.close();
				}

			}
		}
		else
		{
			//Add correct word into corrected vector
			corrected.push_back(bad_text[i]);
		}
	}
	
	//Read out to outputted file
	ofstream myfile;
	myfile.open(dest_file);

	for (int i = 0; i <= corrected.size()-1; i++)
	{
		if (corrected[i] == "," || corrected[i] == "." || corrected[i] == "!" || corrected[i] == "?")
		{
			myfile << corrected[i];
		}
		else
		{
			myfile << " " << corrected[i];
		}
	}

	myfile.close();
    return 0;
} 