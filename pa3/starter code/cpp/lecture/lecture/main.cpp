#include "CityGraph.h";
#include "CsvParser.h"
#include <iostream>;
#include <algorithm>;


int main(void)
{

	//map_num: mapping of vertexs file string
	//deliv_num: delivery file string

	string map_num;
	string deliv_num;

	//cout << "*** Route Planner ***" << endl;
	//cout << "Enter maps file: ";
	//cin >> map_num;
	//cout << "Enter destinations file: ";
	//cin >> deliv_num;

	//Putting the map file into a 2D vector
	CsvStateMachine mapping{ "map1.txt" };
	vector<vector<string>> map_vector = mapping.processFile();

	//Putting the delivery file in a 2D vector even though we dont need it, its makes it easier on me
	CsvStateMachine destinations{ "deliveries1.txt" };
	vector<vector<string>> dest_vector = destinations.processFile();

	//CityGraph that all vertexs and connections will be registered
	CityGraph graph{};

	//Create a unordred map to get all vertexs to put in the city graph
	unordered_map<string, int> vertexs{};
	
	// Adds vertexs before they all get connected
	// Goes through first row while checking to see if the number is already in the graph
	int i = 0;
	int j = 0;

	/*
	for (int i = 0; i < map_vector.size(); i++)
	{
		for (int j = 0; j <= 1; j++)
		{
			if (vertexs.find(map_vector[i][j]) == vertexs.end())
			{
				graph.addVertex(map_vector[i][j]);
			}
		}
	}
	*/

	//Add vertexs only in the deliveries
	for (i = 0; i < dest_vector.size(); i++)
	{
		if (vertexs.find(dest_vector[i][0]) == vertexs.end())
		{
			graph.addVertex(dest_vector[i][0]);
		}
	}

	i = 0;

	//Connect all the vertexs
	while (i < map_vector.size())
	{
		int num = 0;
		string character;

		if (vertexs.find(map_vector[i][j]) == vertexs.end() && vertexs.find(map_vector[i][j + 1]) == vertexs.end())
		{
			character = map_vector[i][2];
			num = stoi(character);
			graph.connectVertex(map_vector[i][0], map_vector[i][1], num);
		}
		i++;
	}

	// After the first row is done, go through the secondst 
	
	auto distances = graph.computeShortestPath(dest_vector[0][0]);
	auto mst = graph.computeMinimumSpanningTree(dest_vector[0][0]);
	
	int total_distance = 0;
	//Now we are going to travel through the deliveries text file
	for (i = 0; i < dest_vector.size(); i++)
	{
		total_distance += mst
	}

	return 0;
}