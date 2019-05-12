
#include "PA1.h"

//PA #1 TOOD: Generates a Huffman character tree from the supplied text
HuffmanTree<char>* PA1::huffmanTreeFromText(vector<string> data)
{
	//Builds a Huffman Tree from the supplied vector of strings.
	//This function implement's Huffman's Algorithm as specified in the
	//book.

	//In order for your tree to be the same as mine, you must take care 
	//to do the following:
	//1.	When merging the two smallest subtrees, make sure to place the 
	//      smallest tree on the left side!

	// counting and storing frequencies in hashtable

	unordered_map<char, int> frequencies{};
	for (auto word : data)
	{
		for (auto ch : word)
		{
			// counts the frequencies
			frequencies[ch]++;
		}
	}

	// put into trees
	//maintains huffman tree forest 
	priority_queue < HuffmanTree<char>*, vector<HuffmanTree<char>*>, TreeComparer> forest{};

	//loop through frequency distributions
	for (auto kvp : frequencies)
	{
		//kvp first char, kvp second frequency(weight)	
		// pushes "trees" into the forest with key, value pair
		forest.push(new HuffmanTree<char>(kvp.first, kvp.second));
	}

	//merge two trees
	// while there is more than one tree in the forest
	while (forest.size() > 1)
	{
		HuffmanTree<char>*smaller = forest.top();
		forest.pop();
		HuffmanTree<char>*larger = forest.top();
		forest.pop();

		//merge two trees
		forest.push(new HuffmanTree<char>{ smaller,larger });
	}


	return forest.top(); // return tree
}

//PA #1 TODO: Generates a Huffman character tree from the supplied encoding map
//NOTE: I used a recursive helper function to solve this!
HuffmanTree<char>* PA1::huffmanTreeFromMap(unordered_map<char, string> huffmanMap)
{
	//Generates a Huffman Tree based on the supplied Huffman Map. Recall that a 
	//Huffman Map contains a series of codes(e.g. 'a' = > 001).Each digit(0, 1) 
	//in a given code corresponds to a left branch for 0 and right branch for 1.

	HuffmanInternalNode<char>* root = new HuffmanInternalNode<char>{ nullptr, nullptr };
	HuffmanInternalNode<char>* node = root;


	string path;
	char value;

	//looping through the map to create the huffman tree
	for (auto kvp : huffmanMap)
	{
		path = kvp.second;
		value = kvp.second[kvp.second.length() - 1];

		for (int i = 0; i < path.length() - 1; i++)
		{
			char ch = path[i];

			//putting the zeros on the left and the ones on the right
			if (ch == '0')
			{
				if (node->getLeftChild() == nullptr)
				{
					node->setLeftChild(new HuffmanInternalNode<char>{ nullptr,nullptr });
				}

				node = dynamic_cast<HuffmanInternalNode<char>*>(node->getLeftChild());
			}

			else
			{
				if (node->getRightChild() == nullptr)
				{
					node->setRightChild(new HuffmanInternalNode<char>{ nullptr,nullptr });
				}

				node = dynamic_cast<HuffmanInternalNode<char>*>(node->getRightChild());
			}

		}

		char last_ch = (path[path.length() - 1]);

		if (last_ch == '0')
		{
			node->setLeftChild(new HuffmanLeafNode<char>{ value,1 });
			node = root;
		}
		else
		{
			node->setRightChild(new HuffmanLeafNode<char>{ value,1 });
			node = root;
		}
	}

	HuffmanTree<char>* forest = new HuffmanTree<char>{ root };

	return forest;
}

void huffmanEncodingMapFromTreeHelper(unordered_map<char, string>&map,
	HuffmanNode<char>*node, string encoding)
{
	if (node->isLeaf() == false)
	{
		//make recursive calls
		// more dynamic casts: from generic node into an internal node
		HuffmanInternalNode<char>*root = dynamic_cast<HuffmanInternalNode<char>*>(node);
		huffmanEncodingMapFromTreeHelper(map, root->getLeftChild(), encoding + "0");
		huffmanEncodingMapFromTreeHelper(map, root->getRightChild(), encoding + "1");
	}
	else
	{
		// is leaf
		// this converts node, which is a Huffman node into a leaf node
		// syntax:                   convert      want			          what we want to convert
		HuffmanLeafNode<char>*root = dynamic_cast<HuffmanLeafNode<char>*>(node);
		map[root->getValue()] = encoding;
		return;
	}
}


