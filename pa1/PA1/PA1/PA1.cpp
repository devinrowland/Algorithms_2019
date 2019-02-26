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
	//store frequencies in hashtable

	unordered_map<char, int> frequencies{};
	for (auto word : data)
	{
		for (auto ch : word)
		{
			frequencies[ch]++;
		}
	}

	//maintains huffman tree forest 
    priority_queue < HuffmanTree<char>*, vector<HuffmanTree<char>*>, TreeComparer> forest{};

	for (auto kvp : frequencies)
	{
		forest.push(new HuffmanTree<char>(kvp.first, kvp.second));
	}

	// This is how you merge two trees, connects them both using a linker node... see example for details
	HuffmanTree<char>* smaller = forest.top();
	forest.pop();
	HuffmanTree<char>* larger = forest.top();
	forest.pop();
	forest.push(new HuffmanTree<char>{ smaller, larger });

    //TODO: shouldn't return nullptr
    return forest.top();
}

//PA #1 TODO: Generates a Huffman character tree from the supplied encoding map
//NOTE: I used a recursive helper function to solve this!
HuffmanTree<char>* PA1::huffmanTreeFromMap(unordered_map<char, string> huffmanMap)
{

    //Generates a Huffman Tree based on the supplied Huffman Map.Recall that a 
    //Huffman Map contains a series of codes(e.g. 'a' = > 001).Each digit(0, 1) 
    //in a given code corresponds to a left branch for 0 and right branch for 1.
    return nullptr;
}

void huffmanEncodingMapFromTreeHelper(unordered_map<char, string>& map,
	HuffmanNode<char>* node,
	string encoding)
{
	if (node->isLeaf() == false)
	{
		//not a leaf, make recursive calls
		HuffmanInternalNode<char>* root =
			dynamic_cast<HuffmanInternalNode<char>*>(node);
		huffmanEncodingMapFromTreeHelper(map, root->getLeftChild(), encoding + "0");
		huffmanEncodingMapFromTreeHelper(map, root->getRightChild(), encoding + "1");
	}
	else
	{
		//this is a leaf. This means that we have a complete mapping for this character
		//this converts node, which is a huffman node into a leafnode
		HuffmanLeafNode<char>* root = dynamic_cast<HuffmanLeafNode<char>*>(node);
		map[root->getValue()] = encoding;
		return;
	}
}

//PA #1 TODO: Generates a Huffman encoding map from the supplied Huffman tree
//NOTE: I used a recursive helper function to solve this!
unordered_map<char, string> PA1::huffmanEncodingMapFromTree(HuffmanTree<char> *tree)
{
	HuffmanNode<char> *node = tree->getRoot();
	if (node->isLeaf() == true)
	{
		HuffmanLeafNode<char> *leaf = dynamic_cast<HuffmanLeafNode<char> *>(node);
		leaf = (HuffmanLeafNode<char> *)node;
	}

    //Generates a Huffman Map based on the supplied Huffman Tree.  Again, recall 
    //that a Huffman Map contains a series of codes(e.g. 'a' = > 001).Each digit(0, 1) 
    //in a given code corresponds to a left branch for 0 and right branch for 1.  
    //As such, a given code represents a pre-order traversal of that bit of the 
    //tree.  I used recursion to solve this problem.
    unordered_map<char, string> result{};
	huffmanEncodingMapFromTreeHelper(result, tree->getRoot(), "");
    return result;
}

//PA #1 TODO: Writes an encoding map to file.  Needed for decompression.
void PA1::writeEncodingMapToFile(unordered_map<char, string> huffmanMap, string file_name)
{
    //Writes the supplied encoding map to a file.  My map file has one 
    //association per line (e.g. 'a' and 001 would yield the line "a001")
}

//PA #1 TODO: Reads an encoding map from a file.  Needed for decompression.
unordered_map<char, string> PA1::readEncodingMapFromFile(string file_name)
{
    //Creates a Huffman Map from the supplied file.Essentially, this is the 
    //inverse of writeEncodingMapToFile.  
    unordered_map<char, string> result{};
    return result;
}

//PA #1 TODO: Converts a vector of bits (bool) back into readable text using the supplied Huffman map
string PA1::decodeBits(vector<bool> bits, unordered_map<char, string> huffmanMap)
{
    //Uses the supplied Huffman Map to convert the vector of bools (bits) back into text.
    //To solve this problem, I converted the Huffman Map into a Huffman Tree and used 
    //tree traversals to convert the bits back into text.
    ostringstream result{};
    return result.str();
}

//PA #1 TODO: Using the supplied Huffman map compression, converts the supplied text into a series of bits (boolean values)
vector<bool> PA1::toBinary(vector<string> text, unordered_map<char, string> huffmanMap)
{
    vector<bool> result{};

	//after you have the tree, walk down the tree until you see a leaf node
	
	//if leaf node:


    return result;
}