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

	cout << "*** Route Planner ***" << endl;
	cout << "Enter maps file: ";
	cin >> map_num;
	cout << "Enter destinations file: ";
	cin >> deliv_num;

	//Putting the map file into a 2D vector
	CsvStateMachine mapping{ map_num };
	vector<vector<string>> map_vector = mapping.processFile();

	//Putting the delivery file in a 2D vector even though we dont need it, its makes it easier on me
	CsvStateMachine destinations{ deliv_num };
	vector<vector<string>> dest_vector = destinations.processFile();

	//CityGraph that all vertexs and connections will be registered
	CityGraph graph{};

	// Will also add to this vector for an easy search to see if the character is already in the CityGraph
	vector<string> vertexs{};
	
	// Adds vertexs before they all get connected
	// Goes through first row while checking to see if the number is already in the graph
	int i = 0;
	int j = 0;

	graph.addVertex(map_vector[i][0]);

	while (i <= map_vector.size())
	{
		if()
	}

	// After the first row is done, go through the secondst 
	
	auto distances = graph.computeShortestPath("a");
	auto mst = graph.computeMinimumSpanningTree("a");
	return 0;
}