//PA #1 TODO: Generates a Huffman encoding map from the supplied Huffman tree
//NOTE: I used a recursive helper function to solve this!
unordered_map<char, string> PA1::huffmanEncodingMapFromTree(HuffmanTree<char> *tree)
{
	// pre order walk of the tree!
	// will need to do dynamic_casting

	HuffmanNode<char> *node = tree->getRoot();

	if (node->isLeaf() == true)
	{
		HuffmanLeafNode<char> *leaf = dynamic_cast<HuffmanLeafNode<char> *>(node);
		leaf = (HuffmanLeafNode<char> *)node;
	}

	unordered_map<char, string> result{};
	huffmanEncodingMapFromTreeHelper(result, tree->getRoot(), "");
	return result;
}

//PA #1 TODO: Writes an encoding map to file.  Needed for decompression.
void PA1::writeEncodingMapToFile(unordered_map<char, string> huffmanMap, string file_name)
{
	//Writes the supplied encoding map to a file.  My map file has one 
	//association per line (e.g. 'a' and 001 would yield the line "a001")
	ofstream outputFile{ file_name };
	for (auto kvp : huffmanMap)
	{
		outputFile << kvp.first;
		for (auto path : kvp.second)
		{
			outputFile << path;
		}
		//putting each value on a seperate line when written to the file
		outputFile << "\n";
	}

	outputFile.close();

}

//PA #1 TODO: Reads an encoding map from a file.  Needed for decompression.
unordered_map<char, string> PA1::readEncodingMapFromFile(string file_name)
{
	//Creates a Huffman Map from the supplied file.Essentially, this is the 
	//inverse of writeEncodingMapToFile.  
	// turn back in to key,value pair
	unordered_map<char, string> result{};
	string line;
	ifstream inputFile{ file_name };
	string path;
	char key;
	while (inputFile.is_open())
	{
		getline(inputFile, line);
		for (auto ch : line)
		{
			if (ch != '0' && ch != '1')
			{
				key = ch;
			}
			else
			{
				path.push_back(ch);
			}
		}
		result.emplace(key, path);
		path.clear();

		if (line.empty())
		{
			inputFile.close();
		}
	}
	return result;
}

//PA #1 TODO: Converts a vector of bits (bool) back into readable text using the supplied Huffman map
string PA1::decodeBits(vector<bool> bits, unordered_map<char, string> huffmanMap)
{
	//Uses the supplied Huffman Map to convert the vector of bools (bits) back into text.
	//To solve this problem, I converted the Huffman Map into a Huffman Tree and used 
	//tree traversals to convert the bits back into text
	// call build tree from map
	ostringstream result{};

	//Initializing nodes for the huffaman tree to be created
	HuffmanTree<char>* root = huffmanTreeFromMap(huffmanMap);

	HuffmanInternalNode<char>* intNode = dynamic_cast<HuffmanInternalNode<char>*>(root->getRoot());

	HuffmanLeafNode<char>* leaf = dynamic_cast<HuffmanLeafNode<char>*>(root->getRoot());

	//Couldn't figure out the tree traversals

	return result.str();
}

//PA #1 TODO: Using the supplied Huffman map compression, converts the supplied text into a series of bits (boolean values)
vector<bool> PA1::toBinary(vector<string> text, unordered_map<char, string> huffmanMap)
{
	// take each char and make it equal to binary representation
	vector<bool> bits{};

	for (auto str : text)
	{
		for (auto ch : str)
		{
			for (auto kvp : huffmanMap)
			{
				if (ch == kvp.first)
				{
					for (auto path : kvp.second)
					{
						if (path == '0')
						{
							bits.push_back(0);
						}
						else
						{
							bits.push_back(1);
						}
					}

				}
			}
		}

	}

	//Return the vector of booleans
	return bits;
